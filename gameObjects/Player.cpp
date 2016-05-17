#include "Player.h"

Vector2f EMPTYVEC = Vector2f();
Vector2f STARTPOSVEC = Vector2f(0, 10);
Vector2f STARTVELVEC = Vector2f(6,4);

Player::Player()
:  angle(0), ph(1, STARTPOSVEC, STARTVELVEC)
{
}

void Player::update(float t)
{

}

void Player::render()
{
    
}
