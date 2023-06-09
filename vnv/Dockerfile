ARG FROM_IMAGE=vnv_libmesh
FROM ${FROM_IMAGE}

#Install MOOSE with VnV
COPY . ${SOFTWARE_DIR}/moose 

RUN cd ${SOFTWARE_DIR}/moose/framework\
    && bear make -j8 \
    && ${VNV_MATCHER} --package MOOSE\
                      --fix-omp \
  		              --cache vnv.__cache__\
    		          --output src/utils/vnv_MOOSE.C \
                      compile_commands.json \
    && make

# Build the VnV example that we created 
ENV MOOSE_DIR=${SOFTWARE_DIR}/moose
RUN cd ${SOFTWARE_DIR}/moose/examples/ex01_inputfile && make vnv 

RUN ${VNV_REGISTER} gui moose ${SOFTWARE_DIR}/moose/vnv/gui/vnv.__registration__ 



