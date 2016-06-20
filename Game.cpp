//Author: MG

#include "Game.h"

Game game;
unsigned int score;

Game::Game() :
		running(false), isGameOver(false), ui(), background(), score(0), mEffectManager(), mEnemyManager() {
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

	player.startTime();//TODO Maybe delete?
	while (running) {

		input.pull();
		update();
		render();

		GD.swap();
	}

}

void Game::update() {

	timer.update();
	world.update(player.getPosition().x);
	player.update();
	mEnemyManager.update();
	mBulletManager.update();
	mEffectManager.update();
	cam.follow(player.getPosition(), player.getVelocity());

}

void Game::render() {

	background.render();

	player.render();
	world.render();
	mBulletManager.render();
	mEffectManager.render();
	world.render();
	ui.render();
	mEnemyManager.render();

}

bool Game::isOver() {
	return isGameOver;
}

void Game::setGameOver() {
	isGameOver = true;
}
