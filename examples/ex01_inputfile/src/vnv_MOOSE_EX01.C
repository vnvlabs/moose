///6570327945584457979
/// This file was automatically generated using the VnV-Matcher executable. 
/// The matcher allows for automatic registration of all VnV plugins and injection 
/// points. Building the matcher requires Clang. If Clang is not available on this machine,
/// Registration code should be written manually. 
/// 

//PACKAGENAME: MOOSE_EX01

#include "VnV.h" 
DECLARESUBPACKAGE(MOOSE)
const char* getFullRegistrationJson_MOOSE_EX01(){
	 return "{\"Communicator\":{\"docs\":\"\",\"name\":\"mpi\",\"package\":\"VNV\"},\"Conclusion\":\"\\nThis is the conclusion.\",\"InjectionPoints\":{\"SanityCheck\":{\"docs\":\"\\n This is some information about the injection point. This text is \\n parsed as restructured text (rST). What ever we put here will show\\n up in the introduction section of this injection point. If you\\n pass a callback function, or set the \\\"write-data\\\" flag for the injection\\n point, you can use the vnv extension for sphinx to inject data values\\n here as well. \\n\\n   \",\"name\":\"SanityCheck\",\"packageName\":\"MOOSE_EX01\",\"parameters\":[{\"x\":\"int\"}],\"stages\":{\"Begin\":{\"docs\":\"\",\"info\":{\"Calling Function\":\"moose_ex01_vnv_test_function\",\"Calling Function Column\":1,\"Calling Function Line\":28,\"filename\":\"/home/ben/source/vv/vnv/applications/MOOSE/examples/ex01_inputfile/src/main.C\",\"lineColumn\":5,\"lineNumber\":136}},\"End\":{\"docs\":\"\",\"info\":{\"Calling Function\":\"moose_ex01_vnv_test_function\",\"Calling Function Column\":1,\"Calling Function Line\":28,\"filename\":\"/home/ben/source/vv/vnv/applications/MOOSE/examples/ex01_inputfile/src/main.C\",\"lineColumn\":5,\"lineNumber\":145}},\"inner\":{\"docs\":\"\",\"info\":{\"Calling Function\":\"moose_ex01_vnv_test_function\",\"Calling Function Column\":1,\"Calling Function Line\":28,\"filename\":\"/home/ben/source/vv/vnv/applications/MOOSE/examples/ex01_inputfile/src/main.C\",\"lineColumn\":5,\"lineNumber\":149}}}}},\"Introduction\":\"\\n This is the introduction.\\n\\n   \",\"SubPackages\":{\"MOOSE\":{\"docs\":\"\",\"name\":\"MOOSE\",\"packageName\":\"MOOSE_EX01\"}}}";}

INJECTION_REGISTRATION(MOOSE_EX01){
	REGISTERSUBPACKAGE(MOOSE_EX01,MOOSE);
	VnV_Declare_Communicator("MOOSE_EX01","VNV","mpi");
	Register_Injection_Point("MOOSE_EX01","SanityCheck",0,"{\"x\":\"int\"}");
	REGISTER_FULL_JSON(MOOSE_EX01, getFullRegistrationJson_MOOSE_EX01);
};



