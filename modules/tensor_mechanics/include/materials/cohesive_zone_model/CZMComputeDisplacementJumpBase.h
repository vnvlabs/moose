//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "InterfaceMaterial.h"
/**
 * This interface material class computes the displacement jump in the interface natural coordinate
 * system. The transformation between local and global coordinates shall be defined in
 * computeLocalDisplacementJump.
 */
class CZMComputeDisplacementJumpBase : public InterfaceMaterial
{
public:
  static InputParameters validParams();
  CZMComputeDisplacementJumpBase(const InputParameters & parameters);

protected:
  void computeQpProperties() override;
  void initQpStatefulProperties() override;

  /// method used to compute the disaplcement jump in interface coordinates according to a
  ///  specific kinematic formulation
  virtual void computeLocalDisplacementJump() = 0;

  /// method computing the required rotation matrices
  virtual void computeRotationMatrices();

  /// Base name of the material system
  const std::string _base_name;

  /// the interface normal in the undeformed configuration
  const MooseArray<Point> & _normals;

  /// number of displacement components
  const unsigned int _ndisp;

  /// the coupled displacement and neighbor displacement values
  ///@{
  std::vector<const VariableValue *> _disp;
  std::vector<const VariableValue *> _disp_neighbor;
  ///@}

  /// the displacement jump in global and interface coordiantes
  ///@{
  MaterialProperty<RealVectorValue> & _displacement_jump_global;
  MaterialProperty<RealVectorValue> & _interface_displacement_jump;
  ///@}

  /// the rotation matrix transforming from the interface to the global coordinate systems
  MaterialProperty<RankTwoTensor> & _czm_total_rotation;
};
