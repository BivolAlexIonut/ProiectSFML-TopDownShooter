#include <SFML/Graphics.hpp>
#include "Player.h"
#include "GameMap.h"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Top-Down Shooter");
    window.setFramerateLimit(60);

    GameMap gameMap;
    if (!gameMap.load("/home/alex/proiect-fac-sfml/ProiectSFML-TopDownShooter/assets/Levels/level1.json",
                      "/home/alex/proiect-fac-sfml/ProiectSFML-TopDownShooter/assets/Premium Content/Tileset with cell size 256x256.png")) {
        std::cerr << "EROARE FATALA: Harta nu a putut fi incarcata." << std::endl;
        return -1;
                      }
    const float mapScale = 0.4f;
    Player player(1000.f * mapScale, 1000.f * mapScale);

    sf::Clock clock;
    //Camera
    sf::View camera;
    camera.setSize({1280,720});//creez caemra si setez marimea camerei(ca marimea ferestrei de lucru)
    camera.setCenter(player.getPosition());

    while (window.isOpen()) {
        sf::Time dt = clock.restart();

        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        sf::Vector2i mousePositionWindow = sf::Mouse::getPosition(window);
        sf::Vector2f mousePositionWorld = window.mapPixelToCoords(mousePositionWindow,camera);
        player.update(dt.asSeconds(), mousePositionWorld);
        camera.setCenter(player.getPosition());

        window.clear(sf::Color(30, 30, 30));

        window.setView(camera);
        gameMap.draw(window);

        player.draw(window);

        window.display();
    }

    return 0;
}