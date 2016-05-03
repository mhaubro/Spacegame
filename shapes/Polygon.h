/*
 * Polygon.h
 *
 *  Created on: May 2, 2016
 *      Author: mathi
 */

#ifndef SRC_SHAPES_POLYGON_H_
#define SRC_SHAPES_POLYGON_H_

#include "Vector2f.h"

class Polygon {
protected:
	int numVertexs;
	Vector2f* vertex;
	Vector2f& Position;
	float& angle;

	Vector2f getVertexTransformed(int index);

public:
	Polygon(Vector2f &position, float &angle, int numVertex, Vector2f data[]);
	virtual ~Polygon();

	void render();

	static bool Collide(Polygon A, Polygon B);
	static bool AxisSeparatePolygons(Vector2f& Axis, Polygon A, Polygon B);
	static void CalculateInterval(Vector2f Axis, Polygon P, float& min, float& max);
	static Vector2f FindMTD(Vector2f* PushVectors, int iNumVectors);
};

#endif /* SRC_SHAPES_POLYGON_H_ */
