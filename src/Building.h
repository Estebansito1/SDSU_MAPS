#ifndef BUILDING_H
#define BUILDING_H

#include <SFML/Graphics.hpp>
#include <string>

    class Building
    {
    public:
        int id;
        std::string name;
        sf::Vector2f position;
        sf::Color color;

        Building()= default;

        Building(int i, const std::string& n, sf::Vector2f pos, sf::Color c)
            : id(i), name(n), position(pos), color(c) {}
/////////////
//
        void draw(sf::RenderWindow& window) const
        {
            sf::CircleShape shape(15);
            shape.setFillColor(color);
            shape.setPosition(position);
            window.draw(shape);
        }
    };

    #endif


