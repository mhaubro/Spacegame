#include <vector>

#include "Game.h"

Game game;
unsigned int score;

Game::Game() :
		running(false), isGameOver(false), ui(), background(), score(42) {
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

	score = 300;

	while (running) {

		input.pull();
		update();
		render();

		poly3.render();

		GD.swap();
	}

}

void Game::update() {

	timer.update();

	score = score + 1;

	player.update();
	cam.follow(player.getPosition(), player.getVelocity());
	world.update(player.getPosition().x);

}

void Game::render() {

	background.render();
	player.render();
	world.render();
	ui.render();

}

bool Game::isOver(){
	return isGameOver;
}

void Game::setGameOver(){
	isGameOver = true;
}
