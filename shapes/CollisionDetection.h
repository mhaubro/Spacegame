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

//PUBLIC FUNCTIONS
//Collision between two polygons
bool collide(Polygon * A, Vector2f positionA, float angleA, Polygon * B, Vector2f positionB, float angleB, Vector2f& Normal, Vector2f& Point, Vector2f & MTD);
//Collision between polygon and circle
bool collide(Polygon * A, Vector2f positionA, float angleA, Vector2f positionSphere, float radius, Vector2f& Normal, Vector2f& Point, Vector2f & MTD );
//Collision between two circles.
bool collide(Vector2f positionACircle, float radiusA, Vector2f positionBCircle, float radiusB, Vector2f& Normal, Vector2f& Point, Vector2f & MTD);
bool collide(Vector2f positionACircle, float radiusA, Vector2f positionBCircle, float radiusB);


//Terraincollisio
//Polygon
bool TerrainCollide(Polygon * A, Vector2f positionA, float angleA, Vector2f& Normal, Vector2f& Point, Vector2f& MTD);
//point
bool TerrainCollide(Vector2f positionA, float radiusA);


#endif /* SRC_SHAPES_COLLISIONDETECTION_H_ */
