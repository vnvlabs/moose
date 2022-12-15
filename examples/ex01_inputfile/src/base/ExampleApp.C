//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

// MOOSE Includes
#include "ExampleApp.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "VnV.h"

VnVExampleApp::VnVExampleApp(ExampleApp *app) {
    
    /**
      * @title Building the Example Application Object.
      *
      * description: todo
      *
      **/
    INJECTION_LOOP_BEGIN_C(VNV_APP_NAME, VWORLD, BuildExampleApp, IPCALLBACK {
      if (type == VnV::InjectionPointType::Begin) {
      
      }
      else if (type == VnV::InjectionPointType::Iter) {
      
      } else {

      }
       
    }, app);
    
}

InputParameters
ExampleApp::validParams()
{
  InputParameters params = MooseApp::validParams();

  params.set<bool>("automatic_automatic_scaling") = false;

  return params;
}

ExampleApp::ExampleApp(InputParameters parameters) : VnVExampleApp(this), MooseApp(parameters)
{
  srand(processor_id());
  ExampleApp::registerAll(_factory, _action_factory, _syntax);
  INJECTION_LOOP_END(VNV_APP_NAME, BuildExampleApp);
}

void
ExampleApp::registerAll(Factory & f, ActionFactory & af, Syntax & /*s*/)
{

  /**
   * @title Registering Factories
   * 
   * Moose will now register all the factories to the Example Application. 
  */
  INJECTION_LOOP_BEGIN_C(MOOSE,VWORLD, RegisterFactories, IPCALLBACK {

  }, f );

  Registry::registerObjectsTo(f, {"ExampleApp"});
  Registry::registerActionsTo(af, {"ExampleApp"});

  INJECTION_LOOP_END(MOOSE, RegisterFactories);

  

}

void
ExampleApp::registerApps()
{
  registerApp(ExampleApp);
}
