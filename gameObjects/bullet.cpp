#include <vector>
#include <algorithm>
#include "bullet.h"
#include "Vector2f.h"
#include "GraphicsTemplates.h"
#include "game.h"
#include "PhysicsConstants.h"
#include "StaticAnimationEffect.h"

#include "CollisionDetection.h"

std::vector<Bullet> friendlybullets;
std::vector<Bullet> foebullets;

Bullet::Bullet(Vector2f& pos, Vector2f& vel, float radius, bool _friendly) :
		Entity(), PhysicsObject(BULLET_MASS, pos, vel), startTime(timer.getRunTime()), mFriendly(_friendly), mRadius(radius), mAnimation(
				BulletTemplate, pos, 0, 2) {

}


Bullet& Bullet::operator=(const Bullet& b){//PROBABLY UNNECESSARY DUE TO DECISION TO USE POINTERS
	this->velocity = b.velocity;
	this->position.x = b.position.x;
	this->position.y = b.position.y;
	this->mDead = b.mDead;
	this->mass = b.mass;
	return *this;
}

void Bullet::render() {
	mAnimation.setPosition(position);
	mAnimation.setAngle(velocity.angle());
	mAnimation.render();
}

void Bullet::update() {
	this->PhysicsObject::updatePhysics();
	if (timer.getRunTime() > startTime + Lifespan) {
		mIsDead = true;
	}

	game.mEnemyManager.checkBulletCollision(this);

	if (TerrainCollide(position, mRadius)) {//Doesn't return the angle//TODO Maybe consider if bullet detection function is overkill in comp. power? - CollisionDetection ->TerrainCollide
		Vector2f normal;
		world.getNormal(position.x, normal);

		StaticAnimationEffect* effect = new StaticAnimationEffect(
				Vector2f(position.x,world.getHeight(position.x)) + normal, .8, GroundCollisionAnimation32,
				normal.angle() + PI / 2, 1);
		game.mEffectManager.addEffect(effect);
		kill();
	}

}


Vector2f getShortestDiffVectorBullet(Vector2f v1, Vector2f v2){//Shortest vector that points from v1 to v2, with respect to the world construction
	Vector2f dv = v2-v1;//Difference vector from v1 to v2.
	if (dv.x < -CHUNK_SIZE*WORLD_SIZE/2){
		dv.x += CHUNK_SIZE*WORLD_SIZE;
	} else if(dv.x > CHUNK_SIZE*WORLD_SIZE/2){
		dv.x -= CHUNK_SIZE*WORLD_SIZE;
	}
	return dv;
}

bool Bullet::outOfBounds(){
	Vector2f camv = Vector2f();
	camv.x = cam.getX();
	camv.y = cam.getY();
	Vector2f diff = getShortestDiffVectorBullet(camv, position);
	return diff.length() > CHUNK_SIZE*1.4;
}

bool Bullet::isDead() {
	return mIsDead;
}

void Bullet::kill() {
	mIsDead = true;
}

bool Bullet::getFriendly() {
	return mFriendly;
}

float Bullet::getRadius() {
	return mRadius;
}
