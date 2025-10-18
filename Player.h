// Player.h
#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player(float startX, float startY);
    ~Player();

    void update(float dt, sf::Vector2f mousePosition);

    void draw(sf::RenderWindow& window);

private:
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    float movementSpeed;
};