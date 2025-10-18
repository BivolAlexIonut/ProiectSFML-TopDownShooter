#include "Player.h"

//Implementez constructorul
Player::Player(float startX,float startY) {
    //Forma
    this->shape.setRadius(25.f);
    this->shape.setFillColor(sf::Color::Green);
    this->movementSpeed=200.f;
}

Player::~Player() {
    //Pentru curatare
}

void Player::update(float dt) {
    //Actiuni pentru player
    sf::Vector2f direction(0.f,0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        direction.y -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        direction.y += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        direction.x -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        direction.x += 1.f;
    }
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0.f) {
        direction /= length;
    }

    // 3. Adaugă mișcarea (folosind direcția, viteza și delta time)
    this->shape.move(direction * this->movementSpeed * dt);

}

void Player::draw(sf::RenderWindow& window) {
    window.draw(this->shape);
}