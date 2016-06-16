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

public:

	Polygon(int numVertex, std::vector<Vector2f> data);
	Polygon(const Polygon & polygon);
	virtual ~Polygon();
	void operator=(const Polygon & poly);

	std::vector<Vector2f> getVertex();
	Vector2f getVertexIndex(int i);
	float getHitradius();

	int getNumberVertexes();

	void render(Vector2f position, float angle);
};

#endif /* SRC_SHAPES_POLYGON_H_ */
