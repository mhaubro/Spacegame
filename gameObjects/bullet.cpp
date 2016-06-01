
#include <vector>
#include "bullet.h"
#include "Vector2f.h"

std::vector<bullet> friendlybullets;
std::vector<bullet> foebullets;

bullet::bullet(Vector2f& pos, Vector2f& vel, int rad, int col) : position(pos), velocity(vel), color(col), radius(rad), visible(true){
//	visible = true;
//	color = col;
//	radius = rad;
	//position = Vector2f(pos.x, pos.y);
	//velocity = Vector2f(vel.x, vel.y);
}

void bullet::applyforces(int dt){
	applydrag(dt);
	applyG(dt);
}

void bullet::render(){
	if (!visible){
		return;
	}
	GD.ColorRGB(color);
	GD.Begin(POINTS);
	GD.PointSize(16*radius);
	cam.Vertex2f(position.x, position.y);
	//GD.cmd_text(40, 40, 16, OPT_SIGNED, "BULLETS");
}

void bullet::applydrag(int dt){
	float v = velocity.length();
	float d = DRAG(v)*dt;
	velocity -= d;
}

void bullet::applyG(int dt){
	velocity.y -= GRAVITY*dt;
}

void bullet::turnInvisible(){
	visible = false;
}

void bullet::update(){
	this->position += velocity*timer.getDeltaTime();
}

bool bullet::isVisible(){
	return visible;
}

bool bullet::checkEarthCollision(){//Simplified
	return (position.y < world.getHeight(position.x));
}

void bullet::operator= (const bullet& b){
	this->velocity = b.velocity;
	this->position = b.position;
	this->radius = b.radius;
	this->color = b.color;
	this->visible = b.visible;
}

bool bullet::outOfBounds(){
	float dx = position.x - cam.getX();
	float dy = position.y - cam.getY();

	if (dx > 480/16 || dx < -480/16 || dy > 272/12 || -dy < -272/12){
		return true;
	}
	return false;
}

