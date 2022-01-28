///MOOSE:10732245286327370187
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
	 return "{\"InjectionPoints\":{\"PicardStepSuccessfull\":{\"docs\":{\"description\":\"\",\"instructions\":\"\",\"params\":{},\"template\":\"\\n Picard Step Completed \\n ==================================\\n\\n A picard step was completed successfully. \\n       \\n\",\"title\":\"\"},\"name\":\"PicardStepSuccessfull\",\"packageName\":\"MOOSE\",\"parameters\":{\"bool PicardSolve::solveStep(libMesh::Real, libMesh::Real &, libMesh::Real, libMesh::Real &, bool, const std::set<dof_id_type> &)\":{\"end_norm\":\"libMesh::Real\",\"end_norm_old\":\"libMesh::Real\"}},\"stages\":{\"Begin\":{\"docs\":{\"description\":\"\",\"instructions\":\"\",\"params\":{},\"template\":\"\",\"title\":\"\"},\"info\":{\"Calling Function\":\"solveStep\",\"Calling Function Column\":1,\"Calling Function Line\":400,\"filename\":\"/home/ben/source/vv/applications/MOOSE/framework/src/executioners/PicardSolve.C\",\"lineColumn\":5,\"lineNumber\":81}}}},\"SanityCheck\":{\"docs\":{\"description\":\"\",\"instructions\":\"\",\"params\":{},\"template\":\"\",\"title\":\"\"},\"loop\":true,\"name\":\"SanityCheck\",\"packageName\":\"MOOSE\",\"parameters\":{\"int moose_vnv_test_function(int)\":{\"x\":\"int\"}},\"stages\":{\"Begin\":{\"docs\":{\"description\":\"\",\"instructions\":\"\",\"params\":{},\"template\":\"\",\"title\":\"\"},\"info\":{\"Calling Function\":\"moose_vnv_test_function\",\"Calling Function Column\":1,\"Calling Function Line\":28,\"filename\":\"/home/ben/source/vv/applications/MOOSE/framework/src/utils/vnv.C\",\"lineColumn\":5,\"lineNumber\":86}},\"End\":{\"docs\":{\"description\":\"\",\"instructions\":\"\",\"params\":{},\"template\":\"\",\"title\":\"\"},\"info\":{\"Calling Function\":\"moose_vnv_test_function\",\"Calling Function Column\":1,\"Calling Function Line\":28,\"filename\":\"/home/ben/source/vv/applications/MOOSE/framework/src/utils/vnv.C\",\"lineColumn\":43,\"lineNumber\":101}}}}},\"Options\":{\"description\":\"\",\"instructions\":\"\",\"params\":{},\"template\":\"\\n VnV allows users to set options in hypre using the input file. This callback\\n registers the json schema for the available options with the toolkit and defines\\n the options callback. Because we are in C, we are using the C interface. \\n \\n Life would be way easier if we can just compile this file with c++ :)\\n\\n TODO: Add options to the schema and parse them in this function.\\n \\n\",\"title\":\"\"},\"SubPackages\":{\"LIBMESH\":{\"docs\":{\"description\":\"\",\"instructions\":\"\",\"params\":{},\"template\":\"\",\"title\":\"\"},\"name\":\"LIBMESH\",\"packageName\":\"MOOSE\"}}}";}

INJECTION_REGISTRATION(MOOSE){
	REGISTERSUBPACKAGE(LIBMESH);
	REGISTEROPTIONS(MOOSE)
	Register_Injection_Point("MOOSE","PicardStepSuccessfull","{\"bool PicardSolve::solveStep(libMesh::Real, libMesh::Real &, libMesh::Real, libMesh::Real &, bool, const std::set<dof_id_type> &)\":{\"end_norm\":\"libMesh::Real\",\"end_norm_old\":\"libMesh::Real\"}}");
	Register_Injection_Point("MOOSE","SanityCheck","{\"int moose_vnv_test_function(int)\":{\"x\":\"int\"}}");
	REGISTER_FULL_JSON(MOOSE, getFullRegistrationJson_MOOSE);
}



