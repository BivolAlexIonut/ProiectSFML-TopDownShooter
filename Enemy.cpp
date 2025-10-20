#include "Enemy.h"
#include <iostream>

Enemy::Enemy(float startX, float startY)
    : health(50.f), m_position(startX, startY),
        enemyTexture(),
        enemySprite(this->enemyTexture)
{
    std::cout << "DEBUG: Inamic creat la " << startX << ", " << startY << std::endl;
    //Mai am de adaugat texturi si inamici
}

Enemy::~Enemy() {}
void Enemy::update(float dt) {}
void Enemy::draw(sf::RenderWindow& window) {}

void Enemy::takeDamage(float damage) {
    this->health -= damage;
    if (this->health < 0) this->health = 0;
    std::cout << "DEBUG: Inamic lovit viata e acum: " << this->health << std::endl;
}

sf::Vector2f Enemy::getPosition() const {
    return this->m_position;
}

std::ostream& operator<<(std::ostream& os, const Enemy& enemy) {
    os << "Pozitie inamic: " << enemy.m_position.x << ", " << enemy.m_position.y
       << " | Health: " << enemy.health << ")";
    return os;
}