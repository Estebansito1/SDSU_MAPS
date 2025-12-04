#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <SFML/Graphics.hpp>

    class Graph
    {
    public:
        Graph() = default;
        explicit Graph(int n);

        void setSize(int n);
        void addEdge(int u, int v, int w= 1);

        void addBuildingCode(const std::string& code, int index);

        void addCourseLocation(const std::string& course, const std::string& buildingCode);

        int indexFromCourse(const std::string& course) const;

        std::vector<int> shortestPath(int start, int end) const;

        void drawEdges(sf::RenderWindow& window, const std::vector<sf::Vector2f>& positions) const;

        void drawPath(sf::RenderWindow& window, const std::vector<sf::Vector2f>& positions,
                  const std::vector<int>& path) const;

        private:
        int n = 0;
        std::vector<std::vector<int>> adj;


        std::unordered_map<std::string, int > buildingCodeToIndex;
        std::unordered_map<std::string, int> courseToIndex;
    };

    #endif


