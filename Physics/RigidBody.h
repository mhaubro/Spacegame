#include "Vector2f.h"
#include "PhysicsObject.h"

class RigidBody : public PhysicsObject{

protected:

	float angle;//Angle of unit, radians.
	float angularAcc;
	//Collection of stuff that makes up the rigid body
	bool checkCollision();

public:
	void applyForces(Vector2f forces, float dt);


	RigidBody();

};
