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

RUN cd /gui && git pull && cd python_api && cd build && make 

# Build the VnV example that we created 
ENV MOOSE_DIR=${SOFTWARE_DIR}/moose
RUN cd ${SOFTWARE_DIR}/moose/examples/ && python3 make_all.py make vnv 



