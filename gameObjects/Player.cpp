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

Vector2f normal = Vector2f();
Vector2f tangent = Vector2f();
Vector2f collisionPoint = Vector2f(10, 10);

Player::Player(Vector2f pos, Vector2f vel) :
		Entity(pos, vel, 1), angle(0), height(0) {

	std::vector<Vector2f> shape;
	shape.push_back(Vector2f(-1, 0));
	shape.push_back(Vector2f(-.5, .8));
	shape.push_back(Vector2f(1, 0));
	shape.push_back(Vector2f(-.5, -.8));

	collisionBox = new Polygon(&ph.position, &angle, 4, shape);

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
		player.angle += input.getRotation() * 0.001;

		while (angle > PI2)
			angle -= PI2;
		while (angle < 0)
			angle += PI2;

		if (input.getLeftTouch()) {
			ph.velocity += FromAngle(0.01, angle);
			Vector2f throttle = FromAngle(getMaxThrottle(), angle); //Tilføjer en kraft på 30 newton i den vinkel
			ph.addForce(throttle);
			isThrust = true;
			if (energy > 1){
				energy -= 1;
			}

		}
		if (input.getRightTouch() && timer.getRunTime() > lastShot + shotInterval) { //Shooting //&&
			lastShot = timer.getRunTime();
			Vector2f bulletpos = player.getShotPos();
			Vector2f bulletv = player.getShotVel(20); //10 = startvelocity of bullet
			bullet b = bullet(bulletpos, bulletv, 2, WHITE); //Param: pos, vel, Radius, color
			friendlybullets.push_back(b);
		}
	}

	ph.addAcceleration(Vector2f(0, -GRAVITY));



	ph.update();

	float groundHeight = world.getHeight(ph.position.x);

	player.height = ph.position.y - groundHeight;

	Vector2f mtd = Vector2f();

	if (Polygon::TerrainCollide(*collisionBox, mtd, normal, collisionPoint)) {
		float speed = normal.normalized().dotProduct(ph.velocity);
		if (speed > 5) {
			health -= speed * speed;
		}

		ph.position += mtd;

		tangent = Vector2f::LeftNormal(normal);

		ph.velocity = ph.velocity
				- (normal * (ph.velocity.dotProduct(normal) * 2));

		ph.velocity *= .4;
		//velocity = (velocity * terrainNormal * .4) + (velocity * terrainTangent*.99);

	}

	energy += .2;
	energy = clamp(energy, 0, maxEnergy);

	health += .01;

	checkHits();//To place here, or maybe before regen?

	if (health <= 0) {
		isDead = true;
		game.setGameOver();
	}
	health = clamp(health, 0, maxHealth);

}

void Player::checkHits(){
	if (startT + 5 > timer.getRunTime()){//Grants invulnerability the first five seconds.
		return;
	}
	for(std::vector<bullet>::iterator it = foebullets.begin(); it != foebullets.end(); ++it) {
		bullet & b = *it;
		Vector2f MTD;
		if (collisionBox->Collide(*collisionBox, b.position,  b.radius, MTD)){
			b.kill();
			health -= 100;
		}
	}
}

void Player::render() {

	GD.RestoreContext();
	//collisionBox->render();
	GD.Begin(BITMAPS);

	if (isThrust) {
		isThrust = false;
		anim->render(Vector2f(-1.2, .2).vertexTransformed(ph.position, angle),
				angle + PI / 2, 1);
		anim->render(Vector2f(-1.2, -.2).vertexTransformed(ph.position, angle),
				angle + PI / 2, 1);
	}
	sprite->render(ph.position.x, ph.position.y, angle + PI / 2, 1);

	GD.Begin(POINTS);
	GD.ColorRGB(WHITE);
	GD.PointSize(16 * 4);
	cam.Vertex2f(collisionPoint);

	GD.Begin(LINES);
	renderVector2f(normal,collisionPoint.x,collisionPoint.y,1);

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
	return ph.position + offset;
}

void Player::startTime(){
	startT = timer.getRunTime();
}

Vector2f Player::getShotVel(float velocity) {
	return FromAngle(velocity, angle) + ph.velocity * 0.5;
}
