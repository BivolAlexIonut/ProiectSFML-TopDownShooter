#include <SFML/Graphics.hpp>
#include "Player.h"
#include "GameMap.h"
#include "Bullet.h"
#include <iostream>
#include <vector>
#include "Enemy.h"
#include "Health.h"
#include "GunSwitch.h"
#include <ostream>


int main() {
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Top-Down Shooter");
    window.setFramerateLimit(60);

    GameMap gameMap;
    if (!gameMap.load("/home/alex/proiect-fac-sfml/assets/Levels/level1.json",
                      "/home/alex/proiect-fac-sfml/assets/Premium Content/Tileset with cell size 256x256.png")) {
        std::cerr << "EROARE FATALA: Harta nu a putut fi incarcata." << std::endl;
        return -1;
                      }
    const float mapScale = 0.4f;
    Player player(1000.f * mapScale, 1000.f * mapScale);

    //BLOC DEBUG
    {
        std::cout << "Testare Regula celor 3 pentru clasa Health:" << std::endl;
        Health h1(50.f);
        Health h2 = h1;
        Health h3(100.f);
        h3 = h1;
        std::cout << "h3: " << h3 << std::endl;
    }

    Enemy enemy1(100.f, 200.f);
    std::vector<Enemy> enemies;
    enemies.push_back(enemy1);

    player.takeDamage(25.f);
    enemies[0].takeDamage(10.f);

    std::cout << "\nTestare operator<< :" << std::endl;
    std::cout << player << std::endl;
    std::cout << enemies[0] << std::endl;
    std::cout << gameMap << std::endl; // Acum ar trebui să funcționeze
    std::cout << "--- Sfârșit testare cerințe POO. Începe jocul. ---" << std::endl;
    //  SFaRȘIT BLOC

    sf::Clock clock;
    sf::View camera;
    camera.setSize({1280,720});
    camera.setCenter(player.getPosition());

    //Bullets
    std::vector<Bullet> bullets;
    sf::Clock shootTimer;
    const float shootCooldown = 0.2f;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();

        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (event->is<sf::Event::KeyPressed>()) {
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::E) {
                    player.switchWeaponNext();
                }
                if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Q) {
                    player.switchWeaponPrev();
                }
            }
        }

        sf::Vector2i mousePositionWindow = sf::Mouse::getPosition(window);
        sf::Vector2f mousePositionWorld = window.mapPixelToCoords(mousePositionWindow,camera);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && shootTimer.getElapsedTime().asSeconds()> shootCooldown) {
            //Creez glnt si trag
            bullets.push_back((player.shoot(mousePositionWorld)));
            shootTimer.restart();
        }


        player.update(dt.asSeconds(), mousePositionWorld);
        camera.setCenter(player.getPosition());

        sf::Vector2f playerPos = player.getPosition();
        for (auto& enemy : enemies) {
            enemy.update(dt.asSeconds(), playerPos);
        }

        for (auto& bullet : bullets) {
            bullet.update(dt.asSeconds());
        }

        window.clear(sf::Color(30, 30, 30));
        window.setView(camera);
        gameMap.draw(window);
        player.draw(window);

        for (auto& enemy : enemies) {
            enemy.draw(window);
        }
        for (auto& bullet : bullets) {
            bullet.draw(window);
        }

        window.display();
    }

    return 0;
}