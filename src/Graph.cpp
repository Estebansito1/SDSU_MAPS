#include "Graph.h"
#include <algorithm>

    Graph::Graph(int n) : n(n), adj(n) {}

        void Graph::setSize(int n_)
        {
            n = n_;
            adj.assign(n, {});
        }

        //
        void Graph::addEdge(int u, int v, int /*w*/)
        {
            if (u< 0 || v < 0 || u>= n || v >= n) return;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        //
        void Graph::addBuildingCode(const std::string& code, int index)
        {
            buildingCodeToIndex[code] = index;
        }

        //
        void Graph::addCourseLocation(const std::string& course,
                              const std::string& buildingCode)
        {
            auto it = buildingCodeToIndex.find(buildingCode);
            if (it == buildingCodeToIndex.end()) return;
            courseToIndex[course] = it->second;
        }
///////////

        int Graph::indexFromCourse(const std::string& course) const
        {
            auto it = courseToIndex.find(course);
            if (it == courseToIndex.end()) return -1;
            return it->second;
        }
//////////////

    std::vector<int> Graph::shortestPath(int start, int end) const
    {
        std::vector<int> path;
        if (start < 0 || end < 0 || start >= n || end >= n) return path;

        std::vector<int> parent(n, -1);
        std::vector<bool> visited(n, false);
        std::queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty())
            {
                int u = q.front();
                q.pop();
                if (u == end) break;

        for (int v : adj[u])
            {
            if (!visited[v])
                {
                visited[v] = true;
                parent[v]= u;
                q.push(v);
                }
            }
        }
        if (!visited[end]) return path;

        for (int cur =end; cur != -1; cur = parent[cur])
            {
             path.push_back(cur);
            }
        std::reverse(path.begin(), path.end());
        return path;
    }
///////////////////

    void Graph::drawEdges(sf::RenderWindow& window,

    const std::vector<sf::Vector2f>& positions) const
    {
        for (int u = 0; u< n; ++u)
            {
             for (int v: adj[u])
                 {
                    if(u < v)
                {
                sf::Vertex line[] =
                    {
                    sf::Vertex(positions[u]+ sf::Vector2f(15.f, 15.f),
                               sf::Color(150, 150, 150)),
                    sf::Vertex(positions[v] +sf::Vector2f(15.f, 15.f),
                               sf::Color(150, 150, 150))
                    };
                    window.draw(line, 2, sf::Triangles);
                }
            }
         }
    }


    void Graph::drawPath(sf::RenderWindow& window,
                     const std::vector<sf::Vector2f>& positions,
                     const std::vector<int>& path) const
    {
    if (path.size() < 2) return;

    for (std::size_t i= 0; i+ 1 < path.size(); ++i)
        {
            int a = path[i];
            int b = path[i +1];

        sf::Vertex line[]=
            {
                sf::Vertex(positions[a] + sf::Vector2f(15.f, 15.f), sf::Color::White),
                sf::Vertex(positions[b] + sf::Vector2f(15.f, 15.f), sf::Color::White)
            };
        window.draw(line, 2, sf::Lines);
        }
    }



