#include "GD2.h"
#include "Game.h"
#include "Graphics.h"

#include "myassets.h"

int main() {

    GD.begin();    
    LOAD_ASSETS();

    resetGraphics();

    Cam cam;

    while (true){
        Game game = Game();
        game.run();
    }
}
