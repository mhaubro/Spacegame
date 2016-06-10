#include <vector>
#include "Player.h"

#include "myassets.h"
#include "Mathematics.h"
#include "Game.h"
#include "RigidBody.h"
#include "Graphics.h"
#include "GraphicsTemplates.h"
#include "Input.h"
#include "bullet.h"
#include "StaticAnimationEffect.h"

Player player = Player(Vector2f(2, 10), Vector2f(0, 0));

Player::Player(Vector2f pos, Vector2f vel) :
		Entity(), RigidBody(1, .5, pos, 0, vel), height(0), sprite(
				Sprite(SpaceShipSprite32, pos, angle, 1)), exhaust1(
				Animation(ExhaustAnimation8, pos, angle, 1)), exhaust2(
				Animation(ExhaustAnimation8, pos, angle, 1)) {

	Vector2f shape1[] = { Vector2f(-1, 0), Vector2f(-.5, .8), Vector2f(1, 0),
			Vector2f(-.5, -.8) };

	collisionBox = new Polygon(position, angle, 4, shape1);
}

Player::~Player() {
	delete collisionBox;
}

void Player::update() {

	if (!isDead) {
		updateSteering();

		if (input.getRightTouch()
				&& timer.getRunTime() > lastShot + shotInterval) { //Shooting //&&
			lastShot = timer.getRunTime();
			Vector2f bulletpos = player.getShotPos();
			Vector2f bulletv = player.getShotVel(20); //10 = startvelocity of bullet

			Bullet * bullet = new Bullet(bulletpos, bulletv, .2, true);
			game.mBulletManager.addBullet(bullet);

			addImpulse(-bulletv * bullet->getMass(), bulletpos);
		}
	}

	player.aVelocity *= .99;
	addAcceleration(Vector2f(0, -GRAVITY));

	updatePhysics();

	float groundHeight = world.getHeight(position.x);

	player.height = position.y - groundHeight;

	Vector2f mtd = Vector2f();

	Vector2f normal = Vector2f();
	Vector2f tangent = Vector2f();
	Vector2f collisionPoint = Vector2f(10, 10);

	if (Polygon::TerrainCollide(*collisionBox, mtd, normal, collisionPoint)) {
		normal = normal.normalized();
		tangent = normal.rightNormal();

		Vector2f impulseN = Vector2f();
		Vector2f impulseF = Vector2f();

		position += mtd;

		float ecoff = .5;
		float fcoff = .25;

		Vector2f diff = collisionPoint - position;
		Vector2f pointVel = velocity
				+ diff.rightNormal().normalized()
						* ((diff).length() * aVelocity);

		float impuls = ((pointVel * -(1 + ecoff)).dotProduct(normal))
				/ (1 / mass + powf((diff).crossproduct(normal), 2) / inertia);
		impulseN = normal * impuls;
		impulseF = -pointVel.projectAt(tangent).normalized() * impuls * fcoff;

		addImpulse(impulseN + impulseF, collisionPoint);

		float damage = (impuls-5);
		if (damage > 0) {
			health -= damage * damage;
		}

		if (impuls > 5) {
			StaticAnimationEffect* effect = new StaticAnimationEffect(
					collisionPoint + normal, .8, GroundCollisionAnimation32,
					normal.angle() + PI / 2, 1);
			game.mEffectManager.addEffect(effect);
		} else if (impuls > 2) {
			StaticAnimationEffect* effect = new StaticAnimationEffect(
					collisionPoint + normal * .5, 1.2,
					GroundCollisionAnimation16, normal.angle() + PI / 2, 1);
			game.mEffectManager.addEffect(effect);
		}
	}

	energy += .2;
	energy = clamp(energy, 0, maxEnergy);

	health += .01;
	if (health <= 0) {
		isDead = true;
		game.setGameOver();
	}
	health = clamp(health, 0, maxHealth);

}

void Player::render() {

	GD.RestoreContext();
	//collisionBox->render();
	GD.Begin(BITMAPS);

	if (enginesOn) {
		enginesOn = false;

		exhaust1.setPosition(
				Vector2f(-1.2, .2).vertexTransformed(position, angle));
		exhaust1.setAngle(angle + PI / 2);
		exhaust1.render();

		exhaust2.setPosition(
				Vector2f(-1.2, -.2).vertexTransformed(position, angle));
		exhaust2.setAngle(angle + PI / 2);
		exhaust2.render();
	}

	sprite.setPosition(position);
	sprite.setAngle(angle);
	sprite.render();

}

float Player::getMaxThrottle() {

	float max = 10;
	if (energy <= 1) {
		return 0;
	}

	float maxHeight = 30;
	float minHeight = 10;

	max *= (1
			- (clamp(cam.getY(), minHeight, maxHeight) - minHeight)
					/ (maxHeight - minHeight));

	return max;
}

void Player::updateSteering() {
	float targetAngVel = input.getRotation() * 8;
	if (aVelocity < targetAngVel - .1) {
		addTorque(3);
	}
	if (aVelocity > targetAngVel + .1) {
		addTorque(-3);
	}

	if (input.getLeftTouch()) {
		Vector2f throttle = FromAngle(getMaxThrottle(), angle); //Tilføjer en kraft på 30 newton i den vinkel
		addForce(throttle, position);
		enginesOn = true;
		if (energy >= 1)
			energy -= 1;

	}
}

Vector2f Player::getShotPos() {
	Vector2f offset = FromAngle(1.2, angle);
	return position + offset;
}

Vector2f Player::getShotVel(float speed) {
	return FromAngle(speed, angle) + velocity * 0.5;
}
