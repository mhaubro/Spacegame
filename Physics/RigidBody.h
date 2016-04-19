class RigidBody{

protected:
Vector2F position, velocity;
public:
	Vector2F getPosition();
	Vector2F getVelocity();
	void ApplyAcceleration(Vector2F acc, float time);//Acceleration has been applied for a given time
	void ApplyAccelerationNG(Vector2F acc, float time);//Acceleration without gravity
};
