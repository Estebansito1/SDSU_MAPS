/* the purpose of this code is so that the graph class cennects
 * building location and course codes into a navigational map strcture.
 * it supports shortest path routing and FSML visualization, enabling
 * users to search for buildings and see directiones drwn on the SDSU campus map
 */
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <SFML/Graphics.hpp>

    //the graph class represents the campus map as a graph
    // each building = node, path between buildings = weighted edge.
    // provides shortes path search and drawing helpers for the UI
    class Graph
    {
    public:
        Graph()= default;
        // creates a graph with n building nodes
        explicit Graph(int n);

        //resizes the adjacent list to n nodes
        void setSize(int n);

        //connect building u and building v with weight w
        // the weight represents the distance
        void addEdge(int u, int v, int w=1);

        //maps a building code like ART Or ENS to graph index
        void addBuildingCode(const std::string& code, int index);

        //links a course CS210 to a building via its code
        void addCourseLocation(const std::string& course, const std::string& buildingCode);

        //return the building  index where a course is located
        int indexFromCourse(const std::string& course) const;

        // find the shortes path between two nodes using BFS
        //return a list of node indecis that form the pah
        std::vector<int> shortesPath(int start, int end) const;


    };

#endif
