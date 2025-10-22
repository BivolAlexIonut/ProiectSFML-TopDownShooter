// Bullet.h
#pragma once
#include <SFML/Graphics.hpp>

class Bullet {
public:
    Bullet(sf::Texture& texture, sf::IntRect& textureRect, sf::Vector2f startPos, sf::Vector2f direction,
           float animSpeed, int animFrames);
    ~Bullet();
    void draw(sf::RenderWindow& window);
    void update(float dt);

private:
    sf::Sprite bulletSprite;
    sf::Vector2f bulletVelocity;
    sf::IntRect bulletRect;
    sf::Clock bulletTimer;
    int bulletCurrentFrame;
    float bulletAnimSpeed;
    int m_animFrames;
};