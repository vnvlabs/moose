//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "FreeBoundary.h"

registerMooseObject("ThermalHydraulicsApp", FreeBoundary);

InputParameters
FreeBoundary::validParams()
{
  InputParameters params = FlowConnection::validParams();
  return params;
}

FreeBoundary::FreeBoundary(const InputParameters & parameters) : FlowConnection(parameters)
{
  logError("Deprecated component. Use FreeBoundary1Phase or FreeBoundary2Phase instead.");
}
