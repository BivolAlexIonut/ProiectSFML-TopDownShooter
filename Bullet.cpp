#include "Bullet.h"
#include <cmath> //am folosit pentru calculul de directie al glontului

Bullet::Bullet(sf::Texture &texture, sf::IntRect &textureRect, sf::Vector2f startPos, sf::Vector2f direction)
    :bulletSprite(texture)
{
    bulletCurrentFrame = 0;
    bulletAnimSpeed = 0.1f;
    bulletSprite.setTextureRect(textureRect);
    bulletRect = textureRect;
    bulletSprite.setPosition(startPos);
    float speed = 800.f;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length!=0)
        direction /= length;
    bulletVelocity = direction * speed;
}

Bullet::~Bullet(){}

void Bullet::update(float dt) {
    //miscar5ea glontului
    bulletSprite.move(bulletVelocity*dt);
    if (bulletTimer.getElapsedTime().asSeconds() > bulletAnimSpeed)
        bulletCurrentFrame++;
    if (bulletCurrentFrame >3)
        bulletCurrentFrame = 0;
    sf::IntRect newRect = bulletRect;
    newRect.position.x = bulletRect.position.x + (bulletRect.size.x * bulletCurrentFrame);
    bulletSprite.setTextureRect(newRect);
    bulletSprite.setTextureRect(newRect);
}

void Bullet::draw(sf::RenderWindow &window) {
    window.draw(bulletSprite);
}