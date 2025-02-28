#pragma once

#include "Component.h"

class Health : public Component {
    char _0x48[0x58];
    float max_health;
    char _0xA4[0x2C];
    float current_health;
public:
    DECLARE_COMPONENT(Health);

    inline float GetMaxHealth() { return max_health; }
    inline float GetHealth() { return current_health; }

    inline void SetMaxHealth(float max) { max_health = max; }
    inline void SetHealth(float health) { current_health = health; }
};