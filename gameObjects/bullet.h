

#include "PhysicsConstants.h"
#include "GD2.h"
#include "particle.h"


class bullet{
private:
	void applydrag(int dt);
	void applyG(int dt);

public:
	Vector2f position;
	Vector2f velocity;
	bool visible;//Maybe useless. Rename to collided?? Maybe useful for bullets that's disappeared?
	int radius;
	unsigned int color;

	bullet(Vector2f position, Vector2f velocity, int radius, unsigned int color);

	void applyforces(int dt);
	void render();
};
