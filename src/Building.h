/*this code defines a building class used to represent a building on the SDSU
 *campus map in the program. he biulding have a ID number, name, and a 2D position on the screen
 *and a display color.
 */

#ifndef BUILDING_H
#define BUILDING_H

#include <SFML/Graphics.hpp>
#include <string>

    //the class represents a building on the SDSU map
    class Building
    {
    public:
        int id;
        std::string name;
        sf::Vector2f position;
        sf::Color color;

        Building()= default; // makes an empty building

        //the constructor that sets all values when created
        Building(int i, const std::string& n, sf::Vector2f pos, sf::Color c)
            :id(i), name(n), color(c){}
        // draws the building as a circle in the SFML window
        void draw(sf::RenderWindow& window) const
        {
            sf::CircleShape shape(15);
            shape.setFillColor(color);
            shape.setPosition(position);
            window.draw(shape);
        }

    };
#endif




