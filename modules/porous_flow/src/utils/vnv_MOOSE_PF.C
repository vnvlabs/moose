///3471573069150029232
/// This file was automatically generated using the VnV-Matcher executable. 
/// The matcher allows for automatic registration of all VnV plugins and injection 
/// points. Building the matcher requires Clang. If Clang is not available on this machine,
/// Registration code should be written manually. 
/// 

//PACKAGENAME: MOOSE_PF

#include "VnV.h" 
DECLARESUBPACKAGE(MOOSE)
DECLAREOPTIONS(MOOSE_PF)
const char* getFullRegistrationJson_MOOSE_PF(){
	 return "{\"Communicator\":{\"docs\":\"\",\"name\":\"mpi\",\"package\":\"VNV\"},\"InjectionPoints\":{\"SanityCheck\":{\"docs\":\"\",\"name\":\"SanityCheck\",\"packageName\":\"MOOSE_PF\",\"parameters\":[{\"x\":\"int\"},{\"x\":\"int\"}],\"stages\":{\"Begin\":{\"docs\":\"\",\"info\":{\"Calling Function\":\"moose_pf_vnv_test_function\",\"Calling Function Column\":1,\"Calling Function Line\":29,\"filename\":\"/home/ben/work/vnv/libs/moose/modules/porous_flow/src/utils/vnv.C\",\"lineColumn\":5,\"lineNumber\":130}},\"End\":{\"docs\":\"\",\"info\":{\"Calling Function\":\"moose_pf_vnv_test_function\",\"Calling Function Column\":1,\"Calling Function Line\":29,\"filename\":\"/home/ben/work/vnv/libs/moose/modules/porous_flow/src/utils/vnv.C\",\"lineColumn\":5,\"lineNumber\":139}},\"inner\":{\"docs\":\"\",\"info\":{\"Calling Function\":\"moose_pf_vnv_test_function\",\"Calling Function Column\":1,\"Calling Function Line\":29,\"filename\":\"/home/ben/work/vnv/libs/moose/modules/porous_flow/src/utils/vnv.C\",\"lineColumn\":5,\"lineNumber\":143}}}}},\"Options\":\"\\n VnV allows users to set options in hypre using the input file. This callback\\n registers the json schema for the available options with the toolkit and defines\\n the options callback. Because we are in C, we are using the C interface. \\n \\n Life would be way easier if we can just compile this file with c++ :)\\n\\n TODO: Add options to the schema and parse them in this function.\\n \",\"SubPackages\":{\"MOOSE\":{\"docs\":\"\",\"name\":\"MOOSE\",\"packageName\":\"MOOSE_PF\"}}}";}

INJECTION_REGISTRATION(MOOSE_PF){
	REGISTERSUBPACKAGE(MOOSE_PF,MOOSE);
	REGISTEROPTIONS(MOOSE_PF)
	VnV_Declare_Communicator("MOOSE_PF","VNV","mpi");
	Register_Injection_Point(MOOSE_PF,SanityCheck,0,"{\"x\":\"int\"}");
	REGISTER_FULL_JSON(MOOSE_PF, getFullRegistrationJson_MOOSE_PF);
};



