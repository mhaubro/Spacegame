#include <vector>

#include "Game.h"

Game game;
unsigned int score;

Game::Game() :
		running(false), isGameOver(false), ui(), background(), score(0) {
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

	//score = 300;
	Vector2f pos = Vector2f(15,15);
	Vector2f vel = Vector2f(0,0);
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

	//score = score + 1;

	player.update();
	updateEnemies();
	cam.follow(player.getPosition(), player.getVelocity());
	world.update(player.getPosition().x);

}

void Game::render() {

	background.render();
	player.render();
	renderEnemies();
	world.render();
	ui.render();

}

bool Game::isOver(){
	return isGameOver;
}

void Game::setGameOver(){
	isGameOver = true;
}

void Game::renderEnemies(){
	GD.RestoreContext();
	for(std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
		Enemy & e = *it;
		if (!e.isDead)//Might end up being unused since always true.
			e.render();
	}
}

void Game::updateEnemies(){
	for(std::vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
		Enemy & e = *it;
		if (!e.isDead)//Might end up being unused since always true.
			e.update();
	}
	removeEnemies();
}

void Game::removeEnemies(){//Same concept as removebullets
	std::vector<Enemy>::iterator i = enemies.begin();
	while (i != enemies.end()){
		Enemy & e = *i;
		if (e.isDead){//If a bullet is to be deleted, it is swapped with the last element, which is then deleted, since order doesn't matter
			e = enemies[enemies.size()-1];
			enemies.erase(enemies.end());
		} else {
			++i;
		}
	}
}
