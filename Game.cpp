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
	Vector2f pos = Vector2f(15, 15);
	Vector2f vel = Vector2f(0, 0);
	Enemy e = Enemy(pos, vel);
	enemies.push_back(e);

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

	world.update(player.getPosition().x);
	player.update();
	updateEnemies();
	cam.follow(player.getPosition(), player.getVelocity());

}

void Game::render() {

	background.render();
	player.render();
	renderEnemies();
	world.render();
	ui.render();

	static float a = 0;
	a += .01;

	while (a > PI * 2)
		a -= PI * 2;

	Vector2f dir = Vector2f(2, 3);
	Vector2f x = FromAngle(4,a);
	Vector2f y = x.rightNormal();

	Vector2f px = dir.projectAt(x);
	Vector2f py = dir.projectAt(y);

	GD.RestoreContext();
	renderVector2f(dir, 10, 10, 1);

	GD.ColorRGB(GREY);
	renderVector2f(x, 10, 10, 1);
	renderVector2f(y, 10, 10, 1);

	GD.ColorRGB(RED);
	renderVector2f(px, 10, 10, 1);

	GD.ColorRGB(BLUE);
	renderVector2f(py, px.x + 10, px.y + 10, 1);

}

bool Game::isOver() {
	return isGameOver;
}

void Game::setGameOver() {
	isGameOver = true;
}

void Game::renderEnemies() {
	for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end();
			++it) {
		Enemy & e = *it;
		e.render();
	}
}

void Game::updateEnemies() {
	for (std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end();
			++it) {
		Enemy & e = *it;
		e.update();
	}
	removeEnemies();
}

void Game::removeEnemies() { //Same concept as removebullets
	std::vector<Enemy>::iterator i = enemies.begin();
	while (i != enemies.end()) {
		Enemy & e = *i;
		if (e.isDead) { //If a bullet is to be deleted, it is swapped with the last element, which is then deleted, since order doesn't matter
			e = enemies[enemies.size() - 1];
			enemies.erase(enemies.end());
		} else {
			++i;
		}
	}
}
