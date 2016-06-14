/*
 * CollisionDetection.h
 *
 *  Created on: 13/06/2016
 *      Author: Martin
 */

#ifndef SRC_SHAPES_COLLISIONDETECTION_H_
#define SRC_SHAPES_COLLISIONDETECTION_H_

#include "Vector2f.h"
#include "Polygon.h"
#include "Enemy.h"
#include "Bullet.h"

////Collision between objects
bool collide(Enemy * e1, Enemy * e2, Vector2f & Normal, Vector2f & Point, Vector2f & MTD);
bool playerCollide(Enemy * e1, Vector2f & Normal, Vector2f & Point, Vector2f & MTD);
bool collidePlayerBullet(Bullet * b, Vector2f & Normal, Vector2f & Point, Vector2f & MTD);
bool collide(Enemy * e, Bullet * b, Vector2f & Normal, Vector2f & Point, Vector2f & MTD);

//Terraincollision
bool TerrainCollide(Enemy * enemy, Vector2f& Normal, Vector2f& Point, Vector2f& MTD);
//Player
bool TerrainCollidePlayer(Vector2f& Normal, Vector2f& Point, Vector2f& MTD);
//point
bool TerrainCollide(Vector2f positionA, float radiusA);


#endif /* SRC_SHAPES_COLLISIONDETECTION_H_ */
