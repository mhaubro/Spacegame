#include "Particle.h"
#include "bullet.h"

particle::particle(Vector2f position, Vector2f velocity, int radius, unsigned int color){
	this->visible = true;
	this->color = color;
	this->radius = radius;
	this->velocity = velocity;
	this->position = position;
}

void particle::applyforces(int dt){
	applydrag(dt);
	applyG(dt);
}

void particle::render(){
	if (!visible){
		return;
	}
	GD.ColorRGB(color);
	GD.PointSize(16*radius);
	GD.Vertex2f(position.x*UNIT16, position.y*UNIT16);
}

void particle::applydrag(int dt){
	float v = velocity.length();
	float d = DRAG(v)*dt;

	velocity -= d;
}

void particle::applyG(int dt){
	velocity.y -= GRAVITY*dt;
}

