///2181537665051660697
/// This file was automatically generated using the VnV-Matcher executable. 
/// The matcher allows for automatic registration of all VnV plugins and injection 
/// points. Building the matcher requires Clang. If Clang is not available on this machine,
/// Registration code should be written manually. 
/// 

//PACKAGENAME: MOOSE_PF_EX

#include "VnV.h" 
DECLARESUBPACKAGE(MOOSE)
const char* getFullRegistrationJson_MOOSE_PF_EX(){
	 return "{\"Communicator\":{\"docs\":\"\",\"name\":\"mpi\",\"package\":\"VNV\"},\"Conclusion\":\"\",\"InjectionPoints\":{\"SanityCheck\":{\"docs\":\"\\n This is some information about the injection point. This text is \\n parsed as restructured text (rST). What ever we put here will show\\n up in the introduction section of this injection point. If you\\n pass a callback function, or set the \\\"write-data\\\" flag for the injection\\n point, you can use the vnv extension for sphinx to inject data values\\n here as well. \\n\\n   \",\"name\":\"SanityCheck\",\"packageName\":\"MOOSE_PF_EX\",\"parameters\":[{\"x\":\"int\"},{\"x\":\"int\"}],\"stages\":{\"Begin\":{\"docs\":\"\",\"info\":{\"Calling Function\":\"moose_pf_ex_vnv_test_function\",\"Calling Function Column\":1,\"Calling Function Line\":20,\"filename\":\"src/main.C\",\"lineColumn\":5,\"lineNumber\":130}},\"End\":{\"docs\":\"\",\"info\":{\"Calling Function\":\"moose_pf_ex_vnv_test_function\",\"Calling Function Column\":1,\"Calling Function Line\":20,\"filename\":\"src/main.C\",\"lineColumn\":5,\"lineNumber\":139}},\"inner\":{\"docs\":\"\",\"info\":{\"Calling Function\":\"moose_pf_ex_vnv_test_function\",\"Calling Function Column\":1,\"Calling Function Line\":20,\"filename\":\"src/main.C\",\"lineColumn\":5,\"lineNumber\":143}}}}},\"Introduction\":\"\\n This is the introduction.\\n\\n   \",\"SubPackages\":{\"MOOSE\":{\"docs\":\"\",\"name\":\"MOOSE\",\"packageName\":\"MOOSE_PF_EX\"}}}";}

INJECTION_REGISTRATION(MOOSE_PF_EX){
	REGISTERSUBPACKAGE(MOOSE_PF_EX,MOOSE);
	VnV_Declare_Communicator("MOOSE_PF_EX","VNV","mpi");
	Register_Injection_Point(MOOSE_PF_EX,SanityCheck,0,"{\"x\":\"int\"}");
	REGISTER_FULL_JSON(MOOSE_PF_EX, getFullRegistrationJson_MOOSE_PF_EX);
};



