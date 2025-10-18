// Player.cpp
#include "Player.h"
#include <cmath>
#include <iostream>

const float PI = 3.14159265358979323846f;

Player::Player(float startX, float startY)
    : playerTexture() // Inițializare implicită pentru textură
    , playerSprite(this->playerTexture) // Pasăm textura la constructorul sprite-ului
{
    if (!this->playerTexture.loadFromFile("../assets/Premium Content/Examples/Assembled skins.png")) {
        std::cerr << "EROARE: Nu am putut incarca ../assets/Premium Content/Examples/Assembled skins.png" << std::endl;
    }
    sf::IntRect skinRect({995, 1637}, {265, 461});
    this->playerSprite.setTextureRect(skinRect);

    this->playerSprite.setOrigin({skinRect.size.x / 2.f, skinRect.size.y / 2.f});
    this->playerSprite.setPosition({startX, startY});
    this->playerSprite.scale({0.2f,0.2f});
    this->movementSpeed = 200.f;
}

Player::~Player() {}

void Player::draw(sf::RenderWindow& window) {
    window.draw(this->playerSprite);
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
}