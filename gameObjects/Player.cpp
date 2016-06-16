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
#include "world.h"
#include "CollisionDetection.h"

Player player = Player(Vector2f(2, 10), Vector2f(0, 0));

static Vector2f arr[] = {Vector2f(-1, 0),Vector2f(-.5, .8), Vector2f(1, 0), Vector2f(-.5, -.8)};
static std::vector<Vector2f> shape(arr, arr + 4);
static Polygon _collisionBox = Polygon(4, shape);

Player::Player(Vector2f pos, Vector2f vel) :
		Entity(), RigidBody(1, .5, pos, 0, vel), sprite(
				Sprite(SpaceShipSprite32, pos, angle, 1)), exhaust1(
				Animation(ExhaustAnimation8, pos, angle, 1)), exhaust2(
				Animation(ExhaustAnimation8, pos, angle, 1)),shotInterval(.2), lastShot(0),enginesOn(false),
				collisionBox(&_collisionBox), height(0), health(MAX_PLAYER_HEALTH), energy(MAX_PLAYER_ENERGY) {
}

Player::~Player() {

}

Polygon * Player::getPolygon(){
	return collisionBox;
}

void Player::update() {

	if (!mIsDead) {
		updateSteering();
		updateCannon();
	}

	player.aVelocity *= .999;
	addAcceleration(Vector2f(0, -GRAVITY));
	updatePhysics();

	float groundHeight = 2;//world.getHeight(position.x);

	player.height = position.y - groundHeight;

	Vector2f mtd = Vector2f();

	Vector2f normal = Vector2f();
	Vector2f tangent = Vector2f();
	Vector2f collisionPoint = Vector2f(10, 10);

	if (TerrainCollidePlayer(normal, collisionPoint, mtd)) {
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

		float damage = (impuls - 5);
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
	energy = clamp(energy, 0, MAX_PLAYER_ENERGY);

	health += .01;

	checkHits();//To place here, or maybe before regen?

	if (health <= 0) {
		mIsDead = true;
		game.setGameOver();
	}
	health = clamp(health, 0, MAX_PLAYER_HEALTH);

}

void Player::checkHits(){
//	if (startT + 5 > timer.getRunTime()){//Grants invulnerability the first five seconds.
//		return;
//	}
//	for(std::vector<Bullet>::iterator it = foebullets.begin(); it != foebullets.end(); ++it) {
//		bullet & b = *it;
//		Vector2f MTD;
//		if (collisionBox->Collide(*collisionBox, b.getPosition(),  b.radius, MTD) && !b.isDead()){
//			b.kill();
//			health -= 100;
//		}
//	}
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

//	GD.ColorRGB(GREEN);
//	collisionBox->render(position, angle);
//	GD.ColorRGB(0xffffff);
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

	if (input.getButton1()) {
		Vector2f throttle = FromAngle(getMaxThrottle(), angle); //Tilføjer en kraft på 30 newton i den vinkel
		addForce(throttle, position);
		enginesOn = true;
		if (energy >= 1)
			energy -= 1;

	}
}

void Player::updateCannon() {
	if (input.getButton3() && timer.getRunTime() > lastShot + shotInterval) { //Shooting //&&
		lastShot = timer.getRunTime();
		Vector2f bulletpos = player.getShotPos();
		Vector2f bulletv = player.getShotVel(20); //10 = startvelocity of bullet

		Bullet * bullet = new Bullet(bulletpos, bulletv, .2, true);
		game.mBulletManager.addBullet(bullet);

		addImpulse(-bulletv * bullet->getMass(), bulletpos);
	}
}

Vector2f Player::getShotPos() {
	Vector2f offset = FromAngle(1.2, angle);
	return position + offset;
}

void Player::startTime(){
	startT = timer.getRunTime();
}

Vector2f Player::getShotVel(float speed) {
	return FromAngle(speed, angle) + velocity * 0.5;
}
