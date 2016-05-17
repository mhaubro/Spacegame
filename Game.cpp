#include "Game.h"

#include "GD2.h"
#include "Player.h"
#include "myassets.h"
#include "Graphics.h"
#include "Input.h"
#include "World.h"
#include "GameTimer.h"

Game game;

Game::Game() :
		running(false), ui(), background(), score(42) {

}

Game::~Game() {
}

bool Game::init() {

	GD.ClearColorA(255);
	GD.SaveContext();

	return true;
}

void Game::run() {
	running = true;

	float angle = 0;
	Vector2f poly2Pos = Vector2f(20, 10);
	Vector2f shape3[] = { Vector2f(-1, -1), Vector2f(-1, 1), Vector2f(0, 2),
			Vector2f(1, 1), Vector2f(1, -1) };
	Polygon poly3 = Polygon(poly2Pos, angle, 5, shape3);

	while (running) {

		input.pull();

		update();
		render();
		//.Clear();
//		static Vector2f mtd = Vector2f();
//		static Vector2f normal = Vector2f();
//		if (Polygon::Collide(poly1, poly3, mtd)
//				|| Polygon::Collide(poly2, poly3, mtd)) {
//			normal = mtd.normalized();
//
//			player.ph.velocity = player.ph.velocity
//					- (normal * (player.ph.velocity.dotProduct(normal) * 2));
//
//			//velocity = (velocity * terrainNormal * .4) + (velocity * terrainTangent*.99);
//
//			player.ph.velocity *= .4;
//			player.ph.position += mtd;
//			GD.ColorRGB(RED);
//
//			poly1.render();
//		}

//		GD.cmd_text(4, 66, 16, OPT_SIGNED, "POW");
//		GD.cmd_number(36, 66, 16, OPT_SIGNED, mtd.x);

		poly3.render();

		GD.swap();
	}

}

void Game::update() {

	timer.update();

	score = score + 1;

	player.update();
	cam.follow(player.getPosition(), player.getVelocity());

//	for (int i = 0; i < entities.size(); i++) {
//		entities[i].update();
//	}

	world.update(player.getPosition().x);

}

void Game::render() {
	background.render();

//	for (int i = 0; i < entities.size(); i++) {
//		entities[i].render();
//	}

	player.render();

	world.render();
	ui.render();

}
