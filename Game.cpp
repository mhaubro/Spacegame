
#include "Game.h"


Game game;
unsigned int score;

Game::Game() :
		running(false), isGameOver(false), ui(), background(), score(0), mEffectManager() {
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
	std::vector<Vector2f> shape;
	shape.push_back(Vector2f(-1, -1));
	shape.push_back(Vector2f(-1, 1));
	shape.push_back(Vector2f(0, 2));
	shape.push_back(Vector2f(1, 1));
	shape.push_back(Vector2f(1, -1));
	Polygon poly3 = Polygon(&poly2Pos, &angle, 5, shape);

	Vector2f pos = Vector2f(15,15);
	Vector2f pos2 = Vector2f(25,15);
	Vector2f vel = Vector2f(0,0);
	player.startTime();
	std::tr1::shared_ptr<Enemy>  e = std::tr1::shared_ptr<Enemy>(new Enemy(pos, vel));
	std::tr1::shared_ptr<Enemy> e2 = std::tr1::shared_ptr<Enemy>(new Enemy(pos2, vel));
	enemies.push_back((e));
	enemies.push_back((e2));
	while (running) {

		input.pull();
		update();
		render();

		GD.swap();
	}

}

void Game::update() {
score++;
	timer.update();
	world.update(player.getPosition().x);
	player.update();
	updateEnemies();
	mEffectManager.update();
	cam.follow(player.getPosition(), player.getVelocity());
}

void Game::render() {

	background.render();
	player.render();
	renderEnemies();
	world.render();
	mEffectManager.render();
	ui.render();

}

bool Game::isOver() {
	return isGameOver;
}

void Game::setGameOver() {
	isGameOver = true;
}

void Game::renderEnemies(){
	GD.RestoreContext();
	for(std::vector<std::tr1::shared_ptr<Enemy> >::iterator it = enemies.begin(); it != enemies.end(); ++it) {
		Enemy & e = **it;//Derefences the iterator to a pointer -> Dereferences the pointer to a the enemy-object.
		if (!e.isDead)//Might end up being unused since always true.
			e.render();
	}
}

void Game::updateEnemies(){

	for(std::vector<std::tr1::shared_ptr<Enemy> >::iterator it = enemies.begin(); it != enemies.end(); ++it) {
		Enemy & e = **it;//Derefences the iterator to a pointer -> Dereferences the pointer to a the enemy-object.
		if (!e.isDead){//Might end up being unused since always true.
			e.update();
		}
	}

	removeEnemies();

	if (enemies.size() < 4){
		generateEnemy();
	}

}

void Game::generateEnemy(){//Generates an enemy at a random position relative to the camera position
	enemies.push_back(std::tr1::shared_ptr<Enemy>(new Enemy()));
}

bool isEDead(std::tr1::shared_ptr<Enemy> e){//NOTE: MUST BE DEFINED BEFORE REMOVEENEMIES OR IN THE TOP OF THE .CPP-file. Predicate-function.
	return e->isDead;
}

void Game::removeEnemies(){//Same concept as removebullets//TODO CAUSES CRASH
	enemies.erase(std::remove_if(enemies.begin(), enemies.end(), isEDead), enemies.end());
}
