/*
 * Polygon.h
 *
 *  Created on: May 2, 2016
 *      Author: mathi
 */

#ifndef SRC_SHAPES_POLYGON_H_
#define SRC_SHAPES_POLYGON_H_

#include "Vector2f.h"
#include "Ray.h"
#include "World.h"

class Polygon {
protected:
	int numVertexs;
	Vector2f* vertex;

	Vector2f getVertexTransformed(int index);

	static bool RayIntersectsSegment(Ray ray, Vector2f pt0, Vector2f pt1);
	static bool RayCast(Ray ray, Polygon polygon);

public:
	const float& angle;
	const Vector2f& Position;

	Polygon(Vector2f &position, float &angle, int numVertex, Vector2f data[]);
	virtual ~Polygon();

	void render();

	static bool Collide(Polygon A, Polygon B, Vector2f& MTD);
	static bool TerrainCollide(Polygon A, World& world, Vector2f& MTD);
	static Vector2f FindMTD(Vector2f* PushVectors, int iNumVectors);

};

#endif /* SRC_SHAPES_POLYGON_H_ */
