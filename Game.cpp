#include "Game.h"

#include "UI.h"
#include "Graphics.h"
#include "Sprite.h"
#include "Chunk.h"
#include "Input.h"

Game::Game() :
		running(false), score(42) {
	maxHealth = 1000;
	maxEnergy = 1000;

	health = maxHealth;
	energy = maxEnergy;
}

void Game::run() {
	running = true;

	Input in = Input();
	UI ui = UI(this);
	GD.ClearColorRGB(BLACK);

	GD.SaveContext();

	Chunk chunk0 = Chunk(0);
	Chunk chunk1 = Chunk(1);
	Chunk chunk2 = Chunk(2);
	Chunk chunk3 = Chunk(3);

	//chunk0.rewrite(1);

	float angle = 0;
	Vector2f pos = Vector2f();
	Vector2f vel = Vector2f();

	Sprite sprite = Sprite(1, 128, 128, 1);

	while (running) {

		in.pull();
		GD.Clear();

		score++;
		angle += in.getRotation() * 0.001;

		while (angle > PI2)
			angle -= PI2;
		while (angle < 0)
			angle += PI2;

		if (in.getThrodle()) {
			vel += FromAngle(0.05, angle);
		}

		vel += Vector2f(0, -0.01);

		pos += vel;

		if (pos.y < 0) {
			pos.y = 0;
			vel.y *= -0.5;
		}
		if (pos.y > 50) {
			pos.y = 50;
			vel.y *= -0.5;
		}
		if (pos.x < 0) {
			pos.x = 0;
			vel.x *= -0.5;
		}
		if (pos.x > 64) {
			pos.x = 64;
			vel.x *= -0.5;
		}

		cam.moveTo(pos);
		cam.translate(Vector2f(10, 0));

		chunk0.render();
		chunk1.render();
		chunk2.render();
		chunk3.render();
		GD.RestoreContext();

		GD.Begin(BITMAPS);
		sprite.render(pos.x, pos.y, angle + PI / 2, .5, 0);
		GD.RestoreContext();

		ui.render();

		GD.swap();
	}
}
