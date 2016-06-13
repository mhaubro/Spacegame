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
bool Collide(Polygon & A, Vector2f positionA, float angleA, Polygon & B, Vector2f positionB, float angleB, Vector2f & MTD);
//Collision between polygon and circle
bool Collide(Polygon & A, Vector2f positionA, float angleA, Vector2f positionSphere, float radius, Vector2f & MTD );
//Collision between two circles.
bool Collide(Vector2f positionACircle, float radiusA, Vector2f positionBCircle, float radiusB, Vector2f & MTD);




//PRIVATE FUNCTIONS, static -> file-protected. Perhaps empty-namespace instead?
//Vector2f getVertexTransformed(Polygon & A, Vector2f & positionA, float angleA, Vector2f & vertex);
//
//bool AxisSeparatePolygons(Vector2f& Axis, Polygon & A, Vector2f & positionA, Polygon & B, Vector2f & positionB);
//bool AxisSeparatePolygons(Vector2f& Axis, Polygon & A, Vector2f & positionB, Vector2f & B, float radius);
//
//static Vector2f FindMTD(Vector2f* PushVectors, int iNumVectors);
//
//void CalculateInterval(Vector2f & Axis, Polygon & P, Vector2f positionP, float& min,	float& max);
//void CalculateInterval(Vector2f & Axis, Vector2f & Point, float radius, float& min, float& max);

#endif /* SRC_SHAPES_COLLISIONDETECTION_H_ */
