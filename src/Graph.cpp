/* this file implements the graph class used to show the SDSU  ampus
 * as a network of buildings connected by a walking path. The graph stores a
 * adjacent list for each building and uses BFS "breadth first search" to
 * compute the shortest route between buildings. It also mapsnbuilding names and course
 * codes to their building ID for fast look up.
 * The graph is used by the UI to draw the edges on the map and animated paths
 * during navigation.
 */

#include "Graph.h"
#include <algorithm>



