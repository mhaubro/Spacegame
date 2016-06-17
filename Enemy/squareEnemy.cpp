//Author: MG

#include "SquareEnemy.h"
#include "Game.h"
#include "Bullet.h"
#include "Player.h"

#define ENEMYACCELERATION 1.5

static Vector2f arr[] = { Vector2f(-.5, -.5), Vector2f(-.5, .5), Vector2f(.5,
		.5), Vector2f(.5, -.5) };
static std::vector<Vector2f> shape(arr, arr + 4);
static Polygon collBox = Polygon(4, shape);
//Stats for the squareEnemy
squareEnemy::squareEnemy(Vector2f _position, Vector2f _velocity) :
		Enemy(&collBox, _position, _velocity), orientRight(true) {
	//Fields from Enemy that must be declared//TODO MAYBE FIND BETTER SOLUTION?
	brakeTime = 1;
	aimTime = 1.75;
	shotDT = .4;
	shotTime = .3;
	shotOffset = Vector2f(.5, 0);
	maxV = 3;
}

squareEnemy::~squareEnemy() { //Maybe call Enemy's deleter?
	// Auto-generated destructor stub
	//Base class Enemy's destructor is autocalled
}

bool squareEnemy::shotInRange(Vector2f shotVector) {
//	float angle = shotVector.angle();
//	if (!enemyOnScreen()) {
//		return false;
//	}
//	if (orientRight) {	//Vinkel enten mindre end pi/3 eller større end 5pi/3
//		return (((angle < PI / 3) && (angle >= 0))
//				or ((angle <= 2 * PI) && (angle > 5 * PI / 3)));
//	} else {
//		return ((angle > (2 * PI / 3)) && (angle < (4 * PI / 3)));
//	}
	return shotVector.length() < 10;
}

float squareEnemy::calcAngleToPlayer() {
	//Returns angle between -pi, pi.
	//Calculate dx, dy with respect to shooting exit.
	//Shoots at random, if player is within the viewing angle, which is 120 degrees (2*60) from the bullet exit.
	Vector2f dPos = player.getPosition() - position;//The vector from enemy to player.
	if (orientRight) {
		dPos -= shotOffset;
	} else {
		dPos += shotOffset;
	}
	return dPos.angle();
}

Vector2f squareEnemy::getShotPos() {
	if (orientRight) {
		return this->getPosition() + Vector2f(.1, 0);
	} else {
		return this->getPosition() + Vector2f(-.1, 0);
	}
}

bool squareEnemy::checkShot(Vector2f VectorToPlayer) {
//	if (VectorToPlayer.x < 0 != orientRight) {
//		turn();
//	}
//	if (orientRight) {
//		VectorToPlayer += shotOffset;
//	} else {
//		VectorToPlayer -= shotOffset;
//	}
	if (shotInRange(VectorToPlayer)) {
		aiming = true;
		aimStart = timer.getRunTime();
		aimVector = VectorToPlayer;
		brake();
		return true;
	}
	return false;
}

void squareEnemy::turn() {	//Turns the orientation of the enemy ship
	orientRight ^= 1;	//Bitflip of boolean true -> f and f-> true.
}

//Consider turns.
void squareEnemy::moveAction(Vector2f vectorToPlayer) {	//Maybe use defined vector as the ones in the top of the file.
	if (getHeight() < 3) {	//If it's flying low, it want to go up
		addAcceleration(Vector2f(0, 4));
		return;
	}
	if (randtime + .8 < timer.getRunTime()){//Sets a general speed for a short time
		rand = (random() % 5)/2;
		randtime = timer.getRunTime();
	}
	if (vectorToPlayer.length() < 5) {
		addAcceleration(-vectorToPlayer.normalized() * 4);
		return;
	}
	if (vectorToPlayer.x < 0) {	//Placed left to the player, but unable to see.
		addAcceleration(Vector2f(-ENEMYACCELERATION*rand, 0));
	} else {	//Placed right of the player, but unable to see.
		addAcceleration(Vector2f(ENEMYACCELERATION*rand, 0));
	}

	if (vectorToPlayer.y < 0) {	//If it's placed above the player
		addAcceleration(Vector2f(0, -ENEMYACCELERATION*rand));
	} else {	//If it's placed below the player
		addAcceleration(Vector2f(0, ENEMYACCELERATION*rand));
	}
}

squareEnemy& squareEnemy::operator=(const squareEnemy & enemy) {//TODO MAYBE DELETE THIS? Easily editable, but still useless code atm.
	height = enemy.height;
	shotOffset = enemy.shotOffset;
	health = enemy.health;
	birthTime = enemy.birthTime;
	orientRight = enemy.orientRight;
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
