/*
 * Enemy.cpp
 *
 *  Created on: 06/06/2016
 *      Author: Martin
 */

#include "Enemy.h"

//#define RIGHTVECTOR Vector2f(10, 0);
//#define LEFTVECTOR 	Vector2f(-10, 0);
//#define UPVECTOR 	Vector2f(0, 10);
//#define DOWNVECTOR	Vector2f(0, -10);
#define ENEMYACCELERATION 3


std::vector<Enemy> enemies;

Enemy::Enemy(Vector2f pos, Vector2f vel) :
Entity(pos, vel, 1), height(pos.y), health(100), lastShot(0), isDead(false) {
	// Auto-generated constructor stub
	Vector2f shape1[] = { Vector2f(-.5, -.5), Vector2f(-.5, .5), Vector2f(.5, .5),
				Vector2f(.5, -.5) };
	float angle = 0;
		collisionBox = new Polygon(ph.position, angle, 4, shape1);

		sprite = new Sprite(SPACESHIPS_HANDLE, 32, 32, 0);
		exhaust = new Sprite(SPRITESHEET_HANDLE, 8, 8, 9);
		anim = new Animation(SPRITESHEET_HANDLE,8,8,9,2,0.1);
}

Enemy::~Enemy() {
	// Auto-generated destructor stub
}

void Enemy::render(){
	collisionBox->render();
}
bool Enemy::collide(Entity entity){//TODO
	return false;
}
void Enemy::update(){
	//Check if being hit/dead
	checkHits();
	checkAlive();


	//Moving
	bestMove();
	updatePosition();


	//Shooting
	if (timer.getRunTime() > (lastShot + FIRERATE)){
		lastShot = timer.getRunTime();

		float angle = calcAngleToPlayer();
		//Vurderer om player er i passende synsvidde.
		if (shotInRange(angle)){//Peges mod højre, vinkel ml. -pi/3 og pi/3 (+- 60 grader)
			enemyShot(angle);
		}
	}
}

bool Enemy::shotInRange(float angle){
	return ((orientRight && angle < 3.14/3 && angle > -3.14/3) or (!orientRight && angle < -2*3.14/3 && angle > 2*3.14/3));
}

void Enemy::enemyShot(float angle){
	Vector2f startpos = getShotPos();
	Vector2f startvel = getShotVel(10, angle);//10 er værdien for friendlyshots as well. Se player::update (righttouch).
	bullet b = bullet(startpos, startvel, 2, 0xffffff);
	foebullets.push_back(b);
}

float Enemy::calcAngleToPlayer(){
	//Returns angle between -pi, pi.
	//Calculate dx, dy with respect to shooting exit.
	//Shoots at random, if player is within the viewing angle, which is 120 degrees (2*60) from the bullet exit.
	Vector2f dPos = player.getPosition() - getPosition();//The vector from enemy to player.
	if (orientRight){
		dPos -= shotOffset;
	} else {
		dPos += shotOffset;
	}
	return dPos.angle();
}

Vector2f Enemy::getShotPos(){
	if (orientRight){
		return ph.position + Vector2f(.5, 0);
	} else {
		return ph.position + Vector2f(-.5, 0);
	}
}

Vector2f Enemy::getShotVel(float velocity, float angle){
	int seedvalue = (int)(ph.position.x*50 + angle*50);
	float randangle = ran.Float(seedvalue)*35-17.5;//Der skydes skævt med +- 17.5 grader.
	return FromAngle(velocity, randangle*3.14/180+angle);//Returnerer//
}

void Enemy::checkHits(){
	for(std::vector<bullet>::iterator it = friendlybullets.begin(); it != friendlybullets.end(); ++it) {
		bullet & b = *it;
		Vector2f MTD;
		if (collisionBox->Collide(*collisionBox, b.position, MTD, (float) b.radius)){
			b.kill();
			game.score = game.score + 100;
			health -= 10;
		}
	}
}

void Enemy::checkAlive(){
	if (health <= 0){
		kill();
		game.score += 2500;
	}
}

void Enemy::kill(){
	isDead = true;
}

void Enemy::bestMove(){
	//Calculates the delta-vector:
	Vector2f VectorToPlayer = player.getPosition() - ph.position;

	//Checks whether the player is in range:
	Vector2f shotVector;
	if (VectorToPlayer.x > 0 && orientRight){
		shotVector = VectorToPlayer + shotOffset;
	} else {
		shotVector = VectorToPlayer + shotOffset;
	}

	float angle = shotVector.angle();
	if (shotInRange(angle)){//If the shot is in range, a shotAction will start. The enemy will spend time adjusting the gun, and .5 sec initialising, and then it'll fire.
		if (orientRight && shotVector.x < 0){
			turn();
		} else if (!orientRight && shotVector.x > 0){
			turn();
		}
		shotAction(angle);
	} else {//If it isn't in range, the enemy will try to get the player in range.
		moveAction(VectorToPlayer);
	}
}

void Enemy::turn(){//Turns the orientation of the enemy ship
	orientRight^=1;//Bitflip of boolean true -> f and f-> true.
}

void Enemy::shotAction(float angle){
	brakeAction();

}
//Consider turns.
void Enemy::moveAction(Vector2f vectorToPlayer){//Maybe use defined vector as the ones in the top of the file.
	if (vectorToPlayer.x < 0){//Placed left to the player, but unable to see.
		ph.addAcceleration(Vector2f(-ENEMYACCELERATION, 0));
	} else {//Placed right of the player, but unable to see.
		ph.addAcceleration(Vector2f(ENEMYACCELERATION, 0));
	}

	if (getHeight() < 3){//If it's flying low, it want to go up
		ph.addAcceleration(Vector2f(0, ENEMYACCELERATION));
	} else if (vectorToPlayer.y < 0){//If it's placed above the player
		ph.addAcceleration(Vector2f(0, -ENEMYACCELERATION));
	} else {//If it's placed below the player
		ph.addAcceleration(Vector2f(0, ENEMYACCELERATION));
	}
	ph.update();
}

void Enemy::brakeAction(){
	braking = true;
	brakeStart = timer.getRunTime();
}

float Enemy::getHeight(){
	return (ph.position.y - world.getHeight(ph.position.x));
}

void Enemy::updatePosition(){
	ph.update();
}

