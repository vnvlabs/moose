/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#include "LevelSetCutUserObject.h"
#include "SubProblem.h"
#include "MooseVariable.h"
#include "libmesh/string_to_enum.h"

template <>
InputParameters
validParams<LevelSetCutUserObject>()
{
  InputParameters params = validParams<GeometricCutUserObject>();
  params.addRequiredParam<VariableName>(
      "level_set_var", "The name of level set variable used to represent the interface");
  params.addClassDescription("XFEM mesh cut by level set function");
  return params;
}

LevelSetCutUserObject::LevelSetCutUserObject(const InputParameters & parameters)
  : GeometricCutUserObject(parameters),
    _level_set_var_number(
        _subproblem.getVariable(_tid, parameters.get<VariableName>("level_set_var")).number()),
    _system(_subproblem.getSystem(getParam<VariableName>("level_set_var"))),
    _solution(_system.current_local_solution.get())
{
}

bool
LevelSetCutUserObject::cutElementByGeometry(const Elem * elem,
                                            std::vector<Xfem::CutEdge> & cut_edges,
                                            std::vector<Xfem::CutNode> & /*cut_nodes*/,
                                            Real /*time*/) const
{
  bool cut_elem = false;

  unsigned int n_sides = elem->n_sides();

  for (unsigned int i = 0; i < n_sides; ++i)
  {
    UniquePtr<Elem> curr_side = elem->side(i);

    if (curr_side->type() != EDGE2)
      mooseError("In LevelSetCutUserObject element side must be EDGE2, but type is: ",
                 libMesh::Utility::enum_to_string(curr_side->type()),
                 " base element type is: ",
                 libMesh::Utility::enum_to_string(elem->type()));

    const Node * node1 = curr_side->get_node(0);
    const Node * node2 = curr_side->get_node(1);

    dof_id_type ls_dof_id_1 = node1->dof_number(_system.number(), _level_set_var_number, 0);
    dof_id_type ls_dof_id_2 = node2->dof_number(_system.number(), _level_set_var_number, 0);

    Number ls_node_1 = (*_solution)(ls_dof_id_1);
    Number ls_node_2 = (*_solution)(ls_dof_id_2);

    if (ls_node_1 * ls_node_2 < 0)
    {
      cut_elem = true;
      Xfem::CutEdge mycut;
      mycut._id1 = node1->id();
      mycut._id2 = node2->id();
      Real seg_int_frac = std::abs(ls_node_1) / std::abs(ls_node_1 - ls_node_2);
      mycut._distance = seg_int_frac;
      mycut._host_side_id = i;
      cut_edges.push_back(mycut);
    }
  }

  return cut_elem;
}

bool
LevelSetCutUserObject::cutElementByGeometry(const Elem * elem,
                                            std::vector<Xfem::CutFace> & cut_faces,
                                            Real /*time*/) const
{
  bool cut_elem = false;

  for (unsigned int i = 0; i < elem->n_sides(); ++i)
  {
    std::unique_ptr<Elem> curr_side = elem->side(i);
    if (curr_side->dim() != 2)
      mooseError("In LevelSetCutUserObject dimension of side must be 2, but it is ",
                 curr_side->dim());
    unsigned int n_edges = curr_side->n_sides();

    std::vector<unsigned int> cut_edges;
    std::vector<Real> cut_pos;

    for (unsigned int j = 0; j < n_edges; j++)
    {
      // This returns the lowest-order type of side.
      std::unique_ptr<Elem> curr_edge = curr_side->side(j);
      if (curr_edge->type() != EDGE2)
        mooseError("In LevelSetCutUserObject face edge must be EDGE2, but type is: ",
                   libMesh::Utility::enum_to_string(curr_edge->type()),
                   " base element type is: ",
                   libMesh::Utility::enum_to_string(elem->type()));

      const Node * node1 = curr_edge->get_node(0);
      const Node * node2 = curr_edge->get_node(1);

      dof_id_type ls_dof_id_1 = node1->dof_number(_system.number(), _level_set_var_number, 0);
      dof_id_type ls_dof_id_2 = node2->dof_number(_system.number(), _level_set_var_number, 0);

      Number ls_node_1 = (*_solution)(ls_dof_id_1);
      Number ls_node_2 = (*_solution)(ls_dof_id_2);

      if (ls_node_1 * ls_node_2 < 0)
      {
        Real seg_int_frac = std::abs(ls_node_1) / std::abs(ls_node_1 - ls_node_2);
        cut_edges.push_back(j);
        cut_pos.push_back(seg_int_frac);
      }
    }

    if (cut_edges.size() == 2)
    {
      cut_elem = true;
      Xfem::CutFace mycut;
      mycut._face_id = i;
      mycut._face_edge.push_back(cut_edges[0]);
      mycut._face_edge.push_back(cut_edges[1]);
      mycut._position.push_back(cut_pos[0]);
      mycut._position.push_back(cut_pos[1]);
      cut_faces.push_back(mycut);
    }
  }
  return cut_elem;
}

bool
LevelSetCutUserObject::cutFragmentByGeometry(std::vector<std::vector<Point>> & /*frag_edges*/,
                                             std::vector<Xfem::CutEdge> & /*cut_edges*/,
                                             Real /*time*/) const
{
  return false;
}

bool
LevelSetCutUserObject::cutFragmentByGeometry(std::vector<std::vector<Point>> & /*frag_faces*/,
                                             std::vector<Xfem::CutFace> & /*cut_faces*/,
                                             Real /*time*/) const
{
  mooseError("cutFragmentByGeometry not yet implemented for 3d level set cutting");
  return false;
}

const std::vector<Point>
LevelSetCutUserObject::getCrackFrontPoints(unsigned int /*num_crack_front_points*/) const
{
  mooseError("getCrackFrontPoints() is not implemented for this object.");
}