//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "SideDiffusiveFluxIntegral.h"

#include "metaphysicl/raw_type.h"

registerMooseObject("MooseApp", SideDiffusiveFluxIntegral);
registerMooseObject("MooseApp", ADSideDiffusiveFluxIntegral);
registerMooseObject("MooseApp", SideVectorDiffusivityFluxIntegral);
registerMooseObject("MooseApp", ADSideVectorDiffusivityFluxIntegral);
registerMooseObjectRenamed("MooseApp",
                           SideFluxIntegral,
                           "06/30/2021 24:00",
                           SideDiffusiveFluxIntegral);
registerMooseObjectRenamed("MooseApp",
                           ADSideFluxIntegral,
                           "06/30/2021 24:00",
                           ADSideDiffusiveFluxIntegral);

template <bool is_ad, typename T>
InputParameters
SideDiffusiveFluxIntegralTempl<is_ad, T>::validParams()
{
  InputParameters params = SideIntegralVariablePostprocessor::validParams();
  params.addRequiredParam<MaterialPropertyName>(
      "diffusivity",
      "The name of the diffusivity material property that will be used in the flux computation.");
  params.addClassDescription(
      "Computes the integral of the diffusive flux over the specified boundary");
  return params;
}

template <bool is_ad, typename T>
SideDiffusiveFluxIntegralTempl<is_ad, T>::SideDiffusiveFluxIntegralTempl(
    const InputParameters & parameters)
  : SideIntegralVariablePostprocessor(parameters),
    _diffusivity(getParam<MaterialPropertyName>("diffusivity")),
    _diffusion_coef(getGenericMaterialProperty<T, is_ad>(_diffusivity))
{
}

template <bool is_ad, typename T>
Real
SideDiffusiveFluxIntegralTempl<is_ad, T>::computeQpIntegral()
{
  if (_fv)
  {
    // Get the face info
    const FaceInfo * const fi = _mesh.faceInfo(_current_elem, _current_side);
    mooseAssert(fi, "We should have a face info");

    // Get the gradient of the variable on the face
    const auto & grad_u = MetaPhysicL::raw_value(_fv_variable->adGradSln(*fi));

    // FIXME Get the diffusion coefficient on the face, see #16809
    return -diffusivityGradientProduct(grad_u, MetaPhysicL::raw_value(_diffusion_coef[_qp])) *
           _normals[_qp];
  }
  else
    return -diffusivityGradientProduct(_grad_u[_qp], MetaPhysicL::raw_value(_diffusion_coef[_qp])) *
           _normals[_qp];
}

template <bool is_ad, typename T>
RealVectorValue
SideDiffusiveFluxIntegralTempl<is_ad, T>::diffusivityGradientProduct(const RealVectorValue & grad_u,
                                                                     const Real diffusivity)
{
  return grad_u * diffusivity;
}

template <bool is_ad, typename T>
RealVectorValue
SideDiffusiveFluxIntegralTempl<is_ad, T>::diffusivityGradientProduct(
    const RealVectorValue & grad_u, const RealVectorValue & diffusivity)
{
  RealVectorValue d_grad_u = grad_u;
  for (unsigned int i = 0; i < LIBMESH_DIM; i++)
    d_grad_u(i) *= diffusivity(i);

  return d_grad_u;
}

template class SideDiffusiveFluxIntegralTempl<false, Real>;
template class SideDiffusiveFluxIntegralTempl<true, Real>;
template class SideDiffusiveFluxIntegralTempl<false, RealVectorValue>;
template class SideDiffusiveFluxIntegralTempl<true, RealVectorValue>;
