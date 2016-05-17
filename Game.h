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
    
    float getMaxThrottle();

    unsigned int score;

    //Player p;
    //PhysicsObject ph;
    //PhysicsObject ph;

    float health;
    float energy;
    
    void runtest();
    float maxHealth;
    float maxEnergy;

};
