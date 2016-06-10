
#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include "BackGround.h"
#include "UI.h"
#include "Entity.h"
#include "GD2.h"
#include "Player.h"
#include "myassets.h"
#include "Graphics.h"
#include "Input.h"
#include "World.h"
#include "GameTimer.h"
#include "Bullet.h"
#include "enemy.h"

#include "EffectManager.h"
#include "BulletManager.h"

class Game
{
protected:
    bool running;
    bool isGameOver;

    UI ui;

    BackGround background;

    void update();
    void updateEnemies();
    void render();
    void renderEnemies();
    void removeEnemies();


public:

    EffectManager mEffectManager;
    BulletManager mBulletManager;

    Game();
    ~Game();

    bool init();
    void run();

    unsigned int score;

    bool isOver();
    void setGameOver();

};

extern Game game;
#endif
