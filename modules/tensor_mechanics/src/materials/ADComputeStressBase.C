//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "ADComputeStressBase.h"
#include "RankTwoTensor.h"
#include "RankFourTensor.h"

InputParameters
ADComputeStressBase::validParams()
{
  InputParameters params = Material::validParams();
  params.addParam<std::string>("base_name",
                               "Optional parameter that allows the user to define "
                               "multiple mechanics material systems on the same "
                               "block, i.e. for multiple phases");
  params.suppressParameter<bool>("use_displaced_mesh");
  params.addParam<std::vector<MaterialPropertyName>>(
      "extra_stress_names",
      std::vector<MaterialPropertyName>(),
      "Material property names of rank two tensors to be added to the stress.");
  return params;
}

ADComputeStressBase::ADComputeStressBase(const InputParameters & parameters)
  : Material(parameters),
    _base_name(isParamValid("base_name") ? getParam<std::string>("base_name") + "_" : ""),
    _mechanical_strain(getADMaterialProperty<RankTwoTensor>(_base_name + "mechanical_strain")),
    _stress(declareADProperty<RankTwoTensor>(_base_name + "stress")),
    _elastic_strain(declareADProperty<RankTwoTensor>(_base_name + "elastic_strain")),
    _extra_stresses(getParam<std::vector<MaterialPropertyName>>("extra_stress_names").size())
{
  if (getParam<bool>("use_displaced_mesh"))
    mooseError("The stress calculator needs to run on the undisplaced mesh.");

  const std::vector<MaterialPropertyName> extra_stress_names =
      getParam<std::vector<MaterialPropertyName>>("extra_stress_names");
  for (MooseIndex(_extra_stresses) i = 0; i < _extra_stresses.size(); ++i)
    _extra_stresses[i] = &getMaterialProperty<RankTwoTensor>(extra_stress_names[i]);
}

void
ADComputeStressBase::initQpStatefulProperties()
{
  _elastic_strain[_qp].zero();
  _stress[_qp].zero();
}

void
ADComputeStressBase::computeQpProperties()
{
  computeQpStress();

  // Add in extra stress
  for (MooseIndex(_extra_stresses) i = 0; i < _extra_stresses.size(); ++i)
    _stress[_qp] += (*_extra_stresses[i])[_qp];
}
