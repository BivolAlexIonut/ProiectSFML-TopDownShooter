#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player(float startX, float startY);
    ~Player();

    void update(float dt, sf::Vector2f mousePosition);
    void draw(sf::RenderWindow& window);
    void takeDamage(float damage);
    void updateHealthBar();
    void updateHealthBarPosition();
    void draw(sf::RenderTarget& target,sf::RenderStates states) const;

    sf::Vector2f getPosition() const;

private:
    sf::RectangleShape HealthBarBackground;
    sf::RectangleShape HealthBarForeground;
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    float movementSpeed;
    float maxHealth;
    float currentHealth;
};