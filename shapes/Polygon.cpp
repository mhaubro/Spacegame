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
#include "Mathematics.h"

#define FLOAT_MAX 10000000

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

bool Polygon::Collide(Polygon A, Polygon B,
		Vector2f& MTD) {

	Vector2f dir = Vector2f(0,1);

	return RayCast(Ray(A.Position, dir), B);

}

bool Polygon::TerrainCollide(Polygon A, World& world, Vector2f& MTD) {

	Vector2f temp;
	float height;
	for (int i = 0; i < A.numVertexs; i++) {
		temp = A.getVertexTransformed(i);
		height = world.getHeight(temp.x);
		if (height > temp.y) {
			world.getNormal(temp.x, MTD);
			MTD = MTD * (height - temp.y);
			return true;
		}
	}

	//TODO check if the terrains points is in the polygon.

	return false;
}

Vector2f Polygon::FindMTD(Vector2f* PushVectors, int iNumVectors) {
	Vector2f MTD = PushVectors[0];
	float mind2 = PushVectors[0].dotProduct(PushVectors[0]);
	for (int i = 1; i < iNumVectors; i++) {
		float d2 = PushVectors[i].dotProduct(PushVectors[i]);
		if (d2 < mind2) {
			mind2 = d2;
			MTD = PushVectors[i];
		}
	}
	return MTD;
}

bool Polygon::RayIntersectsSegment(Ray ray, Vector2f pt0, Vector2f pt1) {
	Vector2f edge = pt1 - pt0;
	Vector2f edgeNormal = Vector2f::LeftNormal(edge);
	float normalDotD = edge.dotProduct(ray.direction);

	// if the edge and the ray direction is parallel, they will not cross.
	if (Equals(normalDotD, 0.0f, 0.001f)) {
		return false;
	}

	Vector2f d0 = pt0 - ray.origin;
	Vector2f d1 = pt1 - ray.origin;


	float d = d0.dotProduct(ray.direction);
	float s0 = d0.dotProduct(Vector2f::LeftNormal(ray.direction)) / normalDotD;
	float s1 = d1.dotProduct(Vector2f::LeftNormal(ray.direction)) / normalDotD;

	return d > 0 && s0 > 0 && s0 < 1.0f && s1 > 0 && s1 < 1.0f;
}

bool Polygon::RayCast(Ray ray, Polygon polygon) {
	int crossings = 0;

	for (int i = 0; i < polygon.numVertexs; i++) {
		int j = (i+1)%polygon.numVertexs;
		if (RayIntersectsSegment(ray, polygon.getVertexTransformed(i), polygon.getVertexTransformed(j))) {
			crossings++;
		}
	}

	GD.cmd_text(4, 100,16,OPT_SIGNED, "crossings:");
	GD.cmd_number(4,116, 16, OPT_SIGNED, crossings);

	return (crossings > 0) && ((crossings % 2) != 0);
}

