#include "Health.h"
#include <iostream>

Health::Health(float maxHealth) : m_currentHealth(maxHealth), m_maxHealth(maxHealth) {
    std::cout << "DEBUG: Cosntrucior Health." << std::endl;
}

Health::Health(const Health& other)
    : m_currentHealth(other.m_currentHealth), m_maxHealth(other.m_maxHealth) {
    std::cout << "DEBUG: Cosntrucitr de copiere Health." << std::endl;
}

Health& Health::operator=(const Health& other) {
    std::cout << "DEBUG: Opeartor= " << std::endl;
    if (this != &other) {
        m_currentHealth = other.m_currentHealth;
        m_maxHealth = other.m_maxHealth;
    }
    return *this;
}

Health::~Health() {
    std::cout << "DEBUG: Destructor." << std::endl;
}

void Health::takeDamage(float amount) {
    m_currentHealth -= amount;
    if (m_currentHealth < 0) {
        m_currentHealth = 0;
    }
}

float Health::getPercentage() const {
    if (m_maxHealth == 0) return 0;
    return m_currentHealth / m_maxHealth;
}

float Health::getCurrent() const { return m_currentHealth; }
float Health::getMax() const  { return m_maxHealth; }

std::ostream& operator<<(std::ostream& os, const Health& health) {
    os << "Health: " << health.m_currentHealth << "/" << health.m_maxHealth;
    return os;
}