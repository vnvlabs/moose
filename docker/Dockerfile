

from vnv_libmesh:latest
COPY . ./moose 
RUN cd moose/framework && bear make && ${VNV_MATCHER} --package MOOSE --extension C --output src/utils/vnv compile_commands.json && make
RUN cd moose/examples/ex01_inputfile && bear make && ${VNV_MATCHER} --package MOOSE --extension C --output vnv compile_commands.json && make

