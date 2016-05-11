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

	float d = 0;
	float length;
	for (int i = 0; i < numVertex; ++i) {
		length = data[i].length();
		if (length > d){
			d = length;
		}
		vertex[i] = Vector2f(data[i]);
	}
	hitRadius = d;
}

Polygon::~Polygon() {
	// TODO Auto-generated destructor stub
}

float Polygon::getHitradius(){
	return hitRadius;
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

bool Polygon::Collide(Polygon A, Polygon B, Vector2f& MTD) {

	if (abs((Vector2f() + A.Position - B.Position).length()) > A.hitRadius + B.hitRadius){
		return false;
	}

	GD.cmd_text(4, 100, 16, OPT_SIGNED, "Can Collide");

	Vector2f dir = Vector2f(0, 1);

	for (int i = 0; i < A.numVertexs; i++) {
		if (RayCast(Ray(A.getVertexTransformed(i), dir), B)) {
			return true;
		}
	}

	for (int i = 0; i < B.numVertexs; i++) {
		if (RayCast(Ray(B.getVertexTransformed(i), dir), A)) {
			return true;
		}
	}

	return false;

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

	Vector2f d = ray.origin - pt0;

	float div = edge.dotProduct(Vector2f::LeftNormal(ray.direction));

	// if the edge and the ray direction is parallel, they will not cross.
	if (Equals(div, 0.0f, 0.001f)) {
		return false;
	}

	float u = determinant(edge, d) / div;
	float v = d.dotProduct(Vector2f::LeftNormal(ray.direction)) / div;

	return u > 0 && v > 0.0f && v <= 1.0f;
}

bool Polygon::RayCast(Ray ray, Polygon polygon) {
	int crossings = 0;

	for (int i = 0; i < polygon.numVertexs; i++) {
		int j = (i + 1) % polygon.numVertexs;
		if (RayIntersectsSegment(ray, polygon.getVertexTransformed(i),
				polygon.getVertexTransformed(j))) {
			crossings++;
		}
	}

	return (crossings > 0) && ((crossings % 2) != 0);
}

