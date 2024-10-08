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
    
   /** Constructing the Example Application
     * ------------------------------------
     * 
     * This text is a VnV placeholder. It plots a random graph. This should be
     * updated with a description of what is happening inside this injection point
     * and/or test. 
     * 
     * .. vnv-chart::
     * 
     *    {
     *       "type" : "line",
     *       "data" : {
     *          "labels" : {{as_json(rand_nums(`100`))}},
     *          "datasets" : [{
     *             "label": "Random Data",
     *             "backgroundColor": "rgb(57, 105, 160)",
     *             "borderColor": "rgb(57, 105, 160)",
     *             "data": {{as_json(rand_nums(`100`))}}
     *           }]
     *       }
     *       
     *    }
     * 
     **/ 
    INJECTION_LOOP_BEGIN(VNV_APP_NAME, VWORLD, BuildExampleApp, VNV_CALLBACK {
       
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
  INJECTION_LOOP_END(VNV_APP_NAME, BuildExampleApp,VNV_NOCALLBACK);
}

void
ExampleApp::registerAll(Factory & f, ActionFactory & af, Syntax & /*s*/)
{

 /** Registering Moose Actions
   * --------------------------
   * 
   * This text is a VnV placeholder. It plots a random graph. This should be
   * updated with a description of what is happening inside this injection point
   * and/or test. 
   * 
   * .. vnv-chart::
   * 
   *    {
   *       "type" : "line",
   *       "data" : {
   *          "labels" : {{as_json(rand_nums(`100`))}},
   *          "datasets" : [{
   *             "label": "Random Data",
   *             "backgroundColor": "rgb(57, 105, 160)",
   *             "borderColor": "rgb(57, 105, 160)",
   *             "data": {{as_json(rand_nums(`100`))}}
   *           }]
   *       }
   *       
   *    }
   * 
   **/
  INJECTION_LOOP_BEGIN(MOOSE,VWORLD, RegisterFactories, VNV_CALLBACK {

  }, f );

  Registry::registerObjectsTo(f, {"ExampleApp"});
  Registry::registerActionsTo(af, {"ExampleApp"});

  INJECTION_LOOP_END(MOOSE, RegisterFactories,VNV_NOCALLBACK);

  

}

void
ExampleApp::registerApps()
{
  registerApp(ExampleApp);
}
