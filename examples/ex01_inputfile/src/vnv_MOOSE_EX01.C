///MOOSE_EX01:11475469920203088589
/// This file was automatically generated using the VnV-Matcher executable. 
/// The matcher allows for automatic registration of all VnV plugins and injection 
/// points. Building the matcher requires Clang. If Clang is not available on this machine,
/// Registration code should be written manually. 
/// 

//PACKAGENAME: MOOSE_EX01

#include "VnV.h" 
DECLARESUBPACKAGE(MOOSE)
const char* getFullRegistrationJson_MOOSE_EX01(){
	 return "{\"Conclusion\":{\"description\":\"\",\"instructions\":\"\",\"params\":{},\"template\":\"\\nThis is the conclusion.\\n\",\"title\":\"\"},\"InjectionPoints\":{\"SanityCheck\":{\"docs\":{\"description\":\"\",\"instructions\":\"\",\"params\":{},\"template\":\"\\n This is some information about the injection point. This text is \\n parsed as restructured text (rST). What ever we put here will show\\n up in the introduction section of this injection point. If you\\n pass a callback function, or set the \\\"write-data\\\" flag for the injection\\n point, you can use the vnv extension for sphinx to inject data values\\n here as well. \\n\\n   \\n\",\"title\":\"\"},\"loop\":true,\"name\":\"SanityCheck\",\"packageName\":\"MOOSE_EX01\",\"parameters\":{\"int moose_ex01_vnv_test_function(int)\":{\"x\":\"int\"}},\"stages\":{\"Begin\":{\"docs\":{\"description\":\"\",\"instructions\":\"\",\"params\":{},\"template\":\"\",\"title\":\"\"},\"info\":{\"Calling Function\":\"moose_ex01_vnv_test_function\",\"Calling Function Column\":1,\"Calling Function Line\":28,\"filename\":\"/home/ben/source/vv/applications/MOOSE/examples/ex01_inputfile/src/main.C\",\"lineColumn\":5,\"lineNumber\":86}},\"End\":{\"docs\":{\"description\":\"\",\"instructions\":\"\",\"params\":{},\"template\":\"\",\"title\":\"\"},\"info\":{\"Calling Function\":\"moose_ex01_vnv_test_function\",\"Calling Function Column\":1,\"Calling Function Line\":28,\"filename\":\"/home/ben/source/vv/applications/MOOSE/examples/ex01_inputfile/src/main.C\",\"lineColumn\":43,\"lineNumber\":101}}}}},\"Introduction\":{\"description\":\"\",\"instructions\":\"\",\"params\":{},\"template\":\"\\n This is the introduction.\\n\\n   \\n\",\"title\":\"\"},\"SubPackages\":{\"MOOSE\":{\"docs\":{\"description\":\"\",\"instructions\":\"\",\"params\":{},\"template\":\"\",\"title\":\"\"},\"name\":\"MOOSE\",\"packageName\":\"MOOSE_EX01\"}}}";}

INJECTION_REGISTRATION(MOOSE_EX01){
	REGISTERSUBPACKAGE(MOOSE);
	Register_Injection_Point("MOOSE_EX01","SanityCheck","{\"int moose_ex01_vnv_test_function(int)\":{\"x\":\"int\"}}");
	REGISTER_FULL_JSON(MOOSE_EX01, getFullRegistrationJson_MOOSE_EX01);
}



