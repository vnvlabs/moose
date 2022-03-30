ARG FROM_IMAGE=vnv_libmesh
FROM ${FROM_IMAGE}:latest

#Install MOOSE with VnV
COPY . ./moose 

RUN cd moose/framework && python3 bear.py /usr/lib/gcc/x86_64-linux-gnu/9/include make -j8 
RUN cd moose/framework && ${VNV_MATCHER} --package MOOSE --output src/utils/vnv_MOOSE.c compile_commands.json && make

ARG COMMIT_HASH=unknown
LABEL vnv.version.moose=${COMMIT_HASH}

ENV VNV_CONFIG=${VNV_CONFIG}:/MOOSE/.vnv-config.json





