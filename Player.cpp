// Player.cpp
#include "Player.h"
#include <cmath>
#include <iostream>

const float PI = 3.14159265358979323846f;
const float HEALTHBAR_WIDTH = 300.f;
const float HEALTHBAR_HEIGHT = 7.f;
const float HEALTHBAR_OFFSET_Y = -360.f;

Player::Player(float startX, float startY) :
    playerTexture(), //Initializez textura
    playerSprite(this->playerTexture) // Pasez textura la cosntructor
{
    if (!this->playerTexture.loadFromFile("../assets/Premium Content/Examples/Assembled skins.png")) {
        std::cerr << "EROARE: Nu am putut incarca ../assets/Premium Content/Examples/Assembled skins.png" << std::endl;
    }
    //Initializare viata jucator
    maxHealth = 100.f;
    currentHealth = maxHealth;

    sf::IntRect skinRect({995, 1637}, {265, 461});
    this->playerSprite.setTextureRect(skinRect);

    //HealthBar
    HealthBarBackground.setSize(sf::Vector2f(HEALTHBAR_WIDTH, HEALTHBAR_HEIGHT));
    HealthBarBackground.setFillColor(sf::Color(50,50,50));
    HealthBarForeground.setSize(sf::Vector2f(HEALTHBAR_WIDTH, HEALTHBAR_HEIGHT));
    HealthBarForeground.setFillColor(sf::Color::Green);
    updateHealthBar();
    updateHealthBarPosition();

    this->playerSprite.setOrigin({skinRect.size.x / 2.f, skinRect.size.y / 2.f});
    this->playerSprite.setPosition({640, 360});
    this->playerSprite.scale({0.2f,0.2f});
    this->movementSpeed = 270.f;
}

Player::~Player() {}

void Player::draw(sf::RenderWindow& window) {
    window.draw(this->playerSprite);
    window.draw(this->HealthBarBackground);
    window.draw(this->HealthBarForeground);
}

void Player::updateHealthBar() {
    float healthpercent = currentHealth / maxHealth;
    float netWidth = HEALTHBAR_WIDTH* healthpercent;
    this->HealthBarForeground.setSize(sf::Vector2f(netWidth,HEALTHBAR_HEIGHT));
    updateHealthBarPosition();
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