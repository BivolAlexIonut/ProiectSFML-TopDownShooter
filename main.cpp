#include <SFML/Graphics.hpp>
#include "Player.h"

int main()
{
    // Crearea ferestrei (folosind sf::Vector2u pentru VideoMode)
    sf::RenderWindow window(sf::VideoMode({800, 600}), "TopDownShooter");
    window.setFramerateLimit(60);

    //Creare obiect de tip player
    Player player(400.f,300.f);
    sf::Clock clock;

    // Bucla principală
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        // ---------------------------------------------
        player.update(dt.asSeconds());
        // Curăță ecranul
        window.clear(sf::Color::Black);
        //Deseneaza
        player.draw(window);

        // Afișează
        window.display();
    }

    return 0;
}