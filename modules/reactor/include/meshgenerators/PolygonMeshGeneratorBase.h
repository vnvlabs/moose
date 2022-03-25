//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "MeshGenerator.h"
#include "MooseEnum.h"
#include "CastUniquePointer.h"
#include "MooseMeshUtils.h"
#include "libmesh/replicated_mesh.h"
#include "libmesh/mesh_modification.h"
#include "libmesh/face_quad4.h"
#include "libmesh/face_tri3.h"
#include "libmesh/serial_mesh.h"
#include "libmesh/boundary_info.h"
#include "libmesh/utility.h"

/**
 * A base class that contains common members for Reactor module mesh generators.
 */
class PolygonMeshGeneratorBase : public MeshGenerator
{
public:
  static InputParameters validParams();

  PolygonMeshGeneratorBase(const InputParameters & parameters);

  virtual std::unique_ptr<MeshBase> generate() override;

  enum MESH_TYPE
  {
    CORNER_MESH = 1,
    BOUNDARY_MESH = 2,
    INNER_MESH = 3
  };

  enum RETURN_TYPE
  {
    ANGLE_DEGREE = 1,
    ANGLE_TANGENT = 2
  };

  enum INTRISIC_SUBDOMAIN_ID : subdomain_id_type
  {
    PERIPHERAL_ID_SHIFT = 1000
  };
  // boundary_id_type is short int so max is 32,767
  enum INTRINSIC_SIDESET_ID : boundary_id_type
  {
    OUTER_SIDESET_ID = 10000,
    OUTER_SIDESET_ID_ALT = 15000,
    SLICE_BEGIN = 30000,
    SLICE_END = 31000,
    SLICE_ALT = 30500
  };

  enum INTRINSIC_NUM_SIDES
  {
    HEXAGON_NUM_SIDES = 6
  };

protected:
  /**
   * Creates a mesh of a slice that corresponds to a single side of the polygon to be generated.
   * @param mesh input mesh to build the slice mesh onto
   * @param ring_radii radii of the ring regions
   * @param rings numbers of radial intervals of the ring regions
   * @param ring_radial_biases values used for radial meshing biasing in ring regions
   * @param ring_inner_boundary_layer_fractions fraction of the ring regions to be used as inner
   * boundary layers
   * @param ring_inner_boundary_layer_intervals number of radial sectors of the inner boundary
   * layers meshes of the ring regions
   * @param ring_inner_boundary_layer_biases growth factors used to bias radial meshing of the inner
   * boundary layers of the ring region
   * @param ring_outer_boundary_layer_fractions fraction of the ring regions to be used as outer
   * boundary layers
   * @param ring_outer_boundary_layer_intervals number of radial sectors of the outer boundary
   * layers meshes of the ring regions
   * @param ring_outer_boundary_layer_biases growth factors used to bias radial meshing of the outer
   * boundary layers of the ring region
   * @param ducts_center_dist distance parameters of the duct regions
   * @param ducts_layers numbers of radial intervals of the duct regions
   * @param duct_radial_biases values used for radial meshing biasing in duct regions
   * @param duct_inner_boundary_layer_fractions fraction of the duct regions to be used as inner
   * boundary layers
   * @param duct_inner_boundary_layer_intervals number of radial sectors of the inner boundary
   * layers meshes of the duct regions
   * @param duct_inner_boundary_layer_biases growth factors used to bias radial meshing of the inner
   * boundary layers of the duct region
   * @param duct_outer_boundary_layer_fractions fraction of the duct regions to be used as outer
   * boundary layers
   * @param duct_outer_boundary_layer_intervals number of radial sectors of the outer boundary
   * layers meshes of the duct regions
   * @param duct_outer_boundary_layer_biases growth factors used to bias radial meshing of the outer
   * boundary layers of the duct region
   * @param has_rings whether the slice contains ring regions or not
   * @param has_ducts whether the slice contains duct regions or not
   * @param num_sectors_per_side number of azimuthal intervals
   * @param background_intervals number of radial intervals of the background region
   * @param background_radial_bias value used for radial meshing biasing in background region
   * @param background_inner_boundary_layer_width width of the background region to be used as
   * inner boundary layer
   * @param background_inner_boundary_layer_intervals number of radial sectors of the inner boundary
   * layer mesh of the background region
   * @param background_inner_boundary_layer_bias growth factor used to bias radial meshing of the
   * inner boundary layer of the background region
   * @param background_outer_boundary_layer_width width of the background region to be used as
   * outer boundary layer
   * @param background_outer_boundary_layer_intervals number of radial sectors of the outer boundary
   * layer mesh of the background region
   * @param background_outer_boundary_layer_bias growth factor used to bias radial meshing of the
   * outer boundary layer of the background region
   * @param node_id_background_meta pointer to the first node's id of the background region
   * @param side_number number of sides of the polygon
   * @param side_index index of the polygon side
   * @param azimuthal_tangent vector of tangent values of the azimuthal angles as reference for
   * adaptive boundary matching
   * @param block_id_shift shift of the subdomain ids generated by this function
   * @param quad_center_elements whether the central region contrains quad elements or not
   * @param boundary_id_shift shift of the interface boundary ids
   * @return a mesh of a polygon slice
   */
  std::unique_ptr<ReplicatedMesh>
  buildSimpleSlice(const std::vector<Real> ring_radii,
                   const std::vector<unsigned int> rings,
                   const std::vector<Real> ring_radial_biases,
                   const std::vector<Real> ring_inner_boundary_layer_fractions,
                   const std::vector<unsigned int> ring_inner_boundary_layer_intervals,
                   const std::vector<Real> ring_inner_boundary_layer_biases,
                   const std::vector<Real> ring_outer_boundary_layer_fractions,
                   const std::vector<unsigned int> ring_outer_boundary_layer_intervals,
                   const std::vector<Real> ring_outer_boundary_layer_biases,
                   std::vector<Real> ducts_center_dist,
                   const std::vector<unsigned int> ducts_layers,
                   const std::vector<Real> duct_radial_biases,
                   const std::vector<Real> duct_inner_boundary_layer_fractions,
                   const std::vector<unsigned int> duct_inner_boundary_layer_intervals,
                   const std::vector<Real> duct_inner_boundary_layer_biases,
                   const std::vector<Real> duct_outer_boundary_layer_fractions,
                   const std::vector<unsigned int> duct_outer_boundary_layer_intervals,
                   const std::vector<Real> duct_outer_boundary_layer_biases,
                   const bool has_rings,
                   const bool has_ducts,
                   const Real pitch,
                   const unsigned int num_sectors_per_side,
                   const unsigned int background_intervals,
                   const Real background_radial_bias,
                   const Real background_inner_boundary_layer_width,
                   const unsigned int background_inner_boundary_layer_intervals,
                   const Real background_inner_boundary_layer_bias,
                   const Real background_outer_boundary_layer_width,
                   const unsigned int background_outer_boundary_layer_intervals,
                   const Real background_outer_boundary_layer_bias,
                   dof_id_type & node_id_background_meta,
                   const unsigned int side_number,
                   const unsigned int side_index,
                   const std::vector<Real> azimuthal_tangent = std::vector<Real>(),
                   const subdomain_id_type block_id_shift = 0,
                   const bool quad_center_elements = false,
                   const boundary_id_type boundary_id_shift = 0);

  /**
   * Creates nodes of the very central mesh layer of the polygon for quad central elements.
   * @param mesh input mesh to add the nodes onto
   * @param side_number number of sides of the polygon
   * @param div_num division number of the central mesh layer
   * @param ring_radii_0 radius of the central mesh layer
   * @param nodes pointer to the mesh's nodes
   * @param nodes vector that contains the nodes with basic geometry information
   */
  void centerNodes(ReplicatedMesh & mesh,
                   const unsigned int side_number,
                   const unsigned int div_num,
                   const Real ring_radii_0,
                   std::vector<std::vector<Node *>> & nodes) const;

  /**
   * Creates nodes for the ring-geometry region of a single slice.
   * @param mesh input mesh to add the nodes onto
   * @param ring_radii radii of the ring regions
   * @param rings numbers of radial intervals of the ring regions
   * @param biased_terms normalized spacing values used for radial meshing biasing in ring regions
   * @param num_sectors_per_side number of azimuthal intervals
   * @param corner_p[2][2] array contains the coordinates of the corner positions
   * @param corner_to_corner diameter of the circumscribed circle of the polygon
   * @param azimuthal_tangent vector of tangent values of the azimuthal angles as reference for
   * adaptive boundary matching
   */
  void ringNodes(ReplicatedMesh & mesh,
                 const std::vector<Real> ring_radii,
                 const std::vector<unsigned int> rings,
                 const std::vector<std::vector<Real>> biased_terms,
                 const unsigned int num_sectors_per_side,
                 const Real corner_p[2][2],
                 const Real corner_to_corner,
                 const std::vector<Real> azimuthal_tangent = std::vector<Real>()) const;

  /**
   * Creates nodes for the ring-to-polygon transition region (i.e., background) of a single slice.
   * @param mesh input mesh to add the nodes onto
   * @param num_sectors_per_side number of azimuthal intervals
   * @param background_intervals number of radial intervals of the background region
   * @param biased_terms normalized spacing values used for radial meshing biasing in background
   * region
   * @param background_corner_distance center to duct (innermost duct) corner distance
   * @param background_corner_radial_interval_length radial interval distance
   * @param corner_p[2][2] array contains the coordinates of the corner positions
   * @param corner_to_corner diameter of the circumscribed circle of the polygon
   * @param background_in radius of the inner boundary of the background region
   * @param azimuthal_tangent vector of tangent values of the azimuthal angles as reference for
   * adaptive boundary matching
   * @return a mesh with background region nodes created
   */
  void backgroundNodes(ReplicatedMesh & mesh,
                       const unsigned int num_sectors_per_side,
                       const unsigned int background_intervals,
                       const std::vector<Real> biased_terms,
                       const Real background_corner_distance,
                       const Real background_corner_radial_interval_length,
                       const Real corner_p[2][2],
                       const Real corner_to_corner,
                       const Real background_in,
                       const std::vector<Real> azimuthal_tangent = std::vector<Real>()) const;

  /**
   * Creates nodes for the duct-geometry region of a single slice.
   * @param mesh input mesh to add the nodes onto
   * @param ducts_center_dist distance parameters of the duct regions
   * @param ducts_layers numbers of radial intervals of the duct regions
   * @param biased_terms normalized spacing values used for radial meshing biasing in duct region
   * @param num_sectors_per_side number of azimuthal intervals
   * @param corner_p[2][2] array contains the coordinates of the corner positions
   * @param corner_to_corner diameter of the circumscribed circle of the polygon
   * @param azimuthal_tangent vector of tangent values of the azimuthal angles as reference for
   * adaptive boundary matching
   */
  void ductNodes(ReplicatedMesh & mesh,
                 std::vector<Real> * const ducts_center_dist,
                 const std::vector<unsigned int> ducts_layers,
                 const std::vector<std::vector<Real>> biased_terms,
                 const unsigned int num_sectors_per_side,
                 const Real corner_p[2][2],
                 const Real corner_to_corner,
                 const std::vector<Real> azimuthal_tangent = std::vector<Real>()) const;

  /**
   * Defines quad elements in the very central region of the polygon.
   * @param mesh input mesh to create the elements onto
   * @param div_num division number of the central mesh layer
   * @param block_id_shift shift of the subdomain ids generated by this function
   * @param boundary_id_shift shift of the interface boundary ids
   * @param id_array pointer to a vector that contains the node_ids with basic geometry information
   * @param assign_external_boundary whether the external boundary ids are assigned
   * @param side_index index of the polygon side (only used if external boundary ids are assigned)
   */
  void cenQuadElemDef(ReplicatedMesh & mesh,
                      const unsigned int div_num,
                      const subdomain_id_type block_id_shift,
                      const boundary_id_type boundary_id_shift,
                      std::vector<std::vector<Node *>> & nodes,
                      const bool assign_external_boundary = false,
                      const unsigned int side_index = 0) const;

  /**
   * Defines triangular elements in the very central region of the polygon.
   * @param mesh input mesh to create the elements onto
   * @param num_sectors_per_side number of azimuthal intervals
   * @param azimuthal_tangent vector of tangent values of the azimuthal angles as reference for
   * adaptive boundary matching
   * @param block_id_shift shift of the subdomain ids generated by this function
   * @param boundary_id_shift shift of the interface boundary ids
   * @param assign_external_boundary whether the external boundary ids are assigned
   * @param side_index index of the polygon side (only used if external boundary ids are assigned)
   */
  void cenTriElemDef(ReplicatedMesh & mesh,
                     const unsigned int num_sectors_per_side,
                     const std::vector<Real> azimuthal_tangent = std::vector<Real>(),
                     const subdomain_id_type block_id_shift = 0,
                     const boundary_id_type boundary_id_shift = 0,
                     const bool assign_external_boundary = false,
                     const unsigned int side_index = 0) const;

  /**
   * Defines general quad elements for the polygon.
   * @param mesh input mesh to create the elements onto
   * @param num_sectors_per_side number of azimuthal intervals
   * @param subdomain_rings numbers of radial intervals of all involved subdomain layers
   * @param side_index index of the polygon side
   * @param azimuthal_tangent vector of tangent values of the azimuthal angles as reference for
   * adaptive boundary matching
   * @param block_id_shift shift of the subdomain ids generated by this function
   * @param nodeid_shift shift of the node_ids of these elements
   * @param boundary_id_shift shift of the interface boundary ids
   */
  void quadElemDef(ReplicatedMesh & mesh,
                   const unsigned int num_sectors_per_side,
                   const std::vector<unsigned int> subdomain_rings,
                   const unsigned int side_index,
                   const std::vector<Real> azimuthal_tangent = std::vector<Real>(),
                   const subdomain_id_type block_id_shift = 0,
                   const dof_id_type nodeid_shift = 0,
                   const boundary_id_type boundary_id_shift = 0) const;

  /**
   * Makes radial correction to preserve ring area.
   * @param azimuthal_list azimuthal angles of all the nodes on the circle
   * @return a correction factor to preserve the area of the circle after polygonization during
   * meshing
   */
  Real radiusCorrectionFactor(const std::vector<Real> & azimuthal_list) const;

  /**
   * Creates peripheral area mesh for the patterned hexagon mesh. Note that the function create the
   * peripheral area for each side of the unit hexagon mesh before stitching. An edge unit hexagon
   * has two sides that need peripheral areas, whereas a corner unit hexagon has three such sides.
   * The positions of the inner and outer boundary nodes are pre-calculated as positions_inner and
   * d_positions_outer; This function performs interpolation to generate the mesh grid.
   * @param mesh input mesh to create the peripheral area mesh onto
   * @param num_sectors_per_side number of azimuthal intervals
   * @param peripheral_invervals number of radial intervals of the peripheral region
   * @param position_inner key positions of the inner side of the peripheral region
   * @param d_position_outer key inremental positions of the outer side of the peripheral region
   * @param id_shift shift of subdomain id of the peripheral region
   * @return a mesh with the peripheral region added to a hexagon input mesh
   */
  std::unique_ptr<ReplicatedMesh>
  buildSimplePeripheral(const unsigned int num_sectors_per_side,
                        const unsigned int peripheral_invervals,
                        const std::vector<std::pair<Real, Real>> & position_inner,
                        const std::vector<std::pair<Real, Real>> & d_position_outer,
                        const subdomain_id_type id_shift);

  /**
   * Calculates the point coordinates of within a parallelogram region using linear interpolation.
   * @param pi_1_x x coordinate of the first inner side point (parallelogram vertex)
   * @param pi_1_y y coordinate of the first inner side point (parallelogram vertex)
   * @param po_1_x x coordinate of the first outer side point (parallelogram vertex)
   * @param po_1_y y coordinate of the first outer side point (parallelogram vertex)
   * @param pi_2_x x coordinate of the second inner side point (parallelogram vertex)
   * @param pi_2_y y coordinate of the second inner side point (parallelogram vertex)
   * @param po_2_x x coordinate of the second outer side point (parallelogram vertex)
   * @param po_2_y y coordinate of the second outer side point (parallelogram vertex)
   * @param i passed loop index 1
   * @param j passed loop index 2
   * @param num_sectors_per_side number of azimuthal intervals
   * @param peripheral_invervals number of radial intervals of the peripheral region
   * @return an interpolated position within a parallelogram
   */
  std::pair<Real, Real> pointInterpolate(const Real pi_1_x,
                                         const Real pi_1_y,
                                         const Real po_1_x,
                                         const Real po_1_y,
                                         const Real pi_2_x,
                                         const Real pi_2_y,
                                         const Real po_2_x,
                                         const Real po_2_y,
                                         const unsigned int i,
                                         const unsigned int j,
                                         const unsigned int num_sectors_per_side,
                                         const unsigned int peripheral_invervals) const;

  /**
   * Adds background and duct region mesh to stitched hexagon meshes. Note that the function works
   * for single unit hexagon mesh (corner or edge) separately before stitching.
   * @param mesh input mesh to add the peripheral region onto
   * @param pattern index of the input mesh for patterning
   * @param pitch pitch size of the input mesh
   * @param extra_dist extra distance needed to create the peripheral region
   * @param num_sectors_per_side_array numbers of azimuthal intervals of all input unit meshes
   * @param peripheral_duct_intervals numbers of radial intervals of the duct regions
   * @param rotation_angle angle that the generated mesh will be rotated by
   * @param mesh_type whether the peripheral region is for a corner or a side hexagon mesh.
   * @return a mesh of the hexagon unit mesh with peripheral region added.
   */
  void addPeripheralMesh(ReplicatedMesh & mesh,
                         const unsigned int pattern, //_pattern{i][j]
                         const Real pitch,           // pitch_array.front()
                         const std::vector<Real> & extra_dist,
                         const std::vector<unsigned int> & num_sectors_per_side_array,
                         const std::vector<unsigned int> & peripheral_duct_intervals,
                         const Real rotation_angle,
                         const unsigned int mesh_type);

  /**
   * Sets up poisitions of peripheral region layer by layer before deformation due to cutoff.
   * @param positions_inner key positions of the inner side of the peripheral region
   * @param d_positions_outer key inremental positions of the outer side of the peripheral region
   * @param extra_dist_in extra distance applied to the inner side
   * @param extra_dist_out extra distance applied to the outer side
   * @param pitch pitch size of the involved hexagon mesh
   * @param radial_index radial layer index
   * @return n/a
   */
  void positionSetup(std::vector<std::pair<Real, Real>> & positions_inner,
                     std::vector<std::pair<Real, Real>> & d_positions_outer,
                     const Real extra_dist_in,
                     const Real extra_dist_out,
                     const Real pitch,
                     const unsigned int radial_index) const;

  /**
   * Calculates x and y coordinates after rotating by theta angle.
   * @param x x coordinate of the node to be rotated
   * @param y y coordinate of the node to be rotated
   * @param theta rotation angle
   * @return n/a
   */
  void nodeCoordRotate(Real & x, Real & y, const Real theta) const;

  /**
   * Deforms peripheral region when the external side of a hexagonal assembly of stitched meshes
   * cuts off the stitched meshes.
   * @param mesh input mesh to be deformed
   * @param orientation orientation angle of the input mesh (move the deformation direction to y)
   * @param y_max_0 original maximum y position
   * @param y_max_n maximum y position after deformation
   * @param y_min minimum y position that is affected by the deformation
   * @param mesh_type whether the peripheral region is for a corner or a side hexagon mesh.
   * @param tols tolerance used to determine the boundary of deformation region
   * @return n/a (input mesh is directly altered)
   */
  void cutOffHexDeform(MeshBase & mesh,
                       const Real orientation,
                       const Real y_max_0,
                       const Real y_max_n,
                       const Real y_min,
                       const unsigned int mesh_type,
                       const Real tols = 1E-5) const;

  /**
   * Finds the center of a quadrilateral based on four vertices.
   * @param p1 vertex 1
   * @param p2 vertex 2
   * @param p3 vertex 3
   * @param p4 vertex 4
   * @return the intecept point coordinate x and y
   */
  std::pair<Real, Real> fourPointIntercept(const std::pair<Real, Real> & p1,
                                           const std::pair<Real, Real> & p2,
                                           const std::pair<Real, Real> & p3,
                                           const std::pair<Real, Real> & p4) const;

  /**
   * Collects sorted azimuthal angles of the external boundary.
   * @param mesh input mesh whose boundary node azimuthal angles need to be collected
   * @param lower_azi lower boundary of the azimuthal angles to be collected
   * @param upper_azi upper boundary of the azimuthal angles to be collected
   * @param return_type whether angle values or tangent values are returned
   * @param calculate_origin whether the mesh origin is calculated based on the centroid position
   * @param input_origin_x precalculated mesh origin coordinate x
   * @param input_origin_y precalculated mesh origin coordinate y
   * @param tol tolerence that the minimum azimuthal angle is
   * @return the list of azimuthal angles of all the nodes on the external grain boundary within the
   * given range
   */
  std::vector<Real> azimuthalAnglesCollector(ReplicatedMesh & mesh,
                                             const Real lower_azi = -30.0,
                                             const Real upper_azi = 30.0,
                                             const unsigned int return_type = ANGLE_TANGENT,
                                             const boundary_id_type bid = OUTER_SIDESET_ID,
                                             const bool calculate_origin = true,
                                             const Real input_origin_x = 0.0,
                                             const Real input_origin_y = 0.0,
                                             const Real tol = 1.0E-10) const;

  /**
   * Creates bias terms for multiple blocks.
   * @param radial_biases bias growth factors of the elements within the main regions of the blocks
   * @param intervals radial interval numbers of the main regions of the blocks
   * @param inner_boundary_layer_fractions radial fractions of the blocks to be defined as the
   * boundary layers near the inner boundaries
   * @param inner_boundary_layer_intervals radial interval numbers of the blocks to be defined as
   * the boundary layers near the inner boundaries
   * @param inner_boundary_layer_biases bias growth factors of the elements within the blocks to be
   * defined as the boundary layers near the inner boundaries
   * @param outer_boundary_layer_fractions radial fractions of the blocks to be defined as the
   * boundary layers near the outer boundaries
   * @param outer_boundary_layer_intervals radial interval numbers of the blocks to be defined as
   * the boundary layers near the outer boundaries
   * @param outer_boundary_layer_biases bias growth factors of the elements within the blocks to be
   * defined as the boundary layers near the outer boundaries
   * @return bias terms describing radial node positions of multiple blocks
   */
  std::vector<std::vector<Real>>
  biasTermsCalculator(const std::vector<Real> radial_biases,
                      const std::vector<unsigned int> intervals,
                      const std::vector<Real> inner_boundary_layer_fractions,
                      const std::vector<unsigned int> inner_boundary_layer_intervals,
                      const std::vector<Real> inner_boundary_layer_biases,
                      const std::vector<Real> outer_boundary_layer_fractions,
                      const std::vector<unsigned int> outer_boundary_layer_intervals,
                      const std::vector<Real> outer_boundary_layer_biases) const;

  /**
   * Creates bias terms for a single block.
   * @param radial_bias bias growth factor of the elements within the main region of the block
   * @param intervals radial interval number of the main region of the block
   * @param inner_boundary_layer_fraction radial fraction of the block to be defined as the
   * boundary layer near the inner boundary
   * @param inner_boundary_layer_intervals radial interval number of the block to be defined as
   * the boundary layer near the inner boundary
   * @param inner_boundary_layer_bias bias growth factor of the elements within the block to be
   * defined as the boundary layer near the inner boundary
   * @param outer_boundary_layer_fraction radial fraction of the block to be defined as the
   * boundary layer near the outer boundary
   * @param outer_boundary_layer_intervals radial interval number of the block to be defined as
   * the boundary layer near the outer boundary
   * @param outer_boundary_layer_bias bias growth factor of the elements within the block to be
   * defined as the boundary layer near the outer boundary
   * @return bias terms describing radial node positions of a single block
   */
  std::vector<Real> biasTermsCalculator(const Real radial_bias,
                                        const unsigned int intervals,
                                        const Real inner_boundary_layer_fraction = 0.0,
                                        const unsigned int inner_boundary_layer_intervals = 0,
                                        const Real inner_boundary_layer_bias = 1.0,
                                        const Real outer_boundary_layer_fraction = 0.0,
                                        const unsigned int outer_boundary_layer_intervals = 0,
                                        const Real outer_boundary_layer_bias = 1.0) const;
};
