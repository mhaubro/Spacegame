
#ifndef GAME_H_
#define GAME_H_

#include "BackGround.h"
#include "UI.h"
#include "Entity.h"

using namespace std;

class Game
{
protected:
    bool running;

    UI ui;

    BackGround background;

    void update();
    void render();

public:
    Game();
    ~Game();

    bool init();
    void run();

    unsigned int score;


};

extern Game game;

#endif
