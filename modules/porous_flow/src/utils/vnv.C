#include <stddef.h>
#include "VnV.h"

INJECTION_LIBRARY(MOOSE_PF) 

static const char* moose_pf_vnv_schema = "{\"type\": \"object\", \"required\":[]}";

/**
 * VnV allows users to set options in hypre using the input file. This callback
 * registers the json schema for the available options with the toolkit and defines
 * the options callback. Because we are in C, we are using the C interface. 
 * 
 * Life would be way easier if we can just compile this file with c++ :)
 *
 * TODO: Add options to the schema and parse them in this function.
 */ 
INJECTION_OPTIONS(MOOSE_PF, moose_pf_vnv_schema, void) {

}

// Let VnV know that this package uses MOOSE. 
INJECTION_SUBPACKAGE(MOOSE_PF, MOOSE)


