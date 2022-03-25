//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "PorousFlowTestApp.h"
#include "MooseInit.h"
#include "Moose.h"
#include "MooseApp.h"
#include "AppFactory.h"
#include "VnV.h"

INJECTION_EXECUTABLE(POROUSFLOW) 
INJECTION_SUBPACKAGE(POROUSFLOW,MOOSE)

int moose_pf_ex_vnv_test_function(int x) {
  
  /**
   * This is some information about the injection point. This text is 
   * parsed as restructured text (rST). What ever we put here will show
   * up in the introduction section of this injection point. If you
   * pass a callback function, or set the "write-data" flag for the injection
   * point, you can use the vnv extension for sphinx to inject data values
   * here as well. 
   *
   */      	
  INJECTION_LOOP_BEGIN("POROUSFLOW", VWORLD, "SanityCheck", x)
  for (int i = 0; i < 10; i++) {
    x += i;
    INJECTION_LOOP_ITER("POROUSFLOW","SanityCheck", "inner");
  }

  INJECTION_LOOP_END("POROUSFLOW", "SanityCheck");
  return x;
}

// Create a performance log
PerfLog Moose::perf_log("PorousFlow");

// Begin the main program.
int
main(int argc, char * argv[])
{
  // Initialize MPI, solvers and MOOSE
  MooseInit init(argc, argv);
 
  /**
   * This is the introduction.
   *
   */ 
  INJECTION_INITIALIZE(POROUSFLOW, &argc, &argv, "./vv-input.json" );

  /** 
   * Run a quick function with some injetion points for testing. 
   */
  moose_pf_ex_vnv_test_function(10);

  // Register this application's MooseApp and any it depends on
  PorousFlowTestApp::registerApps();

  // Create an instance of the application and store it in a smart pointer for easy cleanup
  std::shared_ptr<MooseApp> app = AppFactory::createAppShared("PorousFlowTestApp", argc, argv);

  // Execute the application
  app->run();

  INJECTION_FINALIZE(POROUSFLOW)

  return 0;
}
