/*
 * RoundEnemy.cpp
 *
 *  Created on: 06/06/2016
 *      Author: Martin
 */

#include "RoundEnemy.h"
#include "Game.h"
#include "Bullet.h"
#include "Player.h"

#define ENEMYACCELERATION 1.5

	static Vector2f arr[] = {Vector2f(-.5, -.5),Vector2f(-.5, .5), Vector2f(.5, .5), Vector2f(.5, -.5)};

	static std::vector<Vector2f> shape(arr, arr + 4);

static Polygon collisionBox = Polygon(4, shape);

//Stats for the squareEnemy
RoundEnemy::RoundEnemy(Vector2f _position, Vector2f _velocity) : Enemy(collisionBox, _position,_velocity)
{
	//Fields from Enemy that must be declared//TODO MAYBE FIND BETTER SOLUTION?
	brakeTime = 1;
	aimTime = 1.75;
	shotDT = .2;
	shotTime = .3;
	shotOffset = Vector2f(.5, 0);
	maxV = 5;
}

RoundEnemy::~RoundEnemy() {//Maybe call Enemy's deleter?
	// Auto-generated destructor stub
	//Base class Enemy's destructor is autocalled
}

bool RoundEnemy::shotInRange(Vector2f shotVector){//Considers whether the shot is in range. Maybe check if it'll hit any enemies before shooting?
	float angle = shotVector.angle();//TODO
	return false;
}

float RoundEnemy::calcAngleToPlayer(){//TODO Calculates the viewing angle
	//Returns angle between -pi, pi.
	//Calculate dx, dy with respect to shooting exit.
	//Shoots at random, if player is within the viewing angle, which is 120 degrees (2*60) from the bullet exit.

}

Vector2f RoundEnemy::getShotPos(){//Where the shot starts
	//TODO
}

bool RoundEnemy::checkShot(Vector2f VectorToPlayer){

	//TODO from scratch

//	if (VectorToPlayer.x < 0 != orientRight){
//		turn();
//	}
//	if (orientRight){
//		VectorToPlayer += shotOffset;
//	}
//	if (shotInRange(VectorToPlayer)){
//		//position.x += 2;//Used for debugging.
//		aiming = true;
//		aimStart = timer.getRunTime();
//		aimVector = VectorToPlayer;
//		brake();
//		return true;
//	}
	return false;
}

//Consider turns.
void RoundEnemy::moveAction(Vector2f vectorToPlayer){//Maybe use defined vector as the ones in the top of the file.
//TODO
}

RoundEnemy& RoundEnemy::operator=(const RoundEnemy & enemy){//TODO MAYBE DELETE THIS? Easily editable, but still useless code atm.
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
