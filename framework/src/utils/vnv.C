#include <stddef.h>
#include "VnV.h"

INJECTION_EXECUTABLE(MOOSE) 

static const char* moose_vnv_schema = "{\"type\": \"object\", \"required\":[]}";

/**
 *
 * Welcome to MOOSE
 *
 */ 

INJECTION_OPTIONS(MOOSE, moose_vnv_schema) {
	return nullptr;
}

INJECTION_SUBPACKAGE(MOOSE,LIBMESH)


/** 
 *
 * For testing purposes only -- if you are seeing this, i forgot to remove it
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
