#include "GameMap.h"
#include <nlohmann/json.hpp> // Biblioteca JSON pe care am adăugat-o
#include <fstream>           // Pentru a citi fișierul
#include <iostream>

using json = nlohmann::json;

GameMap::GameMap() : m_tileSize(0, 0), m_mapSize(0, 0) {}

GameMap::~GameMap() {}

bool GameMap::load(const std::string& jsonPath, const std::string& tilesetPath) {

    if (!m_tilesetTexture.loadFromFile(tilesetPath)) {
        std::cerr << "EROARE: Nu am putut incarca tileset-ul: " << tilesetPath << std::endl;
        return false;
    }

    std::ifstream f(jsonPath);
    if (!f.is_open()) {
        std::cerr << "EROARE: Nu am putut deschide fisierul JSON: " << jsonPath << std::endl;
        return false;
    }
    const float mapScale = 0.3f;
    json data;
    try {
        data = json::parse(f);
    } catch (json::parse_error& e) {
        std::cerr << "EROARE: Fisierul JSON este invalid: " << e.what() << std::endl;
        return false;
    }
    f.close();
    m_mapSize.x = data["width"];
    m_mapSize.y = data["height"];
    m_tileSize.x = data["tilewidth"];
    m_tileSize.y = data["tileheight"];

    const auto& tileLayer = data["layers"][0];
    const std::vector<int>& tileIDs = tileLayer["data"].get<std::vector<int>>();

    unsigned int tilesetColumns = m_tilesetTexture.getSize().x / m_tileSize.x;

    m_tiles.clear(); // Golește harta veche, dacă există
    m_tiles.reserve(m_mapSize.x * m_mapSize.y); // Optimizare

    for (unsigned int y = 0; y < m_mapSize.y; ++y) {
        for (unsigned int x = 0; x < m_mapSize.x; ++x) {

            int tileIndex = y * m_mapSize.x + x;
            int tileID = tileIDs[tileIndex];

            if (tileID == 0) {
                continue; // Nu desenăm nimic, sărim peste
            }

            int id = tileID - 1;

            int texX = (id % tilesetColumns) * m_tileSize.x;
            int texY = (id / tilesetColumns) * m_tileSize.y;

            sf::Sprite tileSprite(m_tilesetTexture);
            tileSprite.setTextureRect(sf::IntRect({(int)texX, (int)texY}, {(int)m_tileSize.x, (int)m_tileSize.y}));
            tileSprite.setScale({mapScale, mapScale});
            tileSprite.setPosition({ (float)(x * m_tileSize.x * mapScale),
                                     (float)(y * m_tileSize.y * mapScale) });
            m_tiles.push_back(tileSprite);
        }
    }


    std::cout << "Harta incarcata: " << m_mapSize.x << "x" << m_mapSize.y << " piese." << std::endl;
    std::cout << "Am creat " << m_tiles.size() << " sprite-uri pentru harta." << std::endl;
    return true;
}

void GameMap::draw(sf::RenderWindow& window) {
    for (const auto& tile : m_tiles) {
        window.draw(tile);
    }
}