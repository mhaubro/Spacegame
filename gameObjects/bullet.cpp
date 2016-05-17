#include "bullet.h"

bullet::bullet(Vector2f position, Vector2f velocity, int radius, unsigned int color){
	this->visible = true;
	this->color = color;
	this->radius = radius;
	this->velocity = velocity;
	this->position = position;
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
	GD.PointSize(16*radius);
	GD.Vertex2f(position.x*UNIT16, position.y*UNIT16);
}

void bullet::applydrag(int dt){
	float v = velocity.length();
	float d = DRAG(v)*dt;
	velocity -= d;
}

void bullet::applyG(int dt){
	velocity.y -= GRAVITY*dt;
}

