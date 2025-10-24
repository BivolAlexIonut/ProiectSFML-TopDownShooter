#pragma once
#include <SFML/Graphics.hpp>
#include "Health.h"
#include "GunSwitch.h"
#include "Bullet.h"
#include <ostream>

class Player {
public:
    Player(float startX, float startY);
    ~Player();

    void update(float dt, sf::Vector2f mousePosition);
    void draw(sf::RenderWindow& window) const;
    void takeDamage(float damage);
    sf::Vector2f getPosition() const;

    void switchWeaponNext();
    void switchWeaponPrev();

    Bullet shoot(sf::Vector2f mousePosition);
    float getCurrentWeaponCooldown() const;

    int getCurrentAmmo() const;
    int getReserveAmmo() const;

    void reload();
    bool canShoot() const;

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
    sf::Texture bulletTexture;
    std::vector<sf::Vector2f> m_weaponBarrelOffsets;
    std::vector<sf::IntRect> m_weaponBulletRects;

    std::vector<float> m_weaponBulletAnimSpeeds;
    std::vector<float> m_weaponShootCooldowns;
    std::vector<std::vector<sf::IntRect>> m_weaponBulletAnimRects;

    std::vector<int> weaponMagSize;
    std::vector<int> weaponCurrentAmmo;
    std::vector<int> weaponReserveAmmo;
};