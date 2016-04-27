#include "PhysicsObject.h"
#include "PhysicsConstants.h"
#include "math.h"
#include "GD2.h"
#include "graphics.h"

void PhysicsObject::changeState(float dt) {
	accelerations += forces * (1 / mass);
	velocity += accelerations * dt;
	position += velocity * dt;
	accelerations = 0;
	forces = 0;
}

void PhysicsObject::addForce(Vector2f v) {
	forces += v;
}

void PhysicsObject::addAcceleration(Vector2f v) {
	accelerations += v;
}

void PhysicsObject::applyAcceleration(Vector2f acc, float time) { //Acceleration has been applied for a given time
	//Change position
	position += velocity * time;
	velocity += acc * time;
	//Change velocity
	//velocity += acc*time;
	velocity.y += (GRAVITY) * time;	//OBS: Om det skal være - eller +, idet det er ift. tidligere coordinater -> y stiger negativt
}
void PhysicsObject::applyAccelerationNG(Vector2f acc, float time) {	//Acceleration without gravity
	//Som ovenstående, men ingen GRAVITY. GRAVITY er defineret i Physicsconstants.h
	position += velocity * time;
	velocity += acc * time;

}

void PhysicsObject::applyG(float time) {//Acceleration has been applied for a given time
	//Change position
	position.x += (velocity.x * time);
	position.y += (velocity.y * time);
	//Change velocity
	//velocity += acc*time;
	velocity.y += (GRAVITY) * time;	//OBS: Om det skal være - eller +, idet det er ift. tidligere coordinater -> y stiger negativt
}

bool PhysicsObject::checkCollision(PhysicsObject& ph) {
	return (findDist(ph) < 0);
}

bool PhysicsObject::terrainCollision(World& world) {
	return (world.getHeight(position.x) > position.y);
}

float PhysicsObject::findDistMidpoint(PhysicsObject& ph) {
	return sqrtf(
			powf(position.x - ph.position.x, 2)
					+ powf(position.y - ph.position.y, 2));
}

float PhysicsObject::findDist(PhysicsObject& ph) {
	return findDistMidpoint(ph) - (radius + ph.radius);
}

void PhysicsObject::applyCollission(PhysicsObject& ph) {//ph er object 2, this er obj1.
	//Changes velocity of two physicsobjects if they collided
	//https://en.wikipedia.org/wiki/Elastic_collision
	Vector2f v1subv2 = Vector2f(this->velocity - ph.velocity);
	Vector2f x1subx2 = Vector2f(this->position - ph.position);
	Vector2f v2subv1 = Vector2f(ph.velocity - this->velocity);
	Vector2f x2subx1 = Vector2f(ph.position - this->position);

	Vector2f v = velocity
			- x1subx2
					* ((float) (2 * ph.mass * v1subv2.dotProduct(x1subx2)
							/ (this->mass + ph.mass)
							/ (powf(x1subx2.length(), 2))));
	Vector2f phv = ph.velocity
			- x2subx1
					* ((float) (2 * this->mass * v2subv1.dotProduct(x2subx1)
							/ (this->mass + ph.mass)
							/ (powf(x2subx1.length(), 2))));

	GD.cmd_number(40, 70, 16, OPT_SIGNED, v.x);

	velocity.x = v.x;
	velocity.y = v.y;
	ph.velocity.x = phv.x;
	ph.velocity.y = phv.y;

	//this->velocity -= x1subx2*((float)(2*ph.mass*v1subv2.dotProduct(x1subx2)/(this->mass+ph.mass)/(powf(x1subx2.length(),2))));

}
void PhysicsObject::applyCollissionthis(PhysicsObject& ph) {//ph er object 2, this er obj1.
	//Changes velocity of two physicsobjects if they collided
	//https://en.wikipedia.org/wiki/Elastic_collision
	Vector2f v1subv2 = Vector2f(this->velocity - ph.velocity);
	Vector2f x1subx2 = Vector2f(this->position - ph.position);
	//Vector2f v2subv1 = Vector2f(ph.velocity - this->velocity);
	Vector2f x2subx1 = Vector2f(ph.position - this->position);

	this->velocity -= x1subx2
			* ((float) (2 * ph.mass * v1subv2.dotProduct(x1subx2)
					/ (this->mass + ph.mass) / (powf(x1subx2.length(), 2))));

}

void PhysicsObject::applyTerrainCoolision(World& world){
	static Vector2f terrainNormal = Vector2f(); //vector terrain normal
	static Vector2f terrainTangent = Vector2f();

	world.getNormal(position.x, terrainNormal);
	terrainTangent.x = terrainNormal.y;
	terrainTangent.y = -terrainNormal.x;

	velocity = velocity - (terrainNormal * (velocity.dotProduct(terrainNormal)*2));

	velocity *= .4;
	//velocity = (velocity * terrainNormal * .4) + (velocity * terrainTangent*.99);

	position.y = world.getHeight(position.x);

}

void PhysicsObject::draw() {
	GD.PointSize(radius);
	GD.Vertex2f(position.x, position.y);
}

PhysicsObject::PhysicsObject(float mass, float radius, Vector2f& position,
		Vector2f& velocity) :
		mass(mass), radius(radius), position(position), velocity(velocity) {
}

void PhysicsObject::checkBounds() {
	if (position.x < 0 + radius && velocity.x < 0) {
		velocity.x = -velocity.x;
	} else if (position.x + radius > SCREEN_WIDTH * UNIT && (velocity.x > 0)) {
		velocity.x = -velocity.x;
	}
	if (position.y < 0 + radius && (velocity.y < 0)) {
		velocity.y = -velocity.y;
	} else if (position.y + radius > SCREEN_HEIGHT * UNIT && (velocity.y > 0)) {
		velocity.y = -velocity.y;
	}
}

