#include <stddef.h>
#include "VnV.h"

INJECTION_EXECUTABLE(MOOSE) 

static const char* moose_vnv_schema = "{\"type\": \"object\", \"required\":[]}";

/**
 * VnV allows users to set options in hypre using the input file. This callback
 * registers the json schema for the available options with the toolkit and defines
 * the options callback. Because we are in C, we are using the C interface. 
 * 
 * Life would be way easier if we can just compile this file with c++ :)
 *
 * TODO: Add options to the schema and parse them in this function.
 */ 
INJECTION_OPTIONS(MOOSE, moose_vnv_schema) {

}

INJECTION_SUBPACKAGE(MOOSE,LIBMESH)


/** For testing purposes only -- if you are seeing this, i forgot to remove it
 *
 */

int moose_vnv_test_function(int x) {
   
  INJECTION_LOOP_BEGIN("MOOSE", VWORLD, "SanityCheck", x);
  for (int i = 0; i < 10; i++) {
    x += i;
    INJECTION_LOOP_ITER("MOOSE","SanityCheck", "inner");
  }

  INJECTION_LOOP_END("MOOSE","SanityCheck");
  return x;
}
