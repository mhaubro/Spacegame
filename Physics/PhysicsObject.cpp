#include "PhysicsObject.h"
#include "PhysicsConstants.h"

void PhysicsObject::applyAcceleration(Vector2f acc, float time){//Acceleration has been applied for a given time
	//Change position
	position.x += velocity.x*time;
	position.y += velocity.y*time;
	//Change velocity
	velocity += acc*time;
	velocity.y += (-GRAVITY)*time;//OBS: Om det skal være - eller +, idet det er ift. tidligere coordinater -> y stiger negativt
}
void PhysicsObject::applyAccelerationNG(Vector2f acc, float time){	//Acceleration without gravity
	//Som ovenstående, men ingen GRAVITY. GRAVITY er defineret i Physicsconstants.h
	position.x += velocity.x*time;
	position.y += velocity.y*time;
	velocity += acc*time;

}

bool PhysicsObject::checkCollision(PhysicsObject& ph){
	return findDist > 0;
}

float PhysicsObject::findDistMidpoint(PhysicsObject& ph){
	return sqrtf(powf(position.x-ph.position.x,2) + powf(position.y-ph.position.y,2));
}

float PhysicsObject::findDist(PhysicsObject& ph){
	return findDistMidpoint-(radius+ph.radius);
}

void editCollission(PhysicsObject& ph){
	//Changes velocity of two physicsobjects if they collided
	Vector2f momsum = Vector2f();



}

