#include "GD2.h"
#include "Game.h"
#include "Graphics.h"

#include "myassets.h"
#include "Physicstest.h"

int main() {

	GD.begin();
	LOAD_ASSETS();

	resetGraphics();

	while (true) {
		Game game = Game();
		game.run();
	}
}
