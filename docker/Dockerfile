ARG FROM_IMAGE=vnv_libmesh
FROM ${FROM_IMAGE}:latest

ARG COMMIT_HASH=unknown
LABEL vnv.version.moose=${COMMIT_HASH}

ENV VNV_CONFIG=${VNV_CONFIG}:${SOURCE_DIR}/MOOSE/.vnv-config.json

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





