# ElementPropertyReadFile

!syntax description /UserObjects/ElementPropertyReadFile

This user object has two modes to operate in, which are toggled using the
`read_type` parameter.

- In +element+ mode a file is read in that contains `nprop` values for each element in the mesh. The element IDs are expected to be consecutive numbers starting at zero.
- In +grain+ mode a Voronoi tessellation with `ngrain` random centers is created assuming an orthogonal rectangular periodic mesh. A file is read in that contains `nprop` values for each grain.
- In +block+ mode a file is read in that contains `nprop` values for each block in the mesh. `nblock` is the number of blocks in the mesh.

Values can be queried from the object by passing in a property ID and an element
pointer. In +element+ mode a direct lookup from the data table based on
element ID is performed. In +grain+ mode the centroid of the passed in element
is taken and the grain ID is determined as the ID of the Voronoi center closest
to the element centroid.

The [!param](/UserObjects/ElementPropertyReadFile/use_zero_based_block_indexing)
parameter indicates whether the block numbers start with zero (`true`)
or one (`false`).

!syntax parameters /UserObjects/ElementPropertyReadFile

!syntax inputs /UserObjects/ElementPropertyReadFile

!syntax children /UserObjects/ElementPropertyReadFile

!bibtex bibliography
