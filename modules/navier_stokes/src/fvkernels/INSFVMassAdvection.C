//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "INSFVMassAdvection.h"
#include "NS.h"

registerMooseObject("NavierStokesApp", INSFVMassAdvection);

InputParameters
INSFVMassAdvection::validParams()
{
  auto params = INSFVAdvectionKernel::validParams();
  params.addClassDescription("Object for advecting mass, e.g. rho");
  params.addRequiredParam<MooseFunctorName>(NS::density, "Density functor");
  return params;
}

INSFVMassAdvection::INSFVMassAdvection(const InputParameters & params)
  : INSFVAdvectionKernel(params), _rho(getFunctor<ADReal>(NS::density))
{
#ifndef MOOSE_GLOBAL_AD_INDEXING
  mooseError("INSFV is not supported by local AD indexing. In order to use INSFV, please run the "
             "configure script in the root MOOSE directory with the configure option "
             "'--with-ad-indexing-type=global'");
#endif
}

ADReal
INSFVMassAdvection::computeQpResidual()
{
  ADReal rho_interface;

  const auto elem_face = elemFromFace();
  const auto neighbor_face = neighborFromFace();

  const auto v = _rc_vel_provider.getVelocity(_velocity_interp_method, *_face_info, _tid);
  Moose::FV::interpolate(_advected_interp_method,
                         rho_interface,
                         _rho(elem_face),
                         _rho(neighbor_face),
                         v,
                         *_face_info,
                         true);
  return _normal * v * rho_interface;
}
