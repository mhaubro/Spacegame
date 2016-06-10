#include "UI.h"
#include "Game.h"
#include "GD2.h"
#include "Graphics.h"
#include "player.h"
#include "GameTimer.h"
#include "utils.h"
#include "pinnames.h"

UI::UI() {
	button1 = new Button(PB_13);
	button2 = new Button(PB_14);
	button3 = new Button(PB_15);
	button4 = new Button(PB_1);
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
		GD.cmd_number(4, 4 + 12, 16, OPT_SIGNED, player.getPosition().x);
		GD.cmd_number(4, 4 + 24, 16, OPT_SIGNED, player.getPosition().y);

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
				((16 * (SCREEN_WIDTH / 2 - 16)) / player.maxHealth)
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
						- (16 * (SCREEN_WIDTH / 2 - 16) / player.maxEnergy)
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

		//prints FPS
		GD.cmd_text(4, 50, 16, OPT_SIGNED, "FPS:");
		GD.cmd_number(36, 50, 16, OPT_SIGNED, 1 / timer.getDeltaTime());

		//prints speed
		GD.cmd_text(4, 70, 16, OPT_SIGNED, "UPS:");// units per sec
		GD.cmd_number(36, 70, 16, OPT_SIGNED, player.getVelocity().length());

		if (button1->isPressed()) {
			GD.cmd_text(350, 200, 16, OPT_CENTER, "Digital3");
		}

		if (button2->isPressed()) {
			GD.cmd_text(350, 220, 16, OPT_CENTER, "Digital4");
		}
		if (button3->isPressed()) {
			GD.cmd_text(350, 240, 16, OPT_CENTER, "Digital5");
		}
		if (button4->isPressed()) {
			GD.cmd_text(350, 260, 16, OPT_CENTER, "Digital6");
		}

	}

	GD.RestoreContext();
}
