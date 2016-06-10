/*
 * Enemy.cpp
 *
 *  Created on: 06/06/2016
 *      Author: Martin
 */

#include "Enemy.h"
std::vector<Enemy> enemies;

Enemy::Enemy(Vector2f pos, Vector2f vel) :
Entity(),PhysicsObject(1,pos,vel) ,height(pos.y), health(100), lastShot(0) {
	// Auto-generated constructor stub
	Vector2f shape1[] = { Vector2f(-.5, -.5), Vector2f(-.5, .5), Vector2f(.5, .5),
				Vector2f(.5, -.5) };
	float angle = 0;
		collisionBox = new Polygon(position, angle, 4, shape1);

		sprite = new SpriteTemplate(SPRITESHEET32_HANDLE, 32, 32, 0);
		exhaust = new SpriteTemplate(SPRITESHEET8_HANDLE, 8, 8, 9);
		anim = new AnimationTemplate(SPRITESHEET8_HANDLE,8,8,9,2,0.1);
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



	//Moving
	bestMove();
	updatePosition();


	//Shooting
	if (timer.getRunTime() > (lastShot + FIRERATE)){
		lastShot = timer.getRunTime();

		float angle = calcAngleToPlayer();
		//Vurderer om player er i passende synsvidde.
		if (orientRight && angle < 3.14/3 && angle > -3.14/3){//Peges mod højre, vinkel ml. -pi/3 og pi/3 (+- 60 grader)
			enemyShot(angle);
		} else if (!orientRight && angle < -2*3.14/3 && angle > 2*3.14/3){//Peges mod venstre, vinkel over 2pi/3 eller under -2pi/3
			enemyShot(angle);
		}
	}
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
	Vector2f dPos = player.getPosition() - position;//The vector from enemy to player.
	if (orientRight){
		dPos -= shotOffset;
	} else {
		dPos += shotOffset;
	}
	return dPos.angle();
}

Vector2f Enemy::getShotPos(){
	if (orientRight){
		return position + Vector2f(.5, 0);
	} else {
		return position+ Vector2f(-.5, 0);
	}
}

Vector2f Enemy::getShotVel(float velocity, float angle){
	int seedvalue = (int)(position.x*50 + angle*50);
	float randangle = ran.Float(seedvalue)*35-17.5;//Der skydes skævt med +- 17.5 grader.
	return FromAngle(velocity, randangle*3.14/180+angle);//Returnerer//
}

void Enemy::checkHits(){
	for(std::vector<bullet>::iterator it = friendlybullets.begin(); it != friendlybullets.end(); ++it) {
		bullet b = *it;
		Vector2f MTD;
		if (collisionBox->Collide(*collisionBox, b.getPosition(), b.radius, MTD)){
			game.score = game.score + 10000;
		}


	}
}
void Enemy::bestMove(){

}
void Enemy::updatePosition(){

}

