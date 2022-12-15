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
	return nullptr;
}

INJECTION_SUBPACKAGE(MOOSE,LIBMESH)

