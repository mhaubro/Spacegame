/*
 * KamikazeBehavior.cpp
 *
 *  Created on: 20/06/2016
 *      Author: Martin
 */

#include "KamikazeBehavior.h"
#include "Mathematics.h"
#include "Arduino.h"
#include "Vector2f.h"
#include "Enemy.h"
#include "Behavior.h"
#include "Player.h"

KamikazeBehavior::KamikazeBehavior(Enemy * _enemy) : Behavior(_enemy){
	// TODO Auto-generated constructor stub

}

KamikazeBehavior::~KamikazeBehavior() {
	// TODO Auto-generated destructor stub
}

void KamikazeBehavior::update(){
	//Calc angle from enemy to player.
	float dirAngle = (player.getPosition() - enemy->getPosition()).angle();
	float velAngle = enemy->getVelocity().angle();
//Calculates steering angle
	float dAngle = clamp(2*(loop(dirAngle-velAngle, -PI, PI)), -PI, PI);



	//Ensures steering angle is not bigger than +-180 degrees
	//dAngle = clamp(targetAngle - enemy->getAngle(), -PI, PI) + enemy->getVelocity().angle();
	//Loops to make sure the angle is in bounds.
	float targetAngVel = loop(dAngle+velAngle, 0, 2*PI);
	enemy->targetAngle = FromAngle(2, targetAngVel);

//	//Adds rotation depending on what angle the enemy has to go
//	if (enemy->getAngularVelocity() < targetAngVel){
//		enemy->addTorque(1);
//	} else {
//		enemy->addTorque(-1);
//	}
	enemy->setAngle(targetAngVel);
	enemy->addForce(FromAngle(1, enemy->getAngle()), enemy->getPosition());



	//APPLYING DRAG
	float force = enemy->getVelocity().length();
	force *= force;

	float factor = (100 - enemy->getPosition().y)/100;
	factor = factor * factor * factor*.5;
	enemy->addForce(Vector2f(-enemy->getVelocity().normalized() * force * .1 * factor), enemy->getPosition());
}

