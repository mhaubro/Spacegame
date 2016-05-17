#include "PhysicsConstants.h"
#include "Vector2f.h"
#include "World.h"

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



	PhysicsObject(float mass, Vector2f& position, Vector2f& velocity);

//	Vector2f& getPosition();
//	Vector2f& getVelocity();//Maybe implement?
	void applyAcceleration(Vector2f acc, float time);//Acceleration has been applied for a given time
	void applyAccelerationNG(Vector2f acc, float time);//Acceleration without gravity
	void draw();
	void applyG(float time);


	void addAcceleration(Vector2f v);
	void addForce(Vector2f v);
	void changeState();

	void checkBounds();
	bool Collision(PhysicsObject& ph);
	bool checkCollision(PhysicsObject& ph);
	bool terrainCollision(World& world);
	float findDistMidpoint(PhysicsObject& ph);
	float findDist(PhysicsObject& ph);
	void applyCollission(PhysicsObject& ph1, PhysicsObject& ph2);//Edits for both
//	void applyCollissionthis(PhysicsObject& ph);//Edits data for this object with collision from ph.
	void applyTerrainCoolision(World& world);
};
#endif
