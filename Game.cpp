#include "Game.h"

#include "UI.h"
#include "Graphics.h"
#include "Sprite.h"
#include "Chunk.h"

Game::Game() : running(false), score(42)
{   
    maxHealth = 1000;
    maxEnergy = 1000;
    
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
        if (y < 0)
        {
            vy = -vy;
            y = 0;
        }
        if (y > SCREEN_UNIT_BORDER_Y*2)
        {
            vy = -vy;
            y = SCREEN_UNIT_BORDER_Y*2;
        }

        cam.moveTo(Vector2f(x,y));
        cam.translate(Vector2f(10,0));

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
