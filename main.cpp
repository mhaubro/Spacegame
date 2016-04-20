#include "GD2.h"
#include "Game.h"
#include "Graphics.h"

#include "myassets.h"
#include "Physicstest.h"

int main() {

	GD.reset();

    GD.begin();    
    LOAD_ASSETS();

    resetGraphics();

    Cam cam;

    while (true){
    	Physicstest physicstest = Physicstest();
    	physicstest.run();
    }
}
