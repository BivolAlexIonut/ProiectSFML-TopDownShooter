#pragma once
#include <SFML/Graphics.hpp>
#include <ostream>

class Enemy {
public:
    Enemy(float startX, float startY);
    ~Enemy();
    void update(float dt);
    void draw(sf::RenderWindow& window);
    void takeDamage(float damage);
    sf::Vector2f getPosition() const;
    friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy);

private:
    float health;
    sf::Vector2f m_position;
    sf::Texture enemyTexture;
    sf::Sprite enemySprite;
};