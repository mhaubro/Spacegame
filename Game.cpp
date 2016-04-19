#include "Game.h"

#include "UI.h"
#include "Graphics.h"
#include "Sprite.h"
#include "Chunk.h"

Game::Game() : running(false), score(42)
{   
    maxHealth = 100;
    maxEnergy = 100;
    
    health = maxHealth;
    energy = maxEnergy;
}

void Game::run()
{
    running = true;
    UI ui = UI(this);
    GD.ClearColorRGB(BLACK);

    GD.SaveContext();

    Chunk chunk = Chunk(1);

    short angle = 0;
    float x = 0,y = 0; //position
    float vx = 0.1, vy = 0.1; //velocity
    float ax = 0, ay = 0; //acceleration
    
    int aax = 0, aay = 0, aaz = 0;
    
    Sprite sprite = Sprite(1,128,128,1);

    while (running){

        GD.Clear();
        
        score++;
        angle += 200;
        
        ax = aax / 100;
        ay = aay / 100;
        
        vx += ax;
        vy += ay;
        
        x += vx;
        y += vy;
        
        if (x < -SCREEN_UNIT_BORDER_X)
        {
            vx = -vx;
            x = -SCREEN_UNIT_BORDER_X;
        }
        if (x > SCREEN_UNIT_BORDER_X)
        {
            vx = -vx;
            x = SCREEN_UNIT_BORDER_X;
        }
        if (y < -SCREEN_UNIT_BORDER_Y)
        {
            vy = -vy;
            y = -SCREEN_UNIT_BORDER_Y;
        }
        if (y > SCREEN_UNIT_BORDER_Y)
        {
            vy = -vy;
            y = SCREEN_UNIT_BORDER_Y;
        }

        cam.moveTo(x,y);

        chunk.render();
        GD.RestoreContext();

        GD.Begin(BITMAPS);
        sprite.render(0,0,angle,1,0);
        sprite.render(x, y, angle, .5, 0);
        GD.RestoreContext();
        
        ui.render();
        
        GD.swap();
    }
}
