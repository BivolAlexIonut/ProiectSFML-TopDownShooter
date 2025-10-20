#pragma once
#include <iostream>

class Health {
public:
    Health(float maxHealth = 100.f);

    Health(const Health& other);
    Health& operator=(const Health& other);
    ~Health();

    void takeDamage(float amount);
    float getPercentage() const;
    float getCurrent() const;
    float getMax() const;

    friend std::ostream& operator<<(std::ostream& os, const Health& health);

private:
    float m_currentHealth;
    float m_maxHealth;
};