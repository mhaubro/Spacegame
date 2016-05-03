/*
 * Polygon.cpp
 *
 *  Created on: May 2, 2016
 *      Author: mathi
 */

#include "Polygon.h"
#include "GD2.h"
#include "Graphics.h"
#include "math.h"

Polygon::Polygon(Vector2f &position, float &angle, int numVertex,
		Vector2f data[]) :
		Position(position), angle(angle), numVertexs(numVertex) {
	vertex = new Vector2f[numVertex];
	for (int i = 0; i < numVertex; ++i) {
		vertex[i] = Vector2f(data[i]);
	}
}

Polygon::~Polygon() {
	// TODO Auto-generated destructor stub
}

Vector2f Polygon::getVertexTransformed(int index) {
	return Vector2f(
			FromAngle(1, angle) * vertex[index].x
					+ FromAngle(1, angle - PI / 2) * vertex[index].y) + Position;
}

void Polygon::render() {
	GD.Begin(LINE_STRIP);
	for (int i = 0; i < numVertexs; ++i) {
		cam.Vertex2f(getVertexTransformed(i));
	}
	cam.Vertex2f(getVertexTransformed(0));
}

bool Polygon::Collide(Polygon A, Polygon B) {

	//TODO Optimize with direction. no reason to test a normal, that points away.
	//Vector2f dir = A.Position - B.Position;
	for (int i = 0; i < A.numVertexs; i++) {
		Vector2f E = A.getVertexTransformed((i + 1) % A.numVertexs)
				- A.getVertexTransformed(i);
		Vector2f N = Vector2f(-E.y, E.x);

		if (AxisSeparatePolygons(N, A, B))
			return false;
	}
	for (int i = 0; i < B.numVertexs; i++) {
		Vector2f E = B.getVertexTransformed((i + 1) % B.numVertexs)
				- B.getVertexTransformed(i);
		Vector2f N = Vector2f(-E.y, E.x);

		if (AxisSeparatePolygons(N, A, B))
			return false;
	}

	return true;
}

bool Polygon::TerrainCollide(Polygon A, World& world) {

	Vector2f temp;
	for (int i = 0; i < A.numVertexs; i++) {
		temp = A.getVertexTransformed(i);
		if (world.getHeight(temp.x) > temp.y) {
			return true;
		}
	}

	//TODO check if the terrains points is in the polygon.

	return false;
}

bool Polygon::AxisSeparatePolygons(Vector2f& Axis, Polygon A, Polygon B) {
	float mina, maxa;
	float minb, maxb;

	CalculateInterval(Axis, A, mina, maxa);
	CalculateInterval(Axis, B, minb, maxb);

	if (mina > maxb || minb > maxa)
		return true;

	return false;
}

void Polygon::CalculateInterval(Vector2f Axis, Polygon P, float& min,
		float& max) {
	float d = Axis.dotProduct(P.getVertexTransformed(0));
	min = max = d;
	for (int i = 0; i < P.numVertexs; i++) {
		d = Axis.dotProduct(P.getVertexTransformed(i));
		if (d < min)
			min = d;
		else if (d > max)
			max = d;
	}
}

