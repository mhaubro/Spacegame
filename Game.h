//Author: MG

#ifndef GAME_H_
#define GAME_H_

#define DEBUG false

#include <vector>
#include <memory>
#include <algorithm>
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
#include "EnemyManager.h"
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

    unsigned int score;

    EffectManager mEffectManager;
    BulletManager mBulletManager;
    EnemyManager mEnemyManager;

    Game();
    ~Game();

    bool init();
    void run();

    bool isOver();
    void setGameOver();

};


extern Game game;
#endif
