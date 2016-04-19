#include "Game.h"

#include "UI.h"
#include "Graphics.h"
#include "Sprite.h"

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

    short angle = 0;
    float x = 50,y = 50; //position
    float vx = 1, vy = 1; //velocity
    float ax = 0, ay = 0; //acceleration
    
    int aax = 0, aay = 0, aaz = 0;
    
    Sprite sprite = Sprite(TESTBIGIMAGE_HANDLE,128,128,1);

    while (running){



        GD.Clear();

        GD.SaveContext();

        GD.ColorRGB(0x333333);
        GD.Begin(EDGE_STRIP_B);
        GD.Vertex2f(16*SCREEN_WIDTH*0, 16*SCREEN_HEIGHT/2);
        GD.Vertex2f(16*SCREEN_WIDTH*1, 16*SCREEN_HEIGHT);

        GD.RestoreContext();

        Poly po;
    	po.begin();
    	po.v(16*50, 16*200);
    	po.v(16*150, 16*250);
    	po.v(16*350, 16*225);
    	po.v(16*150, 16*150);
        po.draw();
        GD.RestoreContext();


        score++;

        angle += 200;
        
        ax = aax / 100;
        ay = aay / 100;
        
        vx += ax;
        vy += ay;
        
        x += vx;
        y += vy;
        
        if (x < 0)
        {
            vx = -vx;
            x = 0;
        }
        if (x > SCREEN_WIDTH)
        {
            vx = -vx;
            x = SCREEN_WIDTH;
        }
        if (y < 0)
        {
            vy = -vy;
            y = 0;
        }
        if (y > SCREEN_HEIGHT)
        {
            vy = -vy;
            y = SCREEN_HEIGHT;
        }



        GD.Begin(BITMAPS);
        
        sprite.render(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,angle,1,0);
        
        sprite.render((short)x, (short)y, angle, 1, 0);



        GD.RestoreContext();
        


        ui.render();
        
        GD.swap();
    }
}
