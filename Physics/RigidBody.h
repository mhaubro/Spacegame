#include "Vector2f.h"
#include "PhysicsObject.h"

class RigidBody : public PhysicsObject{

protected:

	float inertia;

	float angle;//Angle of unit, radians.
	float aVelocity;
	float aAcceleration;
	float aTorque;

public:

	RigidBody();



};
