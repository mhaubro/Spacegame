#include "bullet.h"
#include "Vector2f.h"
#include "GraphicsTemplates.h"

#include <vector>
#include <algorithm>

#include "StaticAnimationEffect.h"

std::vector<Bullet> friendlybullets;
std::vector<Bullet> foebullets;

Bullet::Bullet(Vector2f& pos, Vector2f& vel, float radius, bool _friendly) :
		PhysicsObject(BULLET_MASS, pos, vel), startTime(timer.getRunTime()), mDead(
				false), mFriendly(_friendly), mRadius(radius), mAnimation(
				BulletTemplate, pos, 0, 2) {

}

void Bullet::render() {
	mAnimation.setPosition(position);
	mAnimation.setAngle(velocity.angle());
	mAnimation.render();

}

void Bullet::update() {
	this->PhysicsObject::updatePhysics();
	if (timer.getRunTime() > startTime + Lifespan) {
		mDead = true;
	}

	if (checkEarthCollision()) {
		Vector2f normal;
		world.getNormal(position.x, normal);

		StaticAnimationEffect* effect = new StaticAnimationEffect(
				Vector2f(position.x,world.getHeight(position.x)) + normal, .8, GroundCollisionAnimation32,
				normal.angle() + PI / 2, 1);
		game.mEffectManager.addEffect(effect);
		kill();
	}

}

bool Bullet::checkEarthCollision() {	//Simplified
	return (position.y < world.getHeight(position.x) + mRadius);
}

void Bullet::operator=(const Bullet& b) {
	this->velocity = b.velocity;
	this->position = b.position;
	this->mRadius = b.mRadius;
}

bool Bullet::isDead() {
	return mDead;
}

void Bullet::kill() {
	mDead = true;
}

bool Bullet::getFriendly() {
	return mFriendly;
}

float Bullet::getRadius() {
	return mRadius;
}
