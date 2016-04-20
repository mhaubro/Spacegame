#include "Game.h"

#include "UI.h"
#include "Graphics.h"
#include "Sprite.h"
#include "Chunk.h"
#include "Input.h"

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

    Input in = Input();
    UI ui = UI(this);
    GD.ClearColorRGB(BLACK);

    GD.SaveContext();

    Chunk chunk0 = Chunk(0);

    //chunk0.rewrite(1);

    short angle = 0;
    float x = 0,y = 4; //position

    Sprite sprite = Sprite(1,128,128,1);

    while (running){

    	in.pull();
        GD.Clear();
        
        score++;
        angle += in.getRotation();

        cam.moveTo(Vector2f(x,y));
        cam.translate(Vector2f(10,0));

        chunk0.render();
        GD.RestoreContext();

        GD.Begin(BITMAPS);
        sprite.render(x, y, angle, .5, 0);
        GD.RestoreContext();
        
        ui.render();
        
        GD.swap();
    }
}
