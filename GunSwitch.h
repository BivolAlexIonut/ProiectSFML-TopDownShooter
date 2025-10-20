#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <ostream>

class GunSwitch {
public:
    GunSwitch(); // Constructor
    ~GunSwitch();

    void nextWeapon();
    void previousWeapon();
    sf::IntRect getCurrentWeaponRect() const;

    friend std::ostream& operator<<(std::ostream& os, const GunSwitch& switcher);

private:
    int m_currentWeaponIndex;
    std::vector<sf::IntRect> m_weaponRects;
};