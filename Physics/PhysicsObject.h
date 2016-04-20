#include "PhysicsConstants.h"
#include "Vector2f.h"

class PhysicsObject {

public:
	Vector2f& position;
	Vector2f& velocity;
	float mass;
	float radius;

//	Vector2f& getPosition();
//	Vector2f& getVelocity();//Maybe implement?
	void applyAcceleration(Vector2f acc, float time);//Acceleration has been applied for a given time
	void applyAccelerationNG(Vector2f acc, float time);//Acceleration without gravity

	bool checkCollision(PhysicsObject& ph);
	float findDistMidpoint(PhysicsObject& ph);
	float findDist(PhysicsObject& ph);
	void editCollission(PhysicsObject& ph);
};
