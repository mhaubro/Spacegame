class RigidBody{

protected:
Vector2f position, velocity;
public:
	Vector2f getPosition();
	Vector2f getVelocity();
	void ApplyAcceleration(Vector2f acc, float time);//Acceleration has been applied for a given time
	void ApplyAccelerationNG(Vector2f acc, float time);//Acceleration without gravity
};
