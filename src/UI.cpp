/*this code handles all user inputs, such as mouse clicks and keyboard typings,
 *draws building and paths using SFML, and animates the shoetes path route between
 *buildings using the graph data structure.
 *it also uses a BST to search building by name, a graph with BFS to calculate the shortes path
 *a stack to store and undo navigation history by pressing u. The UI is the central controller
 *that connects interaction, display and all data structures learned in cs210.
 */


#include "UI.h"
#include <iostream>

    //converst text into uppercase
    std::string toUpper(std::string s)
    {
        for (char& c: s) c = toupper(c);
        return s;
    }

    //constructor load map places buildinng, builds graph + BST
    UI::UI():window(sf::VideoMode(1200, 800), "SDS_MAPS")
    {
        if (!mapTexture.loadFromFile("assets/sdsu_map.png"))
            std::cout<<"Failed to load map /n";
        mapSprite.setTexture(mapTexture);
        //Vector list of campus building ID,name, map possition, color
        buildings=
        {
            {0, "LAMDEN", {1085, 145}, sf::Color::Cyan},
            {1, "BOOKSTORE", {700, 300}, sf::Color::Yellow},
            {2, "MANCHESTER", {850, 520}, sf::Color::Blue},
            {3, "ADMIN", {300, 350}, sf::Color::Red},
            {4, "LOVE", {480, 520}, sf::Color::Green},
            {5, "BELL", {430, 330}, sf::Color(255,105,180)},
            {6, "STUDENT", {1010, 350}, sf::Color(255,140,0)},
            {7, "EDU", {800, 170}, sf::Color(255,106,33)},
        };

        graph.setSize(buildings.size());

        //insert buildings into BTS and the graph look up table
        for (auto& b : buildings)
        {
            std::string key = toUpper(b.name);
            buildingTree.insert(key, b.id);
            graph.addBuildingCode(key, b.id);
        }
        // stores class in the building location
        graph.addCourseLocation("CS210", "GMCS");
        graph.addCourseLocation("CS370", "GMCS");
        graph.addCourseLocation("MATH303", "ARC");
        graph.addCourseLocation("GAR", "EBA");
        //GRAPH EDGES walking paths between buildings
        auto E = [&](int a, int b) {graph.addEdge(a,b,1);};
        E(0,7); E(0,6); E(7,1); E(1,5); E(1,4); E(5,3); E(3,4); E(4,2); E(2,0);
        E(1,2); E(7,6); E(2,7); E(1,6); E(4,5); E(3,0); E(1,0); E(2,6); E(3,6);

        //walking animation character
        walker.setRadius(12);
        walker.setOrigin(4,4);
        walker.setFillColor(sf::Color::Black);
        clock.restart();
    }

    // detect if a mouse click hits a buildig
    int UI::detectClick(const sf::Vector2f &m) const
    {
    for (int i=0; i<buildings.size(); i++)
    {
        sf::Vector2f p=buildings[i].position;
        float dx= m.x -p.x;
        float dy= m.y -p.y;
        if (dx*dx + dy*dy < 25*25)
            return i;
    }
        return -1;
    }
    //handle recording building and navigation history via stack
    void UI::handleClick (int idx)
    {
        if (idx ==-1) return;
        if (selectedA ==-1)
            selectedA=idx;
        else if (selectedB ==-1)
        {
            history.push(selectedA); // save history for undo
            selectedB=idx;
        }
        else
        {
            history.push(selectedA);
            history.push(selectedB);
            selectedA=idx;
            selectedB=-1;
        }
        // once we have A and B compute shortest BFS path
        if (selectedA != -1 && selectedB != -1)
        {
            activePath = graph.shortestPath(selectedA, selectedB);
            if (activePath.size() >= 2)
            {
                animating true;
                t=0.f;
                pathPos=0;
                walker.setPosition(buildings[activePath[0]].position);
            }
        }
    }
    // undo navigation by popping the stack LIFO
    void UI::undo()
    {
    if (history.empty()) return;
        if (selectedA != -1 && selectedB != -1)
        {
            selectedB =-1;
            activePath.clear();
            animating= false;

            if (!history.empty())
            {
            selectedA =history.top();
                history.pop();
            }
        }
        else if (selectedA !=-1)
        {
        if (!history.empty())
        {
            selectedA = history.top;
            history.pop();
        }
        }
        else if (selectedA !=-1)
        {
            if (!history.empty())
            {
            selectedA = history.top();
                history.pop();
            }
            else
                selectedA = -1;
        }
    }



