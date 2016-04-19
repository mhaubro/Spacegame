#include "GD2.h"
#include "Game.h"

#include "myassets.h"

int main() {

    GD.begin();    
    LOAD_ASSETS();

    while (true){
        Game game = Game();
        game.run();
    }
}