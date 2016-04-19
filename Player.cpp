#include "Player.h"

Player::Player(float x, float y)
: x(x), y(y), angle(0)
{
}

void Player::update(float t)
{
    x += 1 * t;
}

void Player::render()
{
    
}