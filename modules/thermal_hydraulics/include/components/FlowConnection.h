//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "Component.h"

/**
 * Base class for components that connect to flow channels (junctions and boundaries)
 */
class FlowConnection : public Component
{
public:
  FlowConnection(const InputParameters & params);

  /// End type
  enum EEndType
  {
    IN, ///< inlet
    OUT ///< outlet
  };
  /// Map of end type string to enum
  static const std::map<std::string, EEndType> _end_type_to_enum;

  /// Structure for holding data for a connection
  struct Connection
  {
    /// The name of the boundary this connection is attached to
    const BoundaryName _boundary_name;

    /// Name of the geometrical component in the connection
    const std::string _geometrical_component_name;

    /// End type for the connection
    const EEndType _end_type;

    Connection(const BoundaryName & boundary_name,
               const std::string & geometrical_component_name,
               const EEndType & end_type)
      : _boundary_name(boundary_name),
        _geometrical_component_name(geometrical_component_name),
        _end_type(end_type)
    {
    }
  };

  /**
   * Returns the vector of connections of this component
   *
   * @returns vector of connections of this component
   */
  const std::vector<Connection> & getConnections() const { return _connections; }

  /**
   * Returns a list of names of flow channels that are connected to this component
   *
   * @returns list of names of flow channels that are connected to this component
   */
  const std::vector<std::string> & getConnectedComponentNames() const
  {
    return _connected_component_names;
  }

  /**
   * Gets the vector of connected subdomain names
   */
  const std::vector<SubdomainName> & getConnectedSubdomainNames() const
  {
    return _connected_subdomain_names;
  }

  /**
   * Gets the list of boundary nodes connected to this component
   *
   * @return list of connected boundary nodes
   */
  virtual const std::vector<dof_id_type> & getNodeIDs() const;

  /**
   * Gets the boundary names for this component
   *
   * @return boundary names for this component
   */
  const std::vector<BoundaryName> & getBoundaryNames() const;

  /**
   * Gets the name of fluid properties used in all flow connections
   *
   * @return name of fluid properties used in all flow connections
   */
  const UserObjectName & getFluidPropertiesName() const;

protected:
  virtual void setupMesh() override;
  virtual void init() override;
  virtual void check() const override;

  /**
   * Adds a connection for this component
   *
   * Components using this interface must call this function on all of their
   * connection strings.
   *
   * @param[in] boundary_name   The name of the boundary
   */
  void addConnection(const BoundaryName & boundary_name);

  /**
   * Checks that the number of connections is equal to the supplied value
   *
   * @param[in] n_connections   enforced number of connections
   */
  void checkNumberOfConnections(const unsigned int & n_connections) const;

  /**
   * Checks that the size of a vector parameter equals the number of connections
   *
   * @tparam    T       type of element in the vector parameter
   * @param[in] param   vector parameter name
   */
  template <typename T>
  void checkSizeEqualsNumberOfConnections(const std::string & param) const;

  /**
   * Checks that all connections have the same of a certain type of object
   *
   * @tparam    T             type of object to check
   * @param[in] objects       list of objects corresponding to each connection
   * @param[in] description   description of the obect to check
   */
  template <typename T>
  void checkAllConnectionsHaveSame(const std::vector<T> & objects,
                                   const std::string & description) const;

  /// Physical positions of connected flow channels
  std::vector<Point> _positions;
  /// Boundary node IDs from connected flow channels
  std::vector<dof_id_type> _nodes;
  /// Boundary IDs of connected flow channels
  std::vector<unsigned int> _boundary_ids;
  /// Boundary names of connected flow channels
  std::vector<BoundaryName> _boundary_names;
  /// Outward normals associated with connected flow channels
  std::vector<Real> _normals;

  /// Convenience variable that stores model type
  THM::FlowModelID _flow_model_id;
  /// Flow model used in this connection
  std::shared_ptr<const FlowModel> _flow_model;
  /// The name of the fluid property user object
  UserObjectName _fp_name;
  /// Numerical flux user object names
  std::vector<UserObjectName> _numerical_flux_names;
  /// rDG interfacial variables user object names
  std::vector<UserObjectName> _rdg_int_var_uo_names;
  /// Vector of connections of this component
  std::vector<Connection> _connections;
  /// Vector of connected component names
  std::vector<std::string> _connected_component_names;
  /// Vector of subdomain names of the connected geometrical flow components
  std::vector<SubdomainName> _connected_subdomain_names;

public:
  static InputParameters validParams();
};

template <typename T>
void
FlowConnection::checkSizeEqualsNumberOfConnections(const std::string & param) const
{
  const auto & value = getParam<std::vector<T>>(param);
  if (value.size() != _connections.size())
    logError("The number of entries in '",
             param,
             "' (",
             value.size(),
             ") must equal the number of connections (",
             _connections.size(),
             ")");
}

template <typename T>
void
FlowConnection::checkAllConnectionsHaveSame(const std::vector<T> & objects,
                                            const std::string & description) const
{
  for (const auto & obj : objects)
    if (obj != objects[0])
      logError("All connections must have the same ", description);
}

namespace THM
{
template <>
FlowConnection::EEndType stringToEnum(const std::string & s);
}
