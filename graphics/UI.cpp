#include "UI.h"
#include "Game.h"
#include "GD2.h"
#include "Graphics.h"
#include "player.h"
#include "GameTimer.h"
#include "utils.h"
#include "pinnames.h"

UI::UI() :
		youDied(new SpriteTemplate(YOU_DIED_HANDLE, 60, 33, 0)) {

}

void UI::render() {
	GD.RestoreContext();

	if (game.isOver()) {
		GD.ColorRGB(WHITE);
		GD.ColorA(128);
		GD.Begin(BITMAPS);
		GD.BitmapHandle(YOU_DIED_HANDLE);
		GD.Cell(0);
		GD.BitmapSize(NEAREST, BORDER, BORDER, SCREEN_WIDTH, SCREEN_HEIGHT);
		GD.cmd_loadidentity();
		GD.cmd_scale(F16(8), F16(8));
		GD.cmd_setmatrix();
		GD.Vertex2f(0, 0);
	} else {

		GD.ColorA(0x88);
		GD.ColorRGB(GREY);

		GD.Begin(EDGE_STRIP_B);
		GD.Vertex2ii(0, SCREEN_HEIGHT - 30);
		GD.Vertex2ii(56, SCREEN_HEIGHT - 30);
		GD.Vertex2ii(76, SCREEN_HEIGHT - 10);
		GD.Vertex2ii(SCREEN_WIDTH / 2 - 52, SCREEN_HEIGHT - 10);
		GD.Vertex2ii(SCREEN_WIDTH / 2 - 32, SCREEN_HEIGHT - 30);
		GD.Vertex2ii(SCREEN_WIDTH / 2 + 32, SCREEN_HEIGHT - 30);
		GD.Vertex2ii(SCREEN_WIDTH / 2 + 52, SCREEN_HEIGHT - 10);
		GD.Vertex2ii(SCREEN_WIDTH - 76, SCREEN_HEIGHT - 10);
		GD.Vertex2ii(SCREEN_WIDTH - 56, SCREEN_HEIGHT - 30);
		GD.Vertex2ii(SCREEN_WIDTH - 0, SCREEN_HEIGHT - 30);

		GD.Begin(EDGE_STRIP_A);
		GD.Vertex2ii(0, 20);
		GD.Vertex2ii(80, 20);
		GD.Vertex2ii(100, 0);
		GD.Vertex2ii(SCREEN_WIDTH - 100, 0);
		GD.Vertex2ii(SCREEN_WIDTH - 72, 28);
		GD.Vertex2ii(SCREEN_WIDTH, 28);

		GD.ColorA(0xFF);

		GD.LineWidth(3 * 16);

		// prints gameinfo in upper left corner
		GD.ColorRGB(WHITE);
		GD.cmd_text(4, 4, 16, OPT_SIGNED, "SPACE GAME");

		// prints the score in the upper right corner.
		GD.cmd_text(SCREEN_WIDTH - 4, 4, 16, OPT_RIGHTX, "SCORE");
		GD.cmd_number(SCREEN_WIDTH - 4, 4 + 12, 16, OPT_RIGHTX + 8, game.score);

		// prints the health level in the lower left corner
		GD.Begin(LINES);
		GD.ColorRGB(DARK_GREY);
		GD.Vertex2f(16 * 4, 16 * (SCREEN_HEIGHT - 4));
		GD.Vertex2f(16 * (SCREEN_WIDTH / 2 - 16), 16 * (SCREEN_HEIGHT - 4));
		GD.ColorRGB(COLOR_HEALTH);
		GD.Vertex2f(16 * 4, 16 * (SCREEN_HEIGHT - 4));
		GD.Vertex2f(
				((16 * (SCREEN_WIDTH / 2 - 16)) / MAX_PLAYER_HEALTH)
						* player.health, 16 * (SCREEN_HEIGHT - 4));
		GD.cmd_text(4, SCREEN_HEIGHT - 26, 16, OPT_SIGNED, "Health");
		GD.cmd_number(4, SCREEN_HEIGHT - 16, 16, OPT_SIGNED + 4, player.health);
		if (player.health < 100) {
			GD.cmd_text(SCREEN_WIDTH / 2 - 16, 100, 16, OPT_RIGHTX,
					"LOW HEALTH!");
		}

		// prints energy level in the lower right corner
		GD.Begin(LINES);
		GD.ColorRGB(DARK_GREY);
		GD.Vertex2f(16 * (SCREEN_WIDTH - 4), 16 * (SCREEN_HEIGHT - 4));
		GD.Vertex2f(16 * (SCREEN_WIDTH / 2 + 16), 16 * (SCREEN_HEIGHT - 4));
		GD.ColorRGB(COLOR_ENERGY);
		GD.Vertex2f(16 * (SCREEN_WIDTH - 4), 16 * (SCREEN_HEIGHT - 4));
		GD.Vertex2f(
				(16 * SCREEN_WIDTH)
						- (16 * (SCREEN_WIDTH / 2 - 16) / MAX_PLAYER_ENERGY)
								* player.energy, 16 * (SCREEN_HEIGHT - 4));
		GD.cmd_text( SCREEN_WIDTH - 4, SCREEN_HEIGHT - 26, 16, OPT_RIGHTX,
				"Energy");
		GD.cmd_number(SCREEN_WIDTH - 4, SCREEN_HEIGHT - 16, 16, OPT_RIGHTX + 4,
				player.energy);
		if (player.energy < 100) {
			GD.cmd_text(SCREEN_WIDTH / 2 + 16, 100, 16, OPT_SIGNED,
					"LOW ENERGY!");
		}

		// prints the height in the lower middle.
		GD.cmd_text(SCREEN_WIDTH / 2 - 4, SCREEN_HEIGHT - 26, 16, OPT_CENTERX,
				"Height");
		// GD.cmd_number(SCREEN_WIDTH/2-4, SCREEN_HEIGHT - 16, 16, OPT_CENTERX + 4, player.height);
		GD.cmd_number(SCREEN_WIDTH / 2 - 4, SCREEN_HEIGHT - 16, 16,
		OPT_CENTERX + 4, player.height);
	}
#if DEBUG
	GD.ColorRGB(WHITE);
	GD.ColorA(255);

	GD.cmd_text(4, 16, 16, OPT_SIGNED, "X:");
	GD.cmd_text(4, 28, 16, OPT_SIGNED, "Y:");
	GD.cmd_number(20, 4 + 12, 16, OPT_SIGNED, player.getPosition().x);
	GD.cmd_number(20, 4 + 24, 16, OPT_SIGNED, player.getPosition().y);

	//prints FPS
	GD.cmd_text(4, 50, 16, OPT_SIGNED, "FPS:");
	GD.cmd_number(36, 50, 16, OPT_SIGNED, 1 / timer.getDeltaTime());

	//prints speed
	GD.cmd_text(4, 70, 16, OPT_SIGNED, "UPS:"); // units per sec
	GD.cmd_number(36, 70, 16, OPT_SIGNED, player.getVelocity().length());

	GD.cmd_text(4, 150, 16, OPT_SIGNED, "B1: ");
	if (input.getButton1()) {
		GD.cmd_text(30, 150, 16, OPT_SIGNED, "TRUE");
	} else {
		GD.cmd_text(30, 150, 16, OPT_SIGNED, "FALSE");
	}

		//prints FPS
		GD.cmd_text(4, 50, 16, OPT_SIGNED, "FPS:");
		GD.cmd_number(36, 50, 16, OPT_SIGNED, 1 / timer.getDeltaTime());

		//prints speed
		GD.cmd_text(4, 70, 16, OPT_SIGNED, "UPS:");// units per sec
		GD.cmd_number(36, 70, 16, OPT_SIGNED, player.getVelocity().length());

		if (input.getButton1()) {
			GD.cmd_text(350, 200, 16, OPT_CENTER, "B1");
		}
		if (input.getButton2()) {
			GD.cmd_text(350, 220, 16, OPT_CENTER, "B2");
		}
		if (input.getButton3()) {
			GD.cmd_text(350, 240, 16, OPT_CENTER, "B3");
		}
		if (input.getButton4()) {
			GD.cmd_text(350, 260, 16, OPT_CENTER, "B4");
		}
		//Prints enemy location:
//		int j = 50;
//		for (std::vector<std::tr1::shared_ptr<Enemy> >::iterator i = enemies.begin(); i != enemies.end(); ++i){
//			GD.cmd_text(350, j, 16, OPT_SIGNED, "Enemy:");
//			Enemy & e = **i;
//			GD.cmd_number(400, j, 16, OPT_SIGNED, e.getPosition().x-player.getPosition().x);
//			GD.cmd_number(445, j, 16, OPT_SIGNED, e.getPosition().y-player.getPosition().y);
//			j += 30;
//		}
//		GD.cmd_text(100, 100, 16, OPT_SIGNED, "Enemies:");
//		GD.cmd_number(100, 120, 16, OPT_SIGNED, game.mEnemyManager.size());

		//Tries to print RAM:https://developer.mbed.org/questions/6994/How-to-print-Free-RAM-available-RAM-or-u/,
		//BROKEN
//		char   stackVariable;
//		void   *heap;
//		unsigned long result;
//		char* heapc = (char*) heap;
//		heap  = malloc(4);
//		int * result2  = &stackVariable;
//		free(heap);
//		GD.cmd_text(350, 150, 16, OPT_SIGNED, "Enemies size:");
//		GD.cmd_number(350, 180, 16, OPT_SIGNED, enemies.size());
		//GD.cmd_text(100, 150, 16, OPT_SIGNED, "Friendlybullets size:");
		//GD.cmd_number(100, 180, 16, OPT_SIGNED, friendlybullets.size());
		//GD.cmd_text(350, 210, 16, OPT_SIGNED, "Enemybullets size:");
		//GD.cmd_number(350, 240, 16, OPT_SIGNED, foebullets.size());
	GD.cmd_text(4, 170, 16, OPT_SIGNED, "B2: ");
	if (input.getButton2()) {
		GD.cmd_text(30, 170, 16, OPT_SIGNED, "TRUE");
	} else {
		GD.cmd_text(30, 170, 16, OPT_SIGNED, "FALSE");
	}

	GD.cmd_text(4, 190, 16, OPT_SIGNED, "B3: ");
	if (input.getButton3()) {
		GD.cmd_text(30, 190, 16, OPT_SIGNED, "TRUE");
	} else {
		GD.cmd_text(30, 190, 16, OPT_SIGNED, "FALSE");
	}

	GD.cmd_text(4, 210, 16, OPT_SIGNED, "B4: ");
	if (input.getButton4()) {
		GD.cmd_text(30, 210, 16, OPT_SIGNED, "TRUE");
	} else {
		GD.cmd_text(30, 210, 16, OPT_SIGNED, "FALSE");
	}
#endif

	GD.RestoreContext();
}
