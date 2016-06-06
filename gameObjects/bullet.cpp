#include <vector>
#include "bullet.h"
#include "Vector2f.h"

std::vector<bullet> friendlybullets;
std::vector<bullet> foebullets;

bullet::bullet(Vector2f& pos, Vector2f& vel, int rad, int col) :
		PhysicsObject(1, pos, vel), startTime(timer.getRunTime()), color(col) {
//	visible = true;
//	color = col;
//	radius = rad;
	//position = Vector2f(pos.x, pos.y);
	//velocity = Vector2f(vel.x, vel.y);
}

void bullet::render() {
	GD.ColorRGB(color);
	GD.Begin(POINTS);
	GD.PointSize(16 * radius);
	cam.Vertex2f(position.x, position.y);
	//GD.cmd_text(40, 40, 16, OPT_SIGNED, "BULLETS");
}

void bullet::update() {
	this->PhysicsObject::update();
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

