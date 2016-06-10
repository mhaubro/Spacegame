#include <vector>
#include "bullet.h"
#include "Vector2f.h"
#include "animation.h"
#include "Enemy.h"

std::vector<bullet> friendlybullets;
std::vector<bullet> foebullets;

bullet::bullet(Vector2f& pos, Vector2f& vel, float radius, int col) :
		PhysicsObject(1, pos, vel), startTime(timer.getRunTime()), anim(
		SPRITESHEET_HANDLE, 8, 8, 11, 2, 0.1), radius(radius), color(col) {
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
	anim.render(position, velocity.angle(), 2);
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

Vector2f getShortestDiffVectorBullet(Vector2f v1, Vector2f v2){//Shortest vector that points from v1 to v2, with respect to the world construction
	Vector2f dv = v2-v1;
	if (dv.x < -CHUNK_SIZE*WORLD_SIZE/2){
		dv.x += CHUNK_SIZE*WORLD_SIZE;
	} else if(dv.x > CHUNK_SIZE*WORLD_SIZE/2){
		dv.x -= CHUNK_SIZE*WORLD_SIZE;
	}
	return dv;
}

bool bullet::outOfBounds(){
	Vector2f camv = Vector2f();
	camv.x = cam.getX();
	camv.y = cam.getY();
	Vector2f diff = getShortestDiffVectorBullet(camv, position);
	return diff.length() > CHUNK_SIZE*1.4;
}

void bullet::kill() {
	dead = true;
}

