#include "Game.h"

#include "UI.h"
#include "Graphics.h"
#include "Sprite.h"
#include "Chunk.h"
#include "Input.h"
#include "World.h"

Game::Game() :
		running(false), score(42), p() {
	maxHealth = 1000;
	maxEnergy = 1000;

	health = maxHealth / 3;
	energy = maxEnergy / 2;
}

void Game::run() {
	running = true;

	Input in = Input();
	UI ui = UI(this);
	GD.ClearColorRGB(BLACK);

	GD.SaveContext();

	World world = World();
	Vector2f groundNormal = Vector2f();

	Sprite sprite = Sprite(1, 128, 128, 1);

	while (running) {

		in.pull();
		GD.Clear();

		score++;
		p.angle += in.getRotation() * 0.001;

		while (p.angle > PI2)
			p.angle -= PI2;
		while (p.angle < 0)
			p.angle += PI2;

		if (in.getThrodle()) {
			p.vel += FromAngle(0.01, p.angle);
		}

		p.vel += Vector2f(0, -0.001);

		p.pos += p.vel;

		float groundHeight = world.getHeight(p.pos.x);

		if (p.pos.y < groundHeight) {
			p.pos.y = groundHeight;
			p.vel.x *= .5;
			p.vel.y *= -.5;
		}
		if (p.pos.y > 50) {
			p.pos.y = 50;
			p.vel.x *= .5;
			p.vel.y *= -.5;
		}

		world.update(p.pos.x);
		p.height = p.pos.y - groundHeight;

		cam.follow(p.pos,p.vel);

		world.render();

		world.getNormal(p.pos.x, groundNormal);
		renderVector2f(groundNormal, p.pos.x, groundHeight, 1.5);

		GD.Begin(POINTS);
		GD.PointSize(16 * 4);
		GD.ColorRGB(RED);
		cam.Vertex2f(p.pos.x, groundHeight);

		GD.RestoreContext();

		GD.Begin(BITMAPS);
		sprite.render(p.pos.x, p.pos.y, p.angle + PI / 2, .5, 0);
		GD.RestoreContext();

		ui.render();

		GD.swap();
	}
}
