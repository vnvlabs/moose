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

/**
<<<<<<< HEAD
 * Example 1: As simple As It Gets
 * ===============================
 * 
 * 
 * This example briefly describes the creation of a basic input file and the 
 * six required sections for utilizing MOOSE for solving a problem.
 * 
 * 
 */
=======
 * @title Input Files
 * @description Moose Tutorial on Input Files
 * @configuration {
 *    "specDump" : "${application} -i ex01.i",
 *    "empty_exec" : false,
 *    "exec" : {
 *        "active_overrides" : ["ex01.i"]
 *        "overrides" : {
 *           "ex01.i" : {
 *              "command-line" : "${application} -i ex01.i"
 *              "name" : "Example 1" 
 *           },
 *        }
 *    }
 * 
 * 
 * }
*/
>>>>>>> c759b69a2127a9243ffbd81b5e74a4b71e3ba893
INJECTION_EXECUTABLE(MOOSE_EX01) 



INJECTION_SUBPACKAGE(MOOSE_EX01,MOOSE)

// Create a performance log
PerfLog Moose::perf_log("Example");

// Begin the main program.
int
main(int argc, char * argv[])
{
  // Initialize MPI, solvers and MOOSE
  MooseInit init(argc, argv);

  
  INJECTION_INITIALIZE(MOOSE_EX01, &argc, &argv, "./vv-input.json" );
	  
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
