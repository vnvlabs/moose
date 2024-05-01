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
 * Example 1: As simple As It Gets
 * ===============================
 * 
 * 
 * This example briefly describes the creation of a basic input file and the 
 * six required sections for utilizing MOOSE for solving a problem.
 * 
 * 
 */
INJECTION_EXECUTABLE(VNV_APP_NAME,"{}") 

INJECTION_SUBPACKAGE(VNV_APP_NAME,MOOSE)

// Create a performance log
PerfLog Moose::perf_log("Example");

// Begin the main program.
int
main(int argc, char * argv[])
{
  // Initialize MPI, solvers and MOOSE
  MooseInit init(argc, argv);

  
  INJECTION_INITIALIZE(VNV_APP_NAME, &argc, &argv, "./vv-input.json" );
	  
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
  INJECTION_FINALIZE(VNV_APP_NAME);


  return 0;
}
