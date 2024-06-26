//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "MaterialStdVectorAux.h"

registerMooseObject("MooseApp", MaterialStdVectorAux);

InputParameters
MaterialStdVectorAux::validParams()
{
  InputParameters params = MaterialStdVectorAuxBase<>::validParams();
  params.addClassDescription("Extracts a component of a material type std::vector<Real> to an aux "
                             "variable.  If the std::vector is not of sufficient size then zero is "
                             "returned");
  params.addParam<unsigned int>(
      "selected_qp",
      "Evaluate the std::vector<Real> at this quadpoint.  This only needs to be "
      "used if you are interested in a particular quadpoint in each element: "
      "otherwise do not include this parameter in your input file");
  params.addParamNamesToGroup("selected_qp", "Advanced");
  return params;
}

MaterialStdVectorAux::MaterialStdVectorAux(const InputParameters & parameters)
  : MaterialStdVectorAuxBase<Real>(parameters),
    _has_selected_qp(isParamValid("selected_qp")),
    _selected_qp(_has_selected_qp ? getParam<unsigned int>("selected_qp") : 0)
{
}

Real
MaterialStdVectorAux::getRealValue()
{
  if (_has_selected_qp)
  {
    if (_selected_qp >= _q_point.size())
    {
      Threads::spin_mutex::scoped_lock lock(Threads::spin_mtx);
      mooseError("MaterialStdVectorAux.  selected_qp specified as ",
                 _selected_qp,
                 " but there are only ",
                 _q_point.size(),
                 " quadpoints in the element");
    }

    return _prop[_selected_qp][_index];
  }
  return _prop[_qp][_index];
}
