#include "PhysicsConstants.h"
#include "Vector2f.h"

#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H
class PhysicsObject {

public:
	float mass;
	float radius;
	Vector2f forces;
	Vector2f accelerations;
	Vector2f position;
	Vector2f velocity;



	PhysicsObject(float mass, float radius, Vector2f& position, Vector2f& velocity);

//	Vector2f& getPosition();
//	Vector2f& getVelocity();//Maybe implement?
	void applyAcceleration(Vector2f acc, float time);//Acceleration has been applied for a given time
	void applyAccelerationNG(Vector2f acc, float time);//Acceleration without gravity
	void draw();
	void applyG(float time);


	void addAcceleration(Vector2f v);
	void addForce(Vector2f v);
	void changeState(float dt);

	void checkBounds();
	bool checkCollision(PhysicsObject& ph);
	float findDistMidpoint(PhysicsObject& ph);
	float findDist(PhysicsObject& ph);
	void editCollission(PhysicsObject& ph);//Edits for both
	void editCollissionthis(PhysicsObject& ph);//Edits data for this object with collision from ph.
};
#endif
