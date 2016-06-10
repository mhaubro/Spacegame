#include <vector>
#include "bullet.h"
#include "Vector2f.h"

std::vector<bullet> friendlybullets;
std::vector<bullet> foebullets;

static AnimationTemplate BulletTemplate = AnimationTemplate(SPRITESHEET_HANDLE,
		8, 8, 11, 2, 0.1);

bullet::bullet(Vector2f& pos, Vector2f& vel, float radius, int col) :
		PhysicsObject(1, pos, vel), startTime(timer.getRunTime()), mAnimation(
				BulletTemplate, pos, 0, 2), radius(radius), color(col) {

}

void bullet::render() {
	mAnimation.setPosition(position);
	mAnimation.setAngle(velocity.angle());
	mAnimation.render();

}

void bullet::update() {
	this->PhysicsObject::updatePhysics();
	if (timer.getRunTime() > startTime + Lifespan) {
		dead = true;
	}
}

bool bullet::checkEarthCollision() {	//Simplified
	return (position.y < world.getHeight(position.x));
}

void bullet::operator=(const bullet& b) {
	this->velocity = b.velocity;
	this->position = b.position;
	this->radius = b.radius;
	this->color = b.color;
}

bool bullet::isDead() {
	return dead;
}

void bullet::kill() {
	dead = true;
}

