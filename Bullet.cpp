#include "Bullet.h"
#include <cmath>

const float PI = 3.14159265358979323846f;

Bullet::Bullet(sf::Texture &texture, sf::IntRect &textureRect, sf::Vector2f startPos, sf::Vector2f direction,
    float animSpeed,int animFrames)
    :bulletSprite(texture),
    m_animFrames(animFrames)
{
    bulletCurrentFrame = 0;
    bulletAnimSpeed = animSpeed;
    bulletSprite.setTextureRect(textureRect);
    bulletRect = textureRect;

    float originX = bulletRect.size.x / 2.f;
    float originY = bulletRect.size.y / 2.f;
    bulletSprite.setOrigin({originX, originY});
    float angleInRadians = std::atan2(direction.y, direction.x);
    float angleInDegrees = angleInRadians * (180.f / PI);
    bulletSprite.setRotation(sf::degrees(angleInDegrees));

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

    if (bulletTimer.getElapsedTime().asSeconds() > bulletAnimSpeed){
        bulletCurrentFrame++;
        bulletTimer.restart();
    }
    if (bulletCurrentFrame >= m_animFrames) {
        bulletCurrentFrame = 0;
    }
    sf::IntRect newRect = bulletRect;
    newRect.position.x = bulletRect.position.x + (bulletRect.size.x * bulletCurrentFrame);
    bulletSprite.setTextureRect(newRect);
}

void Bullet::draw(sf::RenderWindow &window) {
    window.draw(bulletSprite);
}