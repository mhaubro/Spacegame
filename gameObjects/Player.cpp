#include <vector>
#include "Player.h"

#include "myassets.h"
#include "Mathematics.h"
#include "Game.h"
#include "PhysicsObject.h"
#include "Graphics.h"
#include "Input.h"
#include "bullet.h"

//Vector2f EMPTYVEC = Vector2f();
//Vector2f STARTPOSVEC = Vector2f(0, 10);
//Vector2f STARTVELVEC = Vector2f(6, 4);

Player player = Player(Vector2f(2, 10), Vector2f(0, 0));

Player::Player(Vector2f pos, Vector2f vel) :
		Entity(pos, vel, 1), angle(0), height(0) {

	Vector2f shape1[] = { Vector2f(-1, 1), Vector2f(1, 1), Vector2f(1, -1),
			Vector2f(-1, -1) };

	collisionBox = new Polygon(ph.position, angle, 4, shape1);

	sprite = new Sprite(SPACESHIP_HANDLE, 32, 32, 1);
	exhaust = new Sprite(EXHAUST1_HANDLE, 8, 8, 1);
	anim = new Animation(exhaust, .1, 4);
}

Player::~Player() {
	delete collisionBox;
	delete sprite;
	delete exhaust;
	delete anim;
}

void Player::update() {

	player.angle += input.getRotation() * 0.001;

	while (angle > PI2)
		angle -= PI2;
	while (angle < 0)
		angle += PI2;

	ph.addAcceleration(Vector2f(0, -GRAVITY));

	if (input.getLeftTouch()) {//Changed from input.getThrottle(), to test shots.
		ph.velocity += FromAngle(0.01, angle);
		Vector2f throttle = FromAngle(getMaxThrottle(), angle); //Tilføjer en kraft på 30 newton i den vinkel
		ph.addForce(throttle);
		isThrust = true;
		if (energy > 1)
			energy -= 1;

	} else {
		isThrust = false;
	}

	if (input.getRightTouch() && timer.getRunTime() > lastShot + shotInterval){//Shooting //&&
		lastShot = timer.getRunTime();
		Vector2f bulletpos = player.getShotPos();
		Vector2f bulletv = player.getShotVel(10);//10 = startvelocity of bullet
		bullet b = bullet(bulletpos, bulletv, 2, WHITE);//Param: pos, vel, Radius, color
		bullets.push_back(b);
	}

	ph.update();

	float groundHeight = world.getHeight(ph.position.x);

	player.height = ph.position.y - groundHeight;

	energy += .2;
	energy = clamp(energy, 0, maxEnergy);

	Vector2f mtd = Vector2f();
	Vector2f normal = Vector2f();
	Vector2f tangent = Vector2f();

	if (Polygon::TerrainCollide(*collisionBox, mtd)) {
		GD.ColorRGB(BLUE);

		normal = world.getNormal(ph.position.x, normal);
		tangent = Vector2f::LeftNormal(normal);

		ph.velocity = ph.velocity
				- (normal * (ph.velocity.dotProduct(normal) * 2));

		ph.velocity *= .4;
		//velocity = (velocity * terrainNormal * .4) + (velocity * terrainTangent*.99);

		ph.position += mtd;
	}

}

void Player::render() {

	GD.RestoreContext();
	GD.Begin(BITMAPS);

	if (isThrust) {
		anim->render(Vector2f(-1.2, .65).vertexTransformed(ph.position, angle),
				angle + PI / 2, 1);
		anim->render(Vector2f(-1.2, -.65).vertexTransformed(ph.position, angle),
				angle + PI / 2, 1);
	}
	sprite->render(ph.position.x, ph.position.y, angle + PI / 2, 1, 0);

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

Vector2f Player::getShotPos(){
	Vector2f offset = FromAngle(1.2, angle);
	return ph.position + offset;
}

Vector2f Player::getShotVel(float velocity){
	return FromAngle(velocity, angle);
}
