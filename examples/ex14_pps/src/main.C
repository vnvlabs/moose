//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

/**
 * Example 14: Functions - Using Postprocessors
 *
 * This example will show how to execute some code verification
 * via Method of Manufactured Solutions (MMS).
 *
 * This is achieved by specifying Functions for a forcing function
 * and boundary condition as well as exact solution.  Then comparing
 * the computed solution to the exact solution using Postprocessors.
 */

#include "ExampleApp.h"

// Moose Includes
#include "MooseInit.h"
#include "MooseApp.h"
#include "AppFactory.h"

#include "VnV.h" 

INJECTION_EXECUTABLE(VNV_APP_NAME) 
INJECTION_SUBPACKAGE(VNV_APP_NAME,MOOSE)



// Create a performance log
PerfLog Moose::perf_log("Example");

// Begin the main program.
int main(int argc, char * argv[])
{
  
  
  // Initialize MPI, solvers and MOOSE
  MooseInit init(argc, argv);
  
  /**
   * @title Example 14: Using PostProcessors.
   * 
   * This example will show how to execute some code verification
   * via Method of Manufactured Solutions (MMS).
   *
   * This is achieved by specifying Functions for a forcing function
   * and boundary condition as well as exact solution.  Then comparing
   * the computed solution to the exact solution using Postprocessors.
   * 
  */ 
  INJECTION_INITIALIZE(VNV_APP_NAME, &argc, &argv, "./vv-input.json" );
  

  // Register this application's MooseApp and any it depends on
  
  ExampleApp::registerApps();
  

  // Create an instance of the application and store it in a smart pointer for easy cleanup
  std::shared_ptr<MooseApp> app = AppFactory::createAppShared("ExampleApp", argc, argv);

  // Execute the application

  /**
    * @title title
    *
    * description
    *
    **/
    app->run();  


  INJECTION_FINALIZE(VNV_APP_NAME);
  return 0;
}
