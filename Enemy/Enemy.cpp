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
#define ENEMYACCELERATION 1.5

std::vector<std::tr1::shared_ptr<Enemy> > enemies;

Enemy::Enemy(Vector2f pos, Vector2f vel) :
Entity(),PhysicsObject(1,pos,vel) ,height(pos.y), health(100), isDead(false), lastShot(0), birthTime(timer.getRunTime()) {
	// Auto-generated constructor stub
	std::vector<Vector2f> shape;
	shape.push_back(Vector2f(-.5, -.5));
	shape.push_back(Vector2f(-.5, .5));
	shape.push_back(Vector2f(.5, .5));
	shape.push_back(Vector2f(.5, -.5));

	angle = 0;

	collisionBox = new Polygon(&position, &angle, 4, shape);
}


Enemy::Enemy() : Entity(),PhysicsObject(1) ,height(0), health(100), isDead(false), lastShot(0), birthTime(timer.getRunTime()){
	position = generatePosition();
	height = position.y;
	std::vector<Vector2f> shape;
	shape.push_back(Vector2f(-.5, -.5));
	shape.push_back(Vector2f(-.5, .5));
	shape.push_back(Vector2f(.5, .5));
	shape.push_back(Vector2f(.5, -.5));
	angle = 0;

	collisionBox = new Polygon(&position, &angle, 4, shape);
}

Enemy::~Enemy() {
	// Auto-generated destructor stub
	if (collisionBox) delete collisionBox;
}

Vector2f Enemy::generatePosition(){
	Vector2f startV = Vector2f(cam.getX(), cam.getY());
	int maxX = WORLD_SIZE*CHUNK_SIZE;
	float ranVal = ran.Float(player.getPosition().x);
	float dx = 0.6*CHUNK_SIZE*ran.Float(ranVal);
	float x = cam.getX();
	//Decides whether the enemy will be generated to the right or left of cam.
	if (ranVal < .5){
		x += (CHUNK_SIZE + dx);
	} else {
		x -= (CHUNK_SIZE + dx);
	}
	if (x < 0){
		x+= maxX;
	} else {
		x=(int)(x) % maxX;
	}
		//y is calculated
	float y = world.getHeight(x)+3+12*ran.Float(player.getPosition().y);
	Vector2f startPos = Vector2f(x,y);
	return startPos;
}

void Enemy::render(){
	//collisionBox->render();
	GD.RestoreContext();
	GD.Begin(POINTS);
	GD.PointSize(collisionBox->getHitradius()*16*16);
	GD.ColorRGB(BLUE);
	cam.Vertex2f(position);
	GD.RestoreContext();
}
bool Enemy::collide(Entity entity){//TODO
	return false;
}
void Enemy::update(){
	//Check if being hit/dead
	checkHits();
	checkAlive();


	//Moving and shooting
	bestMove();
	//Updating location
	updatePh();
}

bool Enemy::shotInRange(Vector2f shotVector){
	float angle = shotVector.angle();
	return (((orientRight && angle < 3.14/3 && angle > -3.14/3) or (!orientRight && angle < -2*3.14/3 && angle > 2*3.14/3))  && enemyOnScreen());
}



bool Enemy::enemyOnScreen(){
	Vector2f dscreen = Vector2f();
	dscreen.x += cam.getX();
	dscreen.y += cam.getY();
	dscreen -= position;
	int screenxLength = SCREEN_WIDTH/CHUNK_SIZE/2-1;//Distance from cam-center to where shooting should be allowed, in units
	int screenyLength = SCREEN_HEIGHT/CHUNK_SIZE/2-1;//Same as above;
	//x markerer om x er inbounds. De to || statements er ift. sammensyningen (1024 -> 0), og objekter på begge sider. Antages at dx ikke kan gå under -chunk*world eller over chunk*world.
	bool x = (dscreen.x > -screenxLength && dscreen.x < screenxLength) || (dscreen.x > CHUNK_SIZE*WORLD_SIZE - screenxLength) || (dscreen.x < -CHUNK_SIZE*WORLD_SIZE - screenxLength);
	bool y = (dscreen.y > -screenyLength && dscreen.y < screenyLength);
	return (x && y);
}

void Enemy::enemyShot(float angle){
	Vector2f startpos = getShotPos();
	Vector2f startvel = getShotVel(10, angle);//10 er værdien for friendlyshots as well. Se player::update (righttouch).
	bullet b = bullet(startpos, startvel,.1, 0xffffff);
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
		bullet & b = *it;
		Vector2f MTD;
		if (collisionBox->Collide(*collisionBox, b.getPosition(), b.radius, MTD)){
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
	checkBounds();//Checks if the enemy is far away.
}

void Enemy::kill(){
	isDead = true;
}

void Enemy::bestMove(){
	//Calculates the delta-vector:
	Vector2f VectorToPlayer = player.getPosition() - position;

	//Checks whether the player is in range:
	Vector2f shotVector;
	if (VectorToPlayer.x > 0 && orientRight){
		shotVector = VectorToPlayer + shotOffset;
	} else {
		shotVector = VectorToPlayer + shotOffset;
	}
	if (braking){
		brake();
	}

	float angle = shotVector.angle();

	if (aiming){//If it's aiming it'll only aim
		if (aimStart + aimTime < timer.getRunTime()){
			enemyShot(angle);
			aiming = false;
			shotAction();
		}
		return;
	}

	if (shooting){
		if (shotStart + shotTime < timer.getRunTime() ){
			shooting = false;
			return;
		} else if (lastShot + shotDT < timer.getRunTime() ){
			enemyShot(shotAngle);
			lastShot = timer.getRunTime();
			return;
		}
	}

	if (shotInRange(VectorToPlayer) && !aiming && !shooting){//If the shot is in range, a shotAction will start. The enemy will spend time adjusting the gun, and .5 sec initialising, and then it'll fire.
		if (orientRight && shotVector.x < 0){
			turn();
		} else if (!orientRight && shotVector.x > 0){
			turn();
		}
		shotAngle = angle;
		shotAction(angle);
	} else if (!braking) {//If it isn't in range, the enemy will try to get the player in range.
		moveAction(VectorToPlayer);
	}
}

void Enemy::shotAction(){
	shooting = true;
	shotStart = timer.getRunTime();
	enemyShot(shotAngle);
}

void Enemy::brake(){
	if (brakeStart + brakeTime < timer.getRunTime() or (velocity.x == 0 && velocity.y == 0)){
		braking = false;
		return;
	}
	if (velocity.x < .1 && velocity.x > -.1){
		velocity.x = 0;
	} else {
		velocity.x *= .94;
	}
	if (velocity.y < .1 && velocity.y > -.1){
		velocity.y = 0;
	} else {
		velocity.y *= .94;
	}
}

void Enemy::checkBounds(){
	Vector2f dvec = getShortestDiffVector(position, player.getPosition());

	//
	if (dvec.length() > CHUNK_SIZE*1.6){//Maybe make 1.6 a define value, easier editable?//TODO
		kill();
	}
}

Vector2f Enemy::getShortestDiffVector(Vector2f v1, Vector2f v2){//Shortest vector that points from v1 to v2, with respect to the world construction
	Vector2f dv = v2-v1;
	if (dv.x < -CHUNK_SIZE*WORLD_SIZE/2){
		dv.x += CHUNK_SIZE*WORLD_SIZE;
	} else if(dv.x > CHUNK_SIZE*WORLD_SIZE/2){
		dv.x -= CHUNK_SIZE*WORLD_SIZE;
	}
	return dv;
}

void Enemy::turn(){//Turns the orientation of the enemy ship
	orientRight^=1;//Bitflip of boolean true -> f and f-> true.
}

void Enemy::shotAction(float angle){
	brakeAction();
	aimStart = timer.getRunTime();
	aiming = true;
}

//Consider turns.
void Enemy::moveAction(Vector2f vectorToPlayer){//Maybe use defined vector as the ones in the top of the file.
	if (vectorToPlayer.x < 0){//Placed left to the player, but unable to see.
		addAcceleration(Vector2f(-ENEMYACCELERATION, 0));
	} else {//Placed right of the player, but unable to see.
		addAcceleration(Vector2f(ENEMYACCELERATION, 0));
	}

	if (getHeight() < 8){//If it's flying low, it want to go up
		addAcceleration(Vector2f(0, ENEMYACCELERATION));
	} else if (vectorToPlayer.y < 0){//If it's placed above the player
		addAcceleration(Vector2f(0, -ENEMYACCELERATION));
	} else {//If it's placed below the player
		addAcceleration(Vector2f(0, ENEMYACCELERATION));
	}
}

void Enemy::brakeAction(){
	braking = true;
	brakeStart = timer.getRunTime();
}

float Enemy::getHeight(){
	return (position.y - world.getHeight(position.x));
}

void Enemy::updatePh(){
	updatePhysics();
	if (velocity.length() > 3){
		velocity *=1/(velocity.length())*3;//Sets max velocity at 3.
	}
}



Enemy& Enemy::operator=(const Enemy & enemy){//
	isDead = enemy.isDead;
	height = enemy.height;
	shotOffset = enemy.shotOffset;
	health = enemy.health;
	birthTime = enemy.birthTime;
	orientRight = enemy.orientRight;
	braking = enemy.braking;
	brakeStart = enemy.brakeStart;
	brakeTime = enemy.brakeTime;
	aiming = enemy.aiming;
	aimStart = enemy.aimStart;
	aimTime = enemy.aimTime;
	shooting = enemy.shooting;
	shotStart = enemy.shotStart;
	shotAngle = enemy.shotAngle;
	lastShot = enemy.lastShot;
	shotDT = enemy.shotDT;
	shotTime = enemy.shotTime;

	return *this;
}


