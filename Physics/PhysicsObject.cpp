#include "PhysicsObject.h"
#include "PhysicsConstants.h"
#include "GD2.h"
#include "graphics.h"
#include "GameTimer.h"

void PhysicsObject::update() {
	float dt = timer.getDeltaTime();
	accelerations += forces * (1 / mass);
	velocity += accelerations * dt;
	position += velocity * dt;
	accelerations = 0;
	forces = 0;

	if (position.y > 100) {
		position.y = 100;
		velocity.y *= -.1;
	}

	if (position.y < 0) {
		position.y = 0;
		velocity.y *= -.1;
	}

	if (position.x < 0) {
		velocity.x *= -.1;
		position.x = 0;
	}
	if (position.x > 48) {
		velocity.x *= -.1;
		position.x = 48;
	}

}

void PhysicsObject::addForce(Vector2f v) {
	forces += v;
}

void PhysicsObject::addAcceleration(Vector2f v) {
	accelerations += v;
}

bool PhysicsObject::Collision(PhysicsObject& ph) {
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

void PhysicsObject::applyCollission(PhysicsObject& ph1, PhysicsObject& ph2) { //ph er object 2, this er obj1.
	//Changes velocity of two physicsobjects if they collided
	//https://en.wikipedia.org/wiki/Elastic_collision
	Vector2f v1subv2 = Vector2f(ph1.velocity - ph2.velocity);
	Vector2f x1subx2 = Vector2f(ph1.position - ph2.position);
	Vector2f v2subv1 = Vector2f(ph2.velocity - ph1.velocity);
	Vector2f x2subx1 = Vector2f(ph2.position - ph1.position);
	Vector2f pos2subpos1 = Vector2f(ph2.position - ph1.position);

	Vector2f ph1v = velocity
			- x1subx2
					* ((float) (2 * ph2.mass * v1subv2.dotProduct(x1subx2)
							/ (ph1.mass + ph2.mass)
							/ (powf(x1subx2.length(), 2))));
	Vector2f ph2v = ph2.velocity
			- pos2subpos1
					* ((float) (2 * ph1.mass * v2subv1.dotProduct(pos2subpos1)
							/ (ph1.mass + ph2.mass)
							/ (powf(pos2subpos1.length(), 2))));

	//	GD.cmd_number(40,70,16,OPT_SIGNED, v.x);
	Vector2f v = velocity
			- x1subx2
					* ((float) (2 * ph2.mass * v1subv2.dotProduct(x1subx2)
							/ (ph1.mass + ph2.mass)
							/ (powf(x1subx2.length(), 2))));
	Vector2f phv = ph2.velocity
			- x2subx1
					* ((float) (2 * ph1.mass * v2subv1.dotProduct(x2subx1)
							/ (ph1.mass + ph2.mass)
							/ (powf(x2subx1.length(), 2))));
	//GD.cmd_number(40, 70, 16, OPT_SIGNED, v.x);
	ph1.velocity.x = ph1v.x;
	ph1.velocity.y = ph1v.y;
	ph2.velocity.x = ph2v.x;
	ph2.velocity.y = ph2v.y;

}
float PhysicsObject::findDist(PhysicsObject& ph) {
	return findDistMidpoint(ph) - (radius + ph.radius);
}

/*
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

 }*/

void PhysicsObject::applyTerrainCoolision(World& world) {
	static Vector2f terrainNormal = Vector2f(); //vector terrain normal
	static Vector2f terrainTangent = Vector2f();

	world.getNormal(position.x, terrainNormal);
	terrainTangent.x = terrainNormal.y;
	terrainTangent.y = -terrainNormal.x;

	velocity = velocity
			- (terrainNormal * (velocity.dotProduct(terrainNormal) * 2));

	velocity *= .4;
	//velocity = (velocity * terrainNormal * .4) + (velocity * terrainTangent*.99);

	position.y = world.getHeight(position.x);

}

void PhysicsObject::render() {
	GD.PointSize(radius);
	GD.Vertex2f(position.x, position.y);
}

PhysicsObject::PhysicsObject(float mass, Vector2f& position, Vector2f& velocity) :
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

