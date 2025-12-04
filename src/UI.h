#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Building.h"
#include "Graph.h"
#include "BuildingTree.h"

    class UI
    {
        public:
        UI();
        void run();

        private:
        sf::RenderWindow window;


        sf::Texture mapTexture;
        sf::Sprite mapSprite;


        std::vector<Building> buildings;
        Graph graph;
        BuildingTree buildingTree;


        int selectedA = -1;
        int selectedB = -1;


        std::vector<int> activePath;


        sf::CircleShape walker;
        bool animating = false;
        float t = 0.f;
        int pathPos = 0;
        float walkSpeed = 0.60f;

        sf::Clock clock;


        std::string typedInput;

        void processSearchInput();


        int detectClick(const sf::Vector2f& m) const;
        void handleClick(int idx);
        void handleText(sf::Event& e);
        void processCourse();
        void animateWalker(float dt);
        void drawScene();
    };

    #endif


