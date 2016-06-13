/*
 * Enemy.cpp
 *
 *  Created on: 06/06/2016
 *      Author: Martin
 */

#include "Enemy.h"
#include "graphics.h"
#include "Game.h"
#include "GD2.h"
#include "World.h"
#include "GraphicsTemplates.h"

#define ENEMYACCELERATION 1.5
//Enemies are only randomly generated. Outcomment this if it is wished they are not.
//Enemy::Enemy(Vector2f pos, Vector2f vel) :
//Entity(),PhysicsObject(1,pos,vel) ,height(pos.y), health(100), lastShot(0), birthTime(timer.getRunTime()),
//braking(false), aiming(false), shooting(false){
//	// Auto-generated constructor stub
//	std::vector<Vector2f> shape;
//	shape.push_back(Vector2f(-.5, -.5));
//	shape.push_back(Vector2f(-.5, .5));
//	shape.push_back(Vector2f(.5, .5));
//	shape.push_back(Vector2f(.5, -.5));
//	angle = 0;
//
//	collisionBox = new Polygon(&position, &angle, 4, shape);
//}

Enemy::Enemy(Vector2f _position, Vector2f _velocity) :
		Entity(), RigidBody(1, .5, _position, 0, _velocity), sprite(
				Enemy2Sprite32, _position, angle, 1), exhaust(
				Animation(ExhaustAnimation8, _position, angle, 1)), height(0), health(
				100), lastShot(0), birthTime(timer.getRunTime()), braking(
				false), aiming(false), shooting(false) {
	std::vector<Vector2f> shape;
	shape.push_back(Vector2f(-.5, -.5));
	shape.push_back(Vector2f(-.5, .5));
	shape.push_back(Vector2f(.5, .5));
	shape.push_back(Vector2f(.5, -.5));
	angle = 0;

	collisionBox = new Polygon(&position, &angle, 4, shape);
}

Enemy::~Enemy() {
	// Auto-generated destructor stub
	if (collisionBox)
		delete collisionBox;
//	if (sprite) delete sprite;
//	if (exhaust) delete exhaust;
//	if (anim) delete anim;
}

void Enemy::render() {

	exhaust.setPosition(Vector2f(0, -1).vertexTransformed(position, angle));
	exhaust.setAngle(angle);
	exhaust.render();

	sprite.setPosition(position);
	sprite.setAngle(angle);
	sprite.render();

}

bool Enemy::collide(Entity entity) { //TODO
	return false;
}

void Enemy::update() {
	//Check if being hit/dead
	checkAlive();

	//Moving and shooting
	bestMove();
	//Updating location
	updatePh();
}

bool Enemy::shotInRange(Vector2f shotVector) {
	return false; //Virtual function
}

bool Enemy::enemyOnScreen() {
	Vector2f dscreen = Vector2f();
	dscreen.x += cam.getX();
	dscreen.y += cam.getY();
	dscreen -= position;
	int screenxLength = SCREEN_WIDTH / CHUNK_SIZE / 2 - 1; //Distance from cam-center to where shooting should be allowed, in units
	int screenyLength = SCREEN_HEIGHT / CHUNK_SIZE / 2 - 1; //Same as above;
	//x markerer om x er inbounds. De to || statements er ift. sammensyningen (1024 -> 0), og objekter på begge sider. Antages at dx ikke kan gå under -chunk*world eller over chunk*world.
	bool x = (dscreen.x > -screenxLength && dscreen.x < screenxLength)
			|| (dscreen.x > CHUNK_SIZE * WORLD_SIZE - screenxLength)
			|| (dscreen.x < -CHUNK_SIZE * WORLD_SIZE - screenxLength);
	bool y = (dscreen.y > -screenyLength && dscreen.y < screenyLength);
	return (x && y);
}

void Enemy::enemyShot() {
	float angle = aimVector.angle();
	Vector2f startpos = getShotPos();
	Vector2f startvel = getShotVel(10, angle);//10 er værdien for friendlyshots as well. Se player::update (righttouch).

	game.mBulletManager.addBullet(new Bullet(startpos, startvel, .2, false));
}

float Enemy::calcAngleToPlayer() {
	return 0;	//Virtual function
}

Vector2f Enemy::getShotPos() {
	return Vector2f();	//Virtual function
}

Vector2f Enemy::getShotVel(float velocity, float angle) {//Makes sure shots are slightly off
	int randangle = random(0, 36);//Der skydes skævt med +- 17.5 grader. -> Dvs
	return FromAngle(velocity, randangle * 3.14 / 180 + angle);	//Returnerer//
}

void Enemy::checkAlive() {
	if (health <= 0) {
		kill();
		//game.score += enemyValue;
	}
	checkBounds();	//Checks if the enemy is far away.
}

void Enemy::bestMove() {
	//Considers what to do:

	if (braking) {	//If the enemy is braking.
		hitBrake();
	}
	if (aiming) {	//If the enemy is aiming.
		aim();
		return;
	}
	if (shooting) {
		shoot();
		return;
	}

	Vector2f VectorToPlayer = player.getPosition() - position;

	//Checks whether it's possible to start a shot.
	if (checkShot(VectorToPlayer)) {//It's possible, checkshot will start it.
		return;
	} else {	//Moves the enemy.
		moveAction(VectorToPlayer);	//Moves the enemy
	}
}

void Enemy::aim() {
	if (aimStart + aimTime < timer.getRunTime()) {
		shotStart = timer.getRunTime();
		shooting = true;//Starts shooting.//TODO MAYBE INSTEAD OF AIM, JUST MAKE A WAIT-FUNCTION?
		aiming = false;	//Stops aiming
	}
}

void Enemy::shoot() {

	if (shotStart + shotTime < timer.getRunTime()) {
		shooting = false;
		return;
	}
	if (lastShot + shotDT < timer.getRunTime()) {
		lastShot = timer.getRunTime();
		enemyShot();
	}
}

bool Enemy::checkShot(Vector2f VectorToPlayer) {
	return false;	//virtual function
}

void Enemy::hitBrake() {
	if (brakeStart + brakeTime < timer.getRunTime()
			or (velocity.x == 0 && velocity.y == 0)) {
		braking = false;
		return;
	}
	if (velocity.x < .1 && velocity.x > -.1) {
		velocity.x = 0;
	} else {
		velocity.x *= .94;
	}
	if (velocity.y < .1 && velocity.y > -.1) {
		velocity.y = 0;
	} else {
		velocity.y *= .94;
	}
}

void Enemy::checkBounds() {
	Vector2f dvec = getShortestDiffVector(position, player.getPosition());
	//
	if (dvec.length() > CHUNK_SIZE * 1.6) {	//Maybe make 1.6 a define value, easier editable?//TODO
		kill();
	}
}

Vector2f Enemy::getShortestDiffVector(Vector2f v1, Vector2f v2) {//Shortest vector that points from v1 to v2, with respect to the world construction
	Vector2f dv = v2 - v1;
	if (dv.x < -CHUNK_SIZE * WORLD_SIZE / 2) {
		dv.x += CHUNK_SIZE * WORLD_SIZE;
	} else if (dv.x > CHUNK_SIZE * WORLD_SIZE / 2) {
		dv.x -= CHUNK_SIZE * WORLD_SIZE;
	}
	return dv;
}

void Enemy::aimAction() {
	brake();
	aimStart = timer.getRunTime();
	aiming = true;
}

//Consider turns.
void Enemy::moveAction(Vector2f vectorToPlayer) {//Maybe use defined vector as the ones in the top of the file.
//Virtual function
}

void Enemy::brake() {
	braking = true;
	brakeStart = timer.getRunTime();
}

float Enemy::getHeight() {
	return (position.y - world.getHeight(position.x));
}

void Enemy::updatePh() {
	updatePhysics();
	if (velocity.length() > maxV) {
		velocity *= 1 / (velocity.length()) * maxV;	//Sets max velocity at 3.
	}
}

Enemy& Enemy::operator=(const Enemy & enemy) {//TODO MAYBE DELETE THIS? Easily editable, but still useless code atm.
	isEDead = enemy.isEDead;
	height = enemy.height;
	shotOffset = enemy.shotOffset;
	health = enemy.health;
	birthTime = enemy.birthTime;
	braking = enemy.braking;
	brakeStart = enemy.brakeStart;
	brakeTime = enemy.brakeTime;
	aiming = enemy.aiming;
	aimStart = enemy.aimStart;
	aimTime = enemy.aimTime;
	shooting = enemy.shooting;
	shotStart = enemy.shotStart;
	shotAngle = enemy.shotAngle;
	lastShot = enemy.lastShot;
	shotDT = enemy.shotDT;
	shotTime = enemy.shotTime;

	return *this;
}

bool Enemy::checkHit(Bullet* _bullet) {
	Vector2f MTD = Vector2f();
	if (collisionBox->Collide(*collisionBox, _bullet->getPosition(),
			_bullet->getRadius(), MTD)) {
		_bullet->kill();
		//game.score += 100;
		health -= 50;
		return true;
	}
	return false;
}
