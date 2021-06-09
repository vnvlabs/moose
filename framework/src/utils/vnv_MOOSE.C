///6085033441766171164
/// This file was automatically generated using the VnV-Matcher executable. 
/// The matcher allows for automatic registration of all VnV plugins and injection 
/// points. Building the matcher requires Clang. If Clang is not available on this machine,
/// Registration code should be written manually. 
/// 

//PACKAGENAME: MOOSE

#include "VnV.h" 
DECLARESUBPACKAGE(LIBMESH)
DECLAREOPTIONS(MOOSE)
const char* getFullRegistrationJson_MOOSE(){
	 return "{\"Communicator\":{\"docs\":\"\",\"name\":\"mpi\",\"package\":\"VNV\"},\"InjectionPoints\":{\"PicardStepSuccessfull\":{\"docs\":\"\\n Picard Step Completed \\n ==================================\\n\\n A picard step was completed successfully. \\n       \",\"name\":\"PicardStepSuccessfull\",\"packageName\":\"MOOSE\",\"parameters\":[{\"end_norm\":\"libMesh::Real\",\"end_norm_old\":\"libMesh::Real\"}],\"stages\":{\"Begin\":{\"docs\":\"\",\"info\":{\"Calling Function\":\"solveStep\",\"Calling Function Column\":1,\"Calling Function Line\":400,\"filename\":\"/home/ben/source/vv/vnv/applications/MOOSE/framework/src/executioners/PicardSolve.C\",\"lineColumn\":5,\"lineNumber\":126}}}},\"SanityCheck\":{\"docs\":\"\",\"name\":\"SanityCheck\",\"packageName\":\"MOOSE\",\"parameters\":[{\"x\":\"int\"}],\"stages\":{\"Begin\":{\"docs\":\"\",\"info\":{\"Calling Function\":\"moose_vnv_test_function\",\"Calling Function Column\":1,\"Calling Function Line\":28,\"filename\":\"/home/ben/source/vv/vnv/applications/MOOSE/framework/src/utils/vnv.C\",\"lineColumn\":5,\"lineNumber\":136}},\"End\":{\"docs\":\"\",\"info\":{\"Calling Function\":\"moose_vnv_test_function\",\"Calling Function Column\":1,\"Calling Function Line\":28,\"filename\":\"/home/ben/source/vv/vnv/applications/MOOSE/framework/src/utils/vnv.C\",\"lineColumn\":5,\"lineNumber\":145}},\"inner\":{\"docs\":\"\",\"info\":{\"Calling Function\":\"moose_vnv_test_function\",\"Calling Function Column\":1,\"Calling Function Line\":28,\"filename\":\"/home/ben/source/vv/vnv/applications/MOOSE/framework/src/utils/vnv.C\",\"lineColumn\":5,\"lineNumber\":149}}}}},\"Options\":\"\\n VnV allows users to set options in hypre using the input file. This callback\\n registers the json schema for the available options with the toolkit and defines\\n the options callback. Because we are in C, we are using the C interface. \\n \\n Life would be way easier if we can just compile this file with c++ :)\\n\\n TODO: Add options to the schema and parse them in this function.\\n \",\"SubPackages\":{\"LIBMESH\":{\"docs\":\"\",\"name\":\"LIBMESH\",\"packageName\":\"MOOSE\"}}}";}

INJECTION_REGISTRATION(MOOSE){
	REGISTERSUBPACKAGE(MOOSE,LIBMESH);
	REGISTEROPTIONS(MOOSE)
	VnV_Declare_Communicator("MOOSE","VNV","mpi");
	Register_Injection_Point("MOOSE","PicardStepSuccessfull",0,"{\"end_norm\":\"libMesh::Real\",\"end_norm_old\":\"libMesh::Real\"}");
	Register_Injection_Point("MOOSE","SanityCheck",0,"{\"x\":\"int\"}");
	REGISTER_FULL_JSON(MOOSE, getFullRegistrationJson_MOOSE);
};



