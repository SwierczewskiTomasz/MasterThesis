#ifndef CONSTANTS_H
#define CONSTANTS_H

#ifndef NO_DIM
#define NO_DIM 3
#endif

#ifndef MEASURE_TIME
#define MEASURE_TIME 0
#define MEASURE_CALLS 1
#endif

#ifndef VALIDATE_RESULT
#define VALIDATE_RESULT 0
#endif

#ifndef DEBUG
#define DEBUG 1
#define DEBUG_TRIANGULATION 0
#define DEBUG_REDBLACKTREE 0
#define DEBUG_EDGEOFEDGE 0
#define DEBUG_POLYGON 0
#endif

#ifndef FLOATING_POINT_PRECISION
#define FLOATING_POINT_PRECISION double
#endif

#ifndef ID
#define ID 1
#define ID_TYPE int
#endif



#ifndef REDBLACKTREEDLL
/** Choose structure you would like to store simplexes:
 * RedBlackTree - 0
 * RedBlackTreeDLL - 1
 * LUTRBTDLL - 2 
 */
#define REDBLACKTREEDLL 2
#endif

#ifndef DIVIDEWHEN
#define DIVIDEWHEN 32
#endif

#ifndef BLOCK_SIZE
/** Block size for array. Instead storing n-dimensional array it is using 2 arrays - 
 * one storing blocks, and second storing data in one block.
 */
#define BLOCK_SIZE 1024
#endif

#ifndef BLOCK_TYPE
/** Type for storing id's of place in block array. 
 */
#define BLOCK_TYPE int
#endif

#ifndef DT_EPSILON
#define DT_EPSILON 1e-15
#endif

#endif