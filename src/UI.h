/* The code defines the user interface class, which controls the entire SDSU campus
 * navigation program. It manages drawing the campus map, processing the users interaction
 * animating navigation path, and and handling data structure such as the Graph, BST, and stack
 * for shortes path and routing and undo history.
 */

#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <stack>

//custom project classes
#include "Building.h" // name id positon color
#include "Graph.h" // graph of campus building + shortest path
#include "BuildingTree.h"// BST for searching building by name

    class UI
    {
    public:
        UI(); // constructor loads map + creates building + connect graph
        void run(); // starts the main loop

    private:
        sf::RenderWindow window; // main SFML display window

        sf::Texture mapTexture;
        sf::Sprite mapSprite;

        std::vector<Building> buildings; // list vector of all building in the maps
        Graph graph; // Graph nodes = building, edge = walking pha, BFS for shortest path
        BuildingTree buildingTree; // binary search tree, provides fast text seach

        int selectedA = -1; // start A
        int selectedB = -1; // destination B

        std::vector<int> activePath; // stores the shortest path

        sf::CircleShape walker; // the animation is a circle
        bool animating = false;
        float t = 0.f;
        int pathPos =0;
        float walkSpeed = 0.60f;

        sf::Clock clock; // timing for smooth animation

        std::stack<int> history; // Stack stores previous select destination
                                //for the undo feature LIFO

        std::string typedInput; // stores keyboard input for searching building

        // find building based on course
        void processSearchInput();
        // detect mouse click
        int detectClick(const sf::Vector2f& m) const;
        //respond to mouse click
        void handleClick(int idx);
        //used for typing
        void handleText(sf::Event& e);
        //convert course to biulding ID
        void processCourse();
        // move walker allong the shortes path
        void animateWalker(float dt);
        // draw the map, building, text UI, edges, and walker
        void drawScene();
        // pops the last destination from the stack and redraws path
        void undo();


    };


#endif





