#include <stddef.h>
#include "VnV.h"

INJECTION_LIBRARY(MOOSE) 

static const char* moose_vnv_schema = "{\"type\": \"object\", \"required\":[]}";

/**
 *
 * Welcome to MOOSE
 *
 */ 

INJECTION_OPTIONS(MOOSE, moose_vnv_schema,void) {
	std::string inputfile;

	std::cout << "LOOK AT ME " << std::endl;

	// Look on the command line for an input file. 
	// If it exists, we are good to go -- use the command line
	// as the best option. 
	for (int i = 0; i < cmdline.size(); i++ )  {
		if (cmdline[i].compare("-i") == 0 ) {
			return nullptr;
		}
	}

	// Otherwise -- lets use the input file. 
	auto inf = config.find("inputfile");
	if (inf != config.end()) {
		inputfile = config["inputfile"].get<std::string>();
		cmdline.push_back("-i");
		cmdline.push_back(config["inputfile"].get<std::string>());
		return nullptr;
	}

	// Other Otherwise -- no input file found so moose will blow up.
	// But, lets let MOOSE handle that for now.
	return nullptr;

}

INJECTION_SUBPACKAGE(MOOSE,LIBMESH)

