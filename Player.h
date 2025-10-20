#pragma once
#include <SFML/Graphics.hpp>
#include "Health.h"
#include "GunSwitch.h"
#include <ostream>

class Player {
public:
    Player(float startX, float startY);
    ~Player();

    void update(float dt, sf::Vector2f mousePosition);
    void draw(sf::RenderWindow& window);
    void takeDamage(float damage);
    sf::Vector2f getPosition() const;

    void switchWeaponNext();
    void switchWeaponPrev();

    friend std::ostream& operator<<(std::ostream& os, const Player& player);

private:
    void updateHealthBar();
    void updateHealthBarPosition();

    sf::RectangleShape HealthBarBackground;
    sf::RectangleShape HealthBarForeground;
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    float movementSpeed;
    Health m_health;
    GunSwitch m_gunSwitch;
};