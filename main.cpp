#include <SFML/Graphics.hpp>

int main()
{
    // Crearea ferestrei (folosind sf::Vector2u pentru VideoMode)
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Felicitări! Merge!");

    // Crearea unui cerc
    sf::CircleShape shape(100.f); // Rază de 100
    shape.setFillColor(sf::Color::Green);

    // Setarea poziției (folosind sf::Vector2f)
    shape.setPosition({300.f, 200.f});

    // Bucla principală
    while (window.isOpen())
    {
        // ----- NOUA BUCLĂ DE EVENIMENTE (SFML 3) -----
        // 1. pollEvent() nu mai ia un parametru
        // 2. Returnează un std::optional, pe care îl verificăm
        while (const auto event = window.pollEvent())
        {
            // 3. Verificăm tipul evenimentului cu .is<T>()
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        // ---------------------------------------------

        // Curăță ecranul
        window.clear();

        // Desenează cercul
        window.draw(shape);

        // Afișează
        window.display();
    }

    return 0;
}