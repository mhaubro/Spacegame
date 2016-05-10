#pragma once

#include "GD2.h"
#include "mbed.h"

#include "Player.h"

#include "myassets.h"

class Game
{
protected:
    bool running;
    
public:
    Game();
    void run();
    
    unsigned int score;

    Player p;
    PhysicsObject ph;

    float health;
    float energy;
    
    float maxHealth;
    float maxEnergy;
    
};
