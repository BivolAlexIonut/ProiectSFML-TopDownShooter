// main.cpp
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Top-Down Shooter");
    window.setFramerateLimit(60);

    Player player(window.getSize().x / 2.f, window.getSize().y / 2.f);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();

        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        sf::Vector2i mousePositionWindow = sf::Mouse::getPosition(window);
        sf::Vector2f mousePositionWorld = window.mapPixelToCoords(mousePositionWindow);

        player.update(dt.asSeconds(), mousePositionWorld);

        window.clear(sf::Color(30, 30, 30));
        player.draw(window);
        window.display();
    }

    return 0;
}