#pragma once
#include "GD2.h"
#include "Game.h"

class UI
{
protected:
    Game* game;
    
public:
    UI(Game* game);
    void render();
};
