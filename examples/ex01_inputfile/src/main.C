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


 /** Example 1 : As Simple as it Gets
   * ================================
   * 
   * Problem Statement
   * ===================
   * 
   * This example briefly describes the creation of a basic input file and the six required sections
   * for utilizing MOOSE for solving a problem. We consider the steady-state diffusion equation on the 3D domain :vnvmath:`\\Omega`: find :vnvmath:`u` such that
   * 
   * .. vnv-math::
   *     -\nabla \cdot \nabla u = 0 \in \Omega,
   *     
   * where :vnvmath:`u = 1` on the bottom, :vnvmath:`u = 0` on the top and with
   * 
   * .. vnv-math::
   *     \nabla u \cdot \hat{n} = 0
   *     
   * on the remaining boundaries.
   * 
   * The weak form  of this equation, in inner-product notation, is given by: 
   * 
   * .. vnv-math:: 
   *     \nabla \phi*i, \nabla u*h = 0 \quad \forall  \phi*i, 
   * 
   * where :vnvmath:`\\phi*i` are the test functions and :vnvmath:`u_h` is the finite element solution.
   * 
   * Input File Syntax
   * ===================
   * 
   * A basic moose input file requires six parts:
   * 
   * -  Mesh
   * -  Variables
   * -  Kernels
   * -  BCs
   * -  Executioner
   * -  Outputs
   * 
   * Mesh
   * =======
   * 
   * The domain for the problem is created with the **Mesh** block in the input file.  Here the mesh is
   * read from the file **mug.e** which is a relative path starting in the same directory as the input
   * file itself:
   * 
   * .. vnv-hive-code:: ${MOOSE_DIR}/examples/ex01_inputfile/ex01.i
   *    :block: Mesh 
   * 
   * 
   * .. vnv-file:: ${MOOSE_DIR}/examples/ex01_inputfile/mug.e
   *     :height: 600px
   * 
   * Variables
   * ============
   * 
   * In this simple problem, a single variable, 'diffused,' is defined, which represents :vnvmath:`:vnvmath:`u`` from the
   * continuous problem.  The 'diffused' variable is approximated with linear Lagrange shape functions.
   * 
   * .. vnv-hive-code:: ${MOOSE_DIR}/examples/ex01_inputfile/ex01.i
   *    :block: Variables    
   * 
   * 
   * Kernels
   * ==========
   * 
   * The weak form of the problem statement is represented by a **Diffusion** Kernel object.  In general,
   * users write custom Kernels that reside in their own MOOSE-based application(s), but in this case
   * the **Diffusion** Kernel is already defined in MOOSE.  To use a particular Kernel object an input
   * file sub-section is defined, labeled "diff" (this is an arbitrary user-defined name), that
   * utilizes the **Diffusion** **Kernel** and acts on the previously defined variable "diffused".
   * 
   * .. vnv-hive-code:: ${MOOSE_DIR}/examples/ex01_inputfile/ex01.i
   *    :block: Kernels 
   * 
   * Boundary Conditions (BCs)
   * ============================
   * 
   * Boundary conditions are defined in a manner similar to **Kernels**.  For this problem two Dirichlet
   * boundary conditions are required.  In the input file the two boundary conditions are specified
   * each using the **DirichletBC** object provided by MOOSE.
   * 
   * .. vnv-hive-code:: ${MOOSE_DIR}/examples/ex01_inputfile/ex01.i
   *    :block: BCs    
   * 
   * 
   * Within each of the two sub-section, named "top" and "bottom" by the user, the boundary conditions
   * are linked to their associated variable(s) (i.e. "diffused" in this case) and boundaries.  In this
   * case, the mesh file **mug.e** defines labeled the boundaries "top" and "bottom" which we can refer
   * to. Boundaries will also often be specified by number IDs - depending on how your mesh file was
   * generated.
   * 
   * Note, the Neumann boundary conditions for this problem (on the left and right sides) are satisfied
   * implicitly and are not necessary for us to define. However, for non-zero Neumann or other boundary
   * conditions many built-in objects are provided by MOOSE (e.g., **NeumannBC**). You can also create
   * custom boundary conditions derived from the existing objects within MOOSE.
   * 
   * Executioner
   * ============
   * 
   * The type of problem to solve and the method for solving it is defined within the **Executioner**
   * block.  This problem is steady-state and will use the **Steady** Executioner and will use the
   * default solving method Preconditioned Jacobain Free Newton Krylov.
   * 
   * .. vnv-hive-code:: ${MOOSE_DIR}/examples/ex01_inputfile/ex01.i
   *    :block: Executioner
   * 
   * 
   * Outputs
   * ==========
   * 
   * Here two types of outputs are enabled: output to the screen (console) and output to an Exodus II
   * file (exodus).  Setting the "file_base" parameter is optional, in this example it forces the
   * output file to be named "out.e" ("e" is the extension used for the Exodus II format).
   * 
   * .. vnv-hive-code:: ${MOOSE_DIR}/examples/ex01_inputfile/ex01.i
   *    :block: Outputs
   *
   * 
   * Running the Problem
   * =====================
   * 
   * This example may be run using Peacock or by running the following commands form the command line.
   * 
   * .. vnv-code:: 
   * 
   *     cd ~/projects/moose/examples/ex01_inputfile
   *     make -j8
   *     ./ex01-opt -i ex01.i
   * 
   * 
   * This will generate the results file, out.e, as shown in [example-1-results]. This file may be viewed using
   * Peacock or an external application that supports the Exodus II format (e.g., Paraview).
   * 
   * 
   **/
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

  
  INJECTION_INITIALIZE(VNV_APP_NAME, &argc, &argv);
	  
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
