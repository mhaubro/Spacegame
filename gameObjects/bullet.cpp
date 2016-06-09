#include <vector>
#include "bullet.h"
#include "Vector2f.h"
#include "animation.h"

std::vector<bullet> friendlybullets;
std::vector<bullet> foebullets;

bullet::bullet(Vector2f& pos, Vector2f& vel, float radius, int col) :
		PhysicsObject(1, pos, vel), startTime(timer.getRunTime()), anim(
		SPRITESHEET_HANDLE, 8, 8, 11, 2, 0.1), radius(radius), color(col) {
//	visible = true;
//	color = col;
//	radius = rad;
	//position = Vector2f(pos.x, pos.y);
	//velocity = Vector2f(vel.x, vel.y);
}
bullet& bullet::operator=(const bullet& b){
	this->velocity = b.velocity;
	this->position = b.position;
	this->radius = b.radius;
	this->color = b.color;
	this->startTime = b.startTime;
	this->dead = b.dead;
	this->mass = b.mass;
	return *this;
}

void bullet::render() {
//	GD.ColorRGB(color);
//	GD.Begin(POINTS);
//	GD.PointSize(16 * radius);
//	cam.Vertex2f(position.x, position.y);
	anim.render(position, velocity.angle(), 2);

	//GD.cmd_text(40, 40, 16, OPT_SIGNED, "BULLETS");
}

void bullet::update() {
	this->PhysicsObject::updatePhysics();
	if (timer.getRunTime() > startTime + Lifespan) {
		kill();
	}
}

bool bullet::checkEarthCollision() {	//Simplified
	return (position.y < world.getHeight(position.x));
}

bool bullet::isDead() {
	return dead;
}

void bullet::kill() {
	dead = true;
}

