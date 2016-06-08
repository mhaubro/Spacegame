#include <vector>
#include "Player.h"

#include "myassets.h"
#include "Mathematics.h"
#include "Game.h"
#include "RigidBody.h"
#include "Graphics.h"
#include "Input.h"
#include "bullet.h"

//Vector2f EMPTYVEC = Vector2f();
//Vector2f STARTPOSVEC = Vector2f(0, 10);
//Vector2f STARTVELVEC = Vector2f(6, 4);

Player player = Player(Vector2f(2, 10), Vector2f(0, 0));

Vector2f normal = Vector2f();
Vector2f tangent = Vector2f();
Vector2f collisionPoint = Vector2f(10, 10);

Vector2f impulseN = Vector2f();
Vector2f impulseF = Vector2f();

Player::Player(Vector2f pos, Vector2f vel) :
		Entity(), RigidBody(1,1,pos,0,vel) , height(0) {

	Vector2f shape1[] = { Vector2f(-1, 0), Vector2f(-.5, .8), Vector2f(1, 0),
			Vector2f(-.5, -.8) };

	collisionBox = new Polygon(position, angle, 4, shape1);

	sprite = new Sprite(SPACESHIPS_HANDLE, 32, 32, 0);
	exhaust = new Sprite(SPRITESHEET_HANDLE, 8, 8, 9);
	anim = new Animation(SPRITESHEET_HANDLE, 8, 8, 9, 2, 0.1);
}

Player::~Player() {
	delete collisionBox;
	delete sprite;
	delete exhaust;
	delete anim;
}

void Player::update() {

	if (!game.isOver()) {

		player.aVelocity += input.getRotation() * 0.001;
		player.aVelocity *= .99;

		if (input.getLeftTouch()) {
			Vector2f throttle = FromAngle(getMaxThrottle(), angle); //Tilføjer en kraft på 30 newton i den vinkel
			addForce(throttle, position);
			enginesOn = true;
			if (energy >= 1)
				energy -= 1;

		}
	}

	addAcceleration(Vector2f(0, -GRAVITY));

	if (input.getRightTouch() && timer.getRunTime() > lastShot + shotInterval) { //Shooting //&&
		lastShot = timer.getRunTime();
		Vector2f bulletpos = player.getShotPos();
		Vector2f bulletv = player.getShotVel(20); //10 = startvelocity of bullet
		bullet b = bullet(bulletpos, bulletv, 2, WHITE); //Param: pos, vel, Radius, color
		friendlybullets.push_back(b);
	}

	updatePhysics();

	float groundHeight = world.getHeight(position.x);

	player.height = position.y - groundHeight;

	Vector2f mtd = Vector2f();

	if (Polygon::TerrainCollide(*collisionBox, mtd, normal, collisionPoint)) {
		normal = normal.normalized();
		tangent = normal.rightNormal();

		float damage = abs(velocity.scalarProjectAt(normal));
		if (damage > 1) {
			health -= damage * damage;
		}
		position += mtd;

		float ecoff = .5;
		float fcoff = .25;

		Vector2f diff = collisionPoint - position;
		Vector2f pointVel = velocity + diff.rightNormal().normalized() * ((diff).length() * aVelocity);

		float impuls = ((pointVel * -(1 + ecoff)).dotProduct(normal))/(1/mass + powf((diff).crossproduct(normal),2)/inertia);
		impulseN = normal * impuls;
		impulseF = -pointVel.projectAt(tangent).normalized() * impuls * fcoff;

		addImpulse(impulseN + impulseF,collisionPoint);


//		tangent = normal.leftNormal();
//
//		velocity = velocity
//				- (normal * (velocity.dotProduct(normal) * 2));
//
//		velocity *= .4;
		//velocity = (velocity * terrainNormal * .4) + (velocity * terrainTangent*.99);

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
		anim->render(Vector2f(-1.2, .2).vertexTransformed(position, angle),
				angle + PI / 2, 1);
		anim->render(Vector2f(-1.2, -.2).vertexTransformed(position, angle),
				angle + PI / 2, 1);
	}
	sprite->render(position.x, position.y, angle + PI / 2, 1);

	GD.Begin(POINTS);
	GD.ColorRGB(WHITE);
	GD.PointSize(16 * 4);
	cam.Vertex2f(collisionPoint);

	GD.Begin(LINES);
	renderVector2f(impulseN, collisionPoint.x, collisionPoint.y, 1);
	renderVector2f(impulseF, collisionPoint.x, collisionPoint.y, 1);

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

Vector2f Player::getShotPos() {
	Vector2f offset = FromAngle(1.2, angle);
	return position + offset;
}

Vector2f Player::getShotVel(float speed) {
	return FromAngle(speed, angle) + velocity * 0.5;
}
