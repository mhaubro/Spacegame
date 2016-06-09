/*
 * Polygon.h
 *
 *  Created on: May 2, 2016
 *      Author: mathi
 */

#ifndef SRC_SHAPES_POLYGON_H_
#define SRC_SHAPES_POLYGON_H_

#include <vector>
#include "Vector2f.h"
#include "Ray.h"
#include "World.h"

class Polygon {
protected:
	int numVertexs;
	std::vector<Vector2f> vertex;

	float hitRadius;

	Vector2f getVertexTransformed(std::vector<Vector2f>::iterator it);

	static bool RayIntersectsSegment(Ray ray, Vector2f pt0, Vector2f pt1,
			float &t);
	static bool RayCast(Ray ray, Polygon polygon, float &t, Vector2f& normal);

	Vector2f * Position;//Maybe outcomment this one, and make Poisition an input parameter?

public:
	float * angle;

	float getHitradius();

	Polygon(Vector2f * position, float * angle, int numVertex, std::vector<Vector2f> data);

	Polygon(const Polygon & polygon);
	void operator=(const Polygon & poly);
	virtual ~Polygon();

	void render();
	void setPosition(Vector2f position);
	static bool Collide(Polygon A, Polygon B, Vector2f& MTD);
	static bool Collide(Polygon A, Vector2f PointB, float radius, Vector2f& MTD);

	static bool TerrainCollide(Polygon& A, Vector2f& MTD, Vector2f& Normal, Vector2f& Point);
	static bool AxisSeparatePolygons(Vector2f& Axis, Polygon A, Polygon B);
	static bool AxisSeparatePolygons(Vector2f& Axis, Polygon A, Vector2f B, float radius);
	static void CalculateInterval(Vector2f Axis, Polygon P, float& min, float& max);
	static void CalculateInterval(Vector2f Axis, Vector2f Point, float radius, float& min,
			float& max);
	static Vector2f FindMTD(Vector2f* PushVectors, int iNumVectors);

};

#endif /* SRC_SHAPES_POLYGON_H_ */
