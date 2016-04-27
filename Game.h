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
    
    PhysicsObject ph;
    Player p;

    unsigned int score;
    
    unsigned short health;
    unsigned short energy;
    
    unsigned short maxHealth;
    unsigned short maxEnergy;
    
};
