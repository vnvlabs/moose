//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "StitchedMeshGenerator.h"

#include "CastUniquePointer.h"
#include "MooseUtils.h"

#include "libmesh/replicated_mesh.h"

registerMooseObject("MooseApp", StitchedMeshGenerator);

InputParameters
StitchedMeshGenerator::validParams()
{
  InputParameters params = MeshGenerator::validParams();

  MooseEnum algorithm("BINARY EXHAUSTIVE", "BINARY");

  params.addRequiredParam<std::vector<MeshGeneratorName>>("inputs", "The input MeshGenerators.");
  params.addParam<bool>(
      "clear_stitched_boundary_ids", true, "Whether or not to clear the stitched boundary IDs");
  params.addRequiredParam<std::vector<std::vector<std::string>>>(
      "stitch_boundaries_pairs",
      "Pairs of boundaries to be stitched together between the 1st mesh in inputs and each "
      "consecutive mesh");
  params.addParam<MooseEnum>(
      "algorithm",
      algorithm,
      "Control the use of binary search for the nodes of the stitched surfaces.");
  params.addClassDescription(
      "Allows multiple mesh files to be stiched together to form a single mesh.");

  return params;
}

StitchedMeshGenerator::StitchedMeshGenerator(const InputParameters & parameters)
  : MeshGenerator(parameters),
    _mesh_ptrs(getMeshes("inputs")),
    _input_names(getParam<std::vector<MeshGeneratorName>>("inputs")),
    _clear_stitched_boundary_ids(getParam<bool>("clear_stitched_boundary_ids")),
    _stitch_boundaries_pairs(
        getParam<std::vector<std::vector<std::string>>>("stitch_boundaries_pairs")),
    _algorithm(parameters.get<MooseEnum>("algorithm"))
{
}

std::unique_ptr<MeshBase>
StitchedMeshGenerator::generate()
{
  // We put the first mesh in a local pointer
  std::unique_ptr<ReplicatedMesh> mesh = dynamic_pointer_cast<ReplicatedMesh>(*_mesh_ptrs[0]);

  // Reserve spaces for the other meshes (no need to store the first one another time)
  std::vector<std::unique_ptr<ReplicatedMesh>> meshes(_mesh_ptrs.size() - 1);

  // Read in all of the other meshes
  for (MooseIndex(_mesh_ptrs) i = 1; i < _mesh_ptrs.size(); ++i)
    meshes[i - 1] = dynamic_pointer_cast<ReplicatedMesh>(*_mesh_ptrs[i]);

  // Stitch all the meshes to the first one
  for (MooseIndex(meshes) i = 0; i < meshes.size(); i++)
  {
    auto boundary_pair = _stitch_boundaries_pairs[i];

    boundary_id_type first, second;

    try
    {
      first = MooseUtils::convert<boundary_id_type>(boundary_pair[0], true);
    }
    catch (...)
    {
      first = mesh->get_boundary_info().get_id_by_name(boundary_pair[0]);

      if (first == BoundaryInfo::invalid_id)
      {
        std::stringstream error;

        error << "Boundary " << boundary_pair[0] << " doesn't exist on the first mesh in " << name()
              << "\n";
        error << "Boundary names that do exist: \n";
        error << " ID : Name\n";

        auto & sideset_id_name_map = mesh->get_boundary_info().get_sideset_name_map();

        for (auto & ss_name_map_pair : sideset_id_name_map)
          error << " " << ss_name_map_pair.first << " : " << ss_name_map_pair.second << "\n";

        paramError("stitch_boundaries_pairs", error.str());
      }
    }

    try
    {
      second = MooseUtils::convert<boundary_id_type>(boundary_pair[1], true);
    }
    catch (...)
    {
      second = meshes[i]->get_boundary_info().get_id_by_name(boundary_pair[1]);

      if (second == BoundaryInfo::invalid_id)
      {
        meshes[i]->print_info();

        std::stringstream error;

        error << "Boundary " << boundary_pair[1] << " doesn't exist on mesh " << i + 1 << " in "
              << name() << "\n";
        error << "Boundary names that do exist: \n";
        error << " ID : Name\n";

        auto & sideset_id_name_map = meshes[i]->get_boundary_info().get_sideset_name_map();

        for (auto & ss_name_map_pair : sideset_id_name_map)
          error << " " << ss_name_map_pair.first << " : " << ss_name_map_pair.second << "\n";

        paramError("stitch_boundaries_pairs", error.str());
      }
    }

    const bool use_binary_search = (_algorithm == "BINARY");

    mesh->stitch_meshes(*meshes[i],
                        first,
                        second,
                        TOLERANCE,
                        _clear_stitched_boundary_ids,
                        /*verbose = */ true,
                        use_binary_search);
  }

  return dynamic_pointer_cast<MeshBase>(mesh);
}
