#pragma once
#include <SFML/Graphics.hpp>

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include <cmath>

class Player {
public:
    Player(float stratX,float startY);
    ~Player();
    void update(float dt);
    //Desenez jucatorul prin fereastra
    void draw(sf::RenderWindow& window);

private:
    //Datele specifice jucatorului
    sf::CircleShape shape;
    float movementSpeed;
};
