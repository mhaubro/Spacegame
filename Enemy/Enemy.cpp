/*
 * Enemy.cpp
 *
 *  Created on: 20/06/2016
 *      Author: Martin
 */

#include "Enemy.h"

Enemy::Enemy(float _health, Polygon * _collisionBox, Behavior * _behavior,
		Vector2f _position, float _mass, float _inertia, float _angle,
		Vector2f _velocity) :
		Entity(), RigidBody(_mass, _inertia, _position, _angle, _velocity), health(
				_health), collisionBox(_collisionBox), behavior(_behavior) {

	// TODO Auto-generated constructor stub
}

Enemy::~Enemy() {
	// TODO Auto-generated destructor stub
	if (behavior)
		delete behavior;
}

void Enemy::update() {
	behavior->update();
	updatePhysics();
}

void Enemy::render() {

}

bool Enemy::enemyOnScreen() {
	return false;
}
void Enemy::onDeath() {

}

void Enemy::applyDamage(float damage) {
	health -= damage;
	if (health <= 0) {
		kill();
	}
}

void Enemy::makeDesicion() {

}

void Enemy::kill() {
	mIsDead = true;
	onDeath();
}

Polygon * Enemy::getPolygon() {
	return collisionBox;
}

