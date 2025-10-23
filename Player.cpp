// Player.cpp
#include "Player.h"
#include <cmath>
#include <iostream>
#include <ostream>

const float PI = 3.14159265358979323846f;
const float HEALTHBAR_WIDTH = 300.f;
const float HEALTHBAR_HEIGHT = 7.f;
const float HEALTHBAR_OFFSET_Y = -360.f;

Player::Player(float startX, float startY) :
    playerTexture(),
    playerSprite(this->playerTexture),
    m_health(100.f),
    m_gunSwitch()
{
    if (!this->playerTexture.loadFromFile("../assets/Premium Content/Examples/Basic Usage.png")) {
        std::cerr << "EROARE: Nu am putut incarca ../assets/Premium Content/Examples/Basic Usage.png" << std::endl;
    }
    if (!this->bulletTexture.loadFromFile("/home/alex/proiect-fac-sfml/ProiectSFML-TopDownShooter/assets/Bullets.png")) {
        std::cerr <<"EROARE: Nu am putut incarca ../assets/Bullets.png" << std::endl;
    }

    // (Pistolul)
    m_weaponBarrelOffsets.push_back(sf::Vector2f(131.f, 356.f));
    m_weaponBulletRects.push_back(sf::IntRect({4, 213}, {8, 8}));
    m_weaponBulletAnimSpeeds.push_back(0.1f); // viteza animatie (0.1 secunde pe frame)
    m_weaponBulletAnimFrames.push_back(4);    // nr. frame-uri (are 4 frame-uri)
    m_weaponShootCooldowns.push_back(1.f);

    // PISTOLERO
    m_weaponBarrelOffsets.push_back(sf::Vector2f(133.f, 468.f)); // De ajustat
    m_weaponBulletRects.push_back(sf::IntRect({340, 102}, {9, 5})); // Alt glont
    m_weaponBulletAnimSpeeds.push_back(0.1f); // Animatie mai rapida
    m_weaponBulletAnimFrames.push_back(4);     // Poate are doar 3 frame-uri (0, 1, 2)
    m_weaponShootCooldowns.push_back(0.3f);

    // AGHEU
    m_weaponBarrelOffsets.push_back(sf::Vector2f(133.f, 548.f)); // De ajustat
    m_weaponBulletRects.push_back(sf::IntRect({256, 96}, {15, 16})); // Alt glont
    m_weaponBulletAnimSpeeds.push_back(0.1f); // Animatie mai lenta
    m_weaponBulletAnimFrames.push_back(4);    // Are 4 frame-uri
    m_weaponShootCooldowns.push_back(1.f);


    // SMG
    m_weaponBarrelOffsets.push_back(sf::Vector2f(133.f, 398.f));
    m_weaponBulletRects.push_back(sf::IntRect({256, 134}, {16, 5}));
    m_weaponBulletAnimSpeeds.push_back(0.1f);
    m_weaponBulletAnimFrames.push_back(4);
    m_weaponShootCooldowns.push_back(0.2f);

    // ShotGUN
    m_weaponBarrelOffsets.push_back(sf::Vector2f(133.f, 491.f));
    m_weaponBulletRects.push_back(sf::IntRect({254, 274}, {56, 12}));
    m_weaponBulletAnimSpeeds.push_back(0.35f);
    m_weaponBulletAnimFrames.push_back(3);
    m_weaponShootCooldowns.push_back(1.2f);

    // SNIPER
    m_weaponBarrelOffsets.push_back(sf::Vector2f(133.f, 558.f));
    m_weaponBulletRects.push_back(sf::IntRect({99, 199}, {10, 5}));
    m_weaponBulletAnimSpeeds.push_back(0.2f);
    m_weaponBulletAnimFrames.push_back(4);
    m_weaponShootCooldowns.push_back(2.f);

    sf::IntRect skinRect = m_gunSwitch.getCurrentWeaponRect();
    this->playerSprite.setTextureRect(skinRect);

    //HealthBar
    HealthBarBackground.setSize(sf::Vector2f(HEALTHBAR_WIDTH, HEALTHBAR_HEIGHT));
    HealthBarBackground.setFillColor(sf::Color(50,50,50));
    HealthBarForeground.setSize(sf::Vector2f(HEALTHBAR_WIDTH, HEALTHBAR_HEIGHT));
    HealthBarForeground.setFillColor(sf::Color::Green);
    updateHealthBar();
    updateHealthBarPosition();

    this->playerSprite.scale({0.2f,0.2f});
    this->playerSprite.setOrigin({skinRect.size.x / 2.f, skinRect.size.y / 2.f});
    this->playerSprite.setPosition({640, 360});
    this->movementSpeed = 270.f;
}

Player::~Player() {}

void Player::draw(sf::RenderWindow& window) {
    window.draw(this->playerSprite);
    window.draw(this->HealthBarBackground);
    window.draw(this->HealthBarForeground);
}

void Player::takeDamage(float damage) {
    this->m_health.takeDamage(damage);
    updateHealthBar();
}

void Player::updateHealthBar() {
    float healthpercent = m_health.getPercentage();
    float netWidth = HEALTHBAR_WIDTH * healthpercent;
    this->HealthBarForeground.setSize(sf::Vector2f(netWidth,HEALTHBAR_HEIGHT));
    updateHealthBarPosition();
}

float Player::getCurrentWeaponCooldown() const {
    int index = m_gunSwitch.getCurrentWeaponIndex();
    if (index < 0 || index >= m_weaponShootCooldowns.size()) {
        return 0.3f;
    }
    return m_weaponShootCooldowns[index];
}

void Player::updateHealthBarPosition() {
    sf::Vector2f playerPos = this->playerSprite.getPosition();
    float x = playerPos.x - (HEALTHBAR_WIDTH/2);
    float y = playerPos.y + HEALTHBAR_OFFSET_Y;
    this->HealthBarBackground.setPosition({x,y});
    this->HealthBarForeground.setPosition({x,y});
}

void Player::update(float dt, sf::Vector2f mousePosition) {
    sf::Vector2f direction(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) direction.y = -1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) direction.y = 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) direction.x = -1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) direction.x = 1.f;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0.f) {
        direction /= length;
    }
    this->playerSprite.move(direction * this->movementSpeed * dt);
    sf::Vector2f playerPosition = this->playerSprite.getPosition();
    float deltaX = mousePosition.x - playerPosition.x;
    float deltaY = mousePosition.y - playerPosition.y;
    float angleInRadians = std::atan2(deltaY, deltaX);
    float angleInDegrees = angleInRadians * (180.f / PI);
    this->playerSprite.setRotation(sf::degrees(angleInDegrees-90.f));
    updateHealthBarPosition();
}

sf::Vector2f Player::getPosition() const {
    return this->playerSprite.getPosition();
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
    sf::Vector2f pos = player.getPosition();
    os << "Player( Poz: " << pos.x << ", " << pos.y << " | " << player.m_health << " | " << player.m_gunSwitch << ")";
    return os;
}

void Player::switchWeaponNext() {
    m_gunSwitch.nextWeapon();
    sf::IntRect newRect = m_gunSwitch.getCurrentWeaponRect();
    this->playerSprite.setTextureRect(newRect);
    this->playerSprite.setOrigin({newRect.size.x / 2.f, newRect.size.y / 2.f});
}

void Player::switchWeaponPrev() {
    m_gunSwitch.previousWeapon();
    sf::IntRect newRect = m_gunSwitch.getCurrentWeaponRect();
    this->playerSprite.setTextureRect(newRect);
    this->playerSprite.setOrigin({newRect.size.x / 2.f, newRect.size.y / 2.f});
}


Bullet Player::shoot(sf::Vector2f mousePosition) {
    int currentIndex = m_gunSwitch.getCurrentWeaponIndex();

    if (currentIndex < 0 || currentIndex >= m_weaponBulletRects.size()) {
        currentIndex = 0;
    }

    sf::IntRect bulletRect = m_weaponBulletRects[currentIndex];
    sf::Vector2f barrelOffset = m_weaponBarrelOffsets[currentIndex];
    float animSpeed = m_weaponBulletAnimSpeeds[currentIndex];
    int animFrames = m_weaponBulletAnimFrames[currentIndex];

    const float localBarrelOffsetX = barrelOffset.x;
    const float localBarrelOffsetY = barrelOffset.y;

    sf::Vector2f localBarrelPos(localBarrelOffsetX, localBarrelOffsetY);
    sf::Transform playerTransform = playerSprite.getTransform();

    sf::Vector2f barrelPosition = playerTransform.transformPoint(localBarrelPos);

    sf::Vector2f direction = mousePosition - barrelPosition;
    return Bullet(bulletTexture, bulletRect, barrelPosition, direction,
                  animSpeed, animFrames);
}