# Planned DataStructures

 * Struct (typed properties - immutable properties not values)
 * Tuple (typed list of values as arrayobject - immutable entries not values)
 * Dictionary (force only assoc keys arrayobject)
 * List (force only index keys arrayobject)
 * Boxed (Opaque memory pointer for binary data retrieved as type)

 * Collections (probably very similar to hack's datastructures)
   * Set
   * Vector
   * Pair
   * Immutable?? (as trait? as interface?)

# Other Ideas?

 * Complex Trees?
   * B-tree
   * K-d tree
   * r tree
   * node tree 2, 2-3, 2-4 variants

Many of these can be done in "userland" but some of the more esoteric features
like enums acting as integers in all contexts cannot be replicated in userland