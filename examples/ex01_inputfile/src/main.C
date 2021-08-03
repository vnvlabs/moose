//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

/**
 * Example 1: Input File - The smallest MOOSE based application possible.  It solves
 * a simple 2D diffusion problem with Dirichlet boundary conditions using built-in
 * objects from MOOSE.
 */

#include "ExampleApp.h"

// Moose Includes
#include "MooseInit.h"
#include "MooseApp.h"
#include "AppFactory.h"

#include "VnV.h"

INJECTION_EXECUTABLE(MOOSE_EX01) 
INJECTION_SUBPACKAGE(MOOSE_EX01,MOOSE)

int moose_ex01_vnv_test_function(int x) {
  
  /**
   * This is some information about the injection point. This text is 
   * parsed as restructured text (rST). What ever we put here will show
   * up in the introduction section of this injection point. If you
   * pass a callback function, or set the "write-data" flag for the injection
   * point, you can use the vnv extension for sphinx to inject data values
   * here as well. 
   *
   */      	
  INJECTION_LOOP_BEGIN("MOOSE_EX01", VWORLD, "SanityCheck", x);
  for (int i = 0; i < 10; i++) {
    x += i;
    INJECTION_LOOP_ITER("MOOSE_EX01","SanityCheck","inner");
  }

  INJECTION_LOOP_END("MOOSE_EX01","SanityCheck");
  return x;
}

// Create a performance log
PerfLog Moose::perf_log("Example");

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
  INJECTION_INITIALIZE(MOOSE_EX01, &argc, &argv, "./vv-input.json" );

  /** 
   * Run a quick function with some injetion points for testing. 
   */
  moose_ex01_vnv_test_function(10);
		  
  // Register this application's MooseApp and any it depends on
  ExampleApp::registerApps();

  // Create an instance of the application and store it in a smart pointer for easy cleanup
  std::shared_ptr<MooseApp> app = AppFactory::createAppShared("ExampleApp", argc, argv);

  // Execute the application
  app->run();

  /** 
   * This is the conclusion.
   * 
   */ 
  INJECTION_FINALIZE(MOOSE_EX01);


  return 0;
}
