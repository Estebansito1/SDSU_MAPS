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

    // the constructor createes graph with n  node, each one = a building
    Graph::Graph(int a) : n(n), adj(n) {}

    //rezise graph if more buildings are added later
    void Graph::setSize(int n_)
    {
        n = n_;
        adj.resize(n,{}); // reset adj list
    }
///////////

    // add an inderect edge between buildings u and v for the walking path
    void Graph::addEdge(int u, int v, int /*w*/)
    {
    if (u<0 || v <0 || u>=n || v>=n) return;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
//////////

    //stores mapping code, building index
    void Graph::addBuildingCode(const std::string& code, int index)
    {
        buildingCodeToIndex[code] = index;
    }
//////////

    // stores mapping course code building index where the class is located
    void Graph::addCourseLocation(const std::string& course, const std::string& buildingCode)
    {
        auto it = buildingCodeToIndex.find(buildingCode);
        if (it==buildingCodeToIndex.end()) return;
        courseToIndex[course] = it->second;
    }
/////////

    // look up building ID from the course code return -1 if not found
    int Graph::indexFromCourse(const std::string& course) const
    {
        auto it = courseToIndex.find(course);
        if (it==courseToIndex.end()) return -1;
        return it->second;
    }
//////////

    //BST shortest path search, return the walking path from star to finish
    std::vector<int> Graph::shortestPath(int start, int end) const
    {

    }



