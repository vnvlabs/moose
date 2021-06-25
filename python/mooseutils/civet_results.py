#!/usr/bin/env python3
#* This file is part of the MOOSE framework
#* https://www.mooseframework.org
#*
#* All rights reserved, see COPYRIGHT for full restrictions
#* https://github.com/idaholab/moose/blob/master/COPYRIGHT
#*
#* Licensed under LGPL 2.1, please see LICENSE for details
#* https://www.gnu.org/licenses/lgpl-2.1.html
import os
import sys
import re
import glob
import tarfile
import tempfile
import enum
import urllib.request
import urllib.error
import collections
import logging
import subprocess

DEFAULT_JOBS_CACHE = os.path.join(os.getenv('HOME'), '.local', 'share', 'civet', 'jobs')
DEFAULT_CIVET_SITE = 'https://civet.inl.gov'
DEFAULT_CIVET_REPO = 'idaholab/moose'

TEST_RE = re.compile(r'^(?:\[(?P<time>.+?)s\])?'       # Optional test time
                     r' *(?P<status>[A-Z]+?)'          # Test status (e.g., OK)
                     r' +(?P<test>.*?)'                # Test name
                     r'(?: +(?P<reason>.*?))?'         # reason FAILED (FAILED (ERRORMSG))
                     r'(?: *\[(?P<caveats>.*?)\])?$',  # Test caveats (e.g., [min_cpus=1])
                     flags=re.MULTILINE)

JOB_RE = re.compile(r'id=\"job_(?P<job>\d+)\"')
JOB_NUMBER_RE = re.compile(r"results_(?P<number>[0-9]+).tar\.gz")
RECIPE_RE = re.compile(r'results_(?P<number>\d+)_(?P<job>.*)/(?P<recipe>.*)')
RUN_TESTS_START_RE = re.compile(r'^.+?run_tests.+?$', flags=re.MULTILINE)
RUN_TESTS_END_RE = re.compile(r'^-{5,}$', flags=re.MULTILINE)
RESULT_FILENAME_RE = re.compile(r'results_(?P<number>[0-9]+)_(?P<recipe>.*)\.tar\.gz')

Test = collections.namedtuple('Test', 'recipe status caveats reason time url')
Job = collections.namedtuple('Job', 'number filename status url')

class JobFileStatus(enum.Enum):
    """Status flag for Job file downloads"""
    CACHE = 0
    LOCAL = 1
    DOWNLOAD = 2
    FAIL = 3

def _get_local_civet_jobs(location, url=None, logger=None):
    """
    Get a list of Job objects for the supplied directory; this searches for tar.gz files with the
    name as: results_<JOB>_*.tar.gz.
    """
    jobs = set()
    for filename in glob.glob(os.path.join(location, 'results_*.tar.gz')):
        match = JOB_NUMBER_RE.search(filename)
        if match:
            jobs.add(Job(int(match.group('number')), filename, JobFileStatus.LOCAL, url))
    return sorted(jobs, key=lambda j: j.number)

def _get_remote_civet_jobs(hashes, site, repo, cache=DEFAULT_JOBS_CACHE, logger=None):
    """
    Get a list of Job objects for the supplied git SHA1 strings.
    """

    jobs = set()
    for sha1 in hashes:
        url = '{}/sha_events/{}/{}'.format(site, repo, sha1)
        pid = urllib.request.urlopen(url)

        page = pid.read().decode('utf8')
        for match in JOB_RE.finditer(page):
            job = jobs.add(_download_job(int(match.group('job')), site, cache, logger))

    return sorted(jobs, key=lambda j: j.number)

def _download_job(job, site, cache, logger):
    """
    Download, if it doesn't already exist, the raw data file from CIVET testing given a Job object.
    """

    if not os.path.isdir(cache):
        os.makedirs(cache)

    url = '{}/job_results/{}'.format(site, job)
    filename = '{}/results_{}.tar.gz'.format(cache, job)

    status = None
    if os.path.isfile(filename):
        if logger:
            logger.debug('Using cached results for job %s', job)
        status = JobFileStatus.CACHE

    else:
        try:
            response = urllib.request.urlopen(url)
            if response.code == 200:
                if logger:
                    logger.debug('Downloading results for job %s', job)
                with open(filename, 'wb') as fid:
                    fid.write(response.read())
                status = JobFileStatus.DOWNLOAD

        except urllib.error.HTTPError:
            if logger:
                logger.warning('Failed to download results for job %s: %s', job, url)
            status = JobFileStatus.FAIL

    return Job(job, filename, status, site)

def _update_database_from_job(job, database, possible):
    """
    Update the test result database given a Job object.
    """

    if job.status == JobFileStatus.FAIL:
        return

    tar = tarfile.open(job.filename, 'r:gz')
    for member in tar.getmembers():
        match = RECIPE_RE.search(member.name)
        recipe = match.group('recipe')
        number = int(match.group('number'))

        f = tar.extractfile(member)
        if f is not None:
            content = f.read().decode('utf8')
            begin = RUN_TESTS_START_RE.search(content)
            if begin is None:
                continue
            end = RUN_TESTS_END_RE.search(content)
            if end is not None:
                _process_results(database, job, recipe, content[begin.end():end.start()], possible)

def _process_results(database, job, recipe, content, possible):
    """
    Extract results from run_tests and update the database.
    """
    for match in TEST_RE.finditer(content):
        caveats = match.group('caveats')
        reason = match.group('reason')
        if caveats is not None:
            caveats = caveats.split(',')

        time = match.group('time')
        if time is not None:
            time = float(time)

        tname = match.group('test').split(':')[-1]
        status = match.group('status')
        if (possible is None) or (status in possible):
            url = job.url if job.url is not None else job.filename
            database[tname][job.number].append(Test(recipe, status, caveats, reason, time, url))

def get_civet_results(local=DEFAULT_JOBS_CACHE,
                      hashes=None,
                      site=(DEFAULT_CIVET_SITE, DEFAULT_CIVET_REPO),
                      possible=None,
                      cache=DEFAULT_JOBS_CACHE, logger=None):

    database = collections.defaultdict(lambda: collections.defaultdict(list))
    if local is not None:
        jobs = _get_local_civet_jobs(local, site[0], logger=logger)
        for job in jobs:
            _update_database_from_job(job, database, possible)

    if hashes is not None:
        jobs = _get_remote_civet_jobs(hashes, site[0], site[1], cache=cache, logger=logger)
        for job in jobs:
            _update_database_from_job(job, database, possible)
    return database


def get_civet_hashes(remote, start='HEAD', branch='master', author='moosetest', logger=None):
    """
    Helper function for returning the hashes associated with testing using CIVET.

    In general, this function should be run from the "master" branch or a release tag that
    stems from a release branch. In this scenario, the script performs the following tasks.

    $ git log --merges --author moosetest -n 1 HEAD

    commit 90123e7b6bd52f1bc36e68aac5d1fa95e76aeb91
    Merge: 20330877ed d72a8d0d69
    Author: moosetest <bounces@inl.gov>
    Date:   Tue May 18 04:24:26 2021 -0600

    Merge commit 'd72a8d0d69e21b4945eedf2e78a7de80b1bd3e6f'

    The first commit that is returned is the commit for the merge: 90123..., which is the
    merge commit performed by CIVET (i.e., moosetest).

    The second commit this is returned is the commit that contains the merge into the "next" branch
    for MOOSE or "devel" for applications, in this case 972a8d.... For MOOSE, on CIVET this hash will
    contain the testing that occurred for the merge into "next" as well as the "devel" testing. For
    applications this will contain the merge into "devel" testing.

    If this function is run on a differing branch where a merge commit doesn't exist, then None is
    returned.
    """

    # Create "git clone" command
    clone_cmd = ['git', 'clone', '--single-branch', '--branch', branch, remote, 'tmp']
    if logger is not None:
        logger.info("Cloning repository to gather commit information, this can take several minutes.")

    # Merge information command
    merge_cmd = ['git', 'log', '--merges', '--author', author, '-n', '1', start]

    with tempfile.TemporaryDirectory(dir='/tmp') as tmp_dir:
        subprocess.run(clone_cmd, capture_output=True, text=True, check=True, cwd=tmp_dir)
        out = subprocess.run(merge_cmd, capture_output=True, text=True, check=True,
                             cwd=os.path.join(tmp_dir, 'tmp'))

        regex = r"commit (?P<master>[a-f0-9]{40}).*?Merge commit\s+'(?P<devel>[0-9a-f]{40})'"
        match = re.match(regex, out.stdout, flags=re.DOTALL|re.UNICODE)
        return (match.group('master'), match.group('devel')) if match else None
