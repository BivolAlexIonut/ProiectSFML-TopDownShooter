#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy();
    ~Enemy();
    void draw();
    void update();
    void takeDamage(float damage);

    sf::Vector2f getPosition();
private:
    float health;
    sf::Texture enemyTexture;
    sf::Sprite enemySprite;
};