
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
	Enemy * e = new Enemy(pos, vel);
	Enemy * e2 = new Enemy(pos2, vel);
	enemies.push_back(e);
	enemies.push_back(e2);
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

void Game::renderEnemies(){
	GD.RestoreContext();
	for(std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
		Enemy & e = **it;//Derefences the iterator to a pointer -> Dereferences the pointer to a the enemy-object.
		if (!e.isDead)//Might end up being unused since always true.
			e.render();
	}
}

void Game::updateEnemies(){

	for(std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
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
	Vector2f startV = Vector2f();
	int maxX = WORLD_SIZE*CHUNK_SIZE;
	float ranVal = ran.Float(player.getPosition().x);
	float dx = CHUNK_SIZE*ran.Float(ranVal);
	float x = cam.getX();

	//Decides whether the enemy will be generated to the right or left of cam.
	if (ranVal < .5){
		x += 2*(CHUNK_SIZE + dx);
	} else {
		x -= 2*(CHUNK_SIZE + dx);
	}
	if (x < 0){
		x+= maxX;
	} else {
		x=(int)(x) % maxX;
	}

	//y is calculated
	float y = world.getHeight(x)+3+12*ran.Float(player.getPosition().y);

	Vector2f startPos = Vector2f(x,y);

	Enemy * e = new Enemy(startPos, startV);
	enemies.push_back(e);
}

bool isEDead(Enemy * e){
	return (e->isDead);
}

void Game::removeEnemies(){//Same concept as removebullets//TODO CAUSES CRASH
	enemies.erase(std::remove_if(enemies.begin(), enemies.end(), isEDead), enemies.end());
}
