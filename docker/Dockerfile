ARG FROM_IMAGE=vnv_libmesh
FROM ${FROM_IMAGE}

ARG COMMIT_HASH=unknown
LABEL vnv.version.moose=${COMMIT_HASH}


#Install MOOSE with VnV
COPY . ${SOURCE_DIR}/moose 

RUN cd ${SOURCE_DIR}/moose/framework\
    && bear make -j8 \
    && ${VNV_MATCHER} --package MOOSE\
                      --fix-omp \
		      --cache vnv.__cache__\
		      --output src/utils/vnv_MOOSE.c \
                      compile_commands.json \
    && make

# Build the VnV example that we created 
RUN cd ${SOURCE_DIR}/moose/examples/ex01_inputfile && make vnv 

ENV MOOSE_DIR=${SOURCE_DIR}/moose

ENV VNV_CONFIG=${VNV_CONFIG}:${MOOSE_DIR}/vnv.__registration__
ENV VNV_CONFIG=${VNV_CONFIG}:${SOURCE_DIR}/moose/docker/config/vnv.__registration__


