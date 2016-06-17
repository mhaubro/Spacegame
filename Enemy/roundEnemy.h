//Author: MH

#ifndef SRC_ENEMY_ROUNDENEMY_H_
#define SRC_ENEMY_ROUNDENEMY_H_

#include "Vector2f.h"
#include "Enemy.h"

class RoundEnemy : public Enemy {
protected:


	bool shotInRange(Vector2f shotVector);
	bool checkShot(Vector2f VectorToPlayer);

	float calcAngleToPlayer();

	Vector2f getShotPos();

	void turn();//Turns the orientation of the enemy ship
	void moveAction(Vector2f vectorToPlayer);//Maybe use defined vector as the ones in the top of the file.


public:
	RoundEnemy(Vector2f _position, Vector2f _velocity = Vector2f());
	RoundEnemy& operator=(const RoundEnemy & enemy);
	virtual ~RoundEnemy();
};

#endif /* SRC_ENEMY_ROUNDENEMY_H_ */
