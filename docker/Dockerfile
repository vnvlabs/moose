

from vnv_libmesh:latest

RUN cd /vnv-mount/applications/MOOSE/framework && bear make && ${VNV_MATCHER} --package MOOSE --extension C --output src/utils/vnv compile_commands.json && make
RUN cd /vnv-mount/applications/MOOSE/examples/ex01_inputfile && bear make && ${VNV_MATCHER} --package MOOSE --extension C --output vnv compile_commands.json && make

