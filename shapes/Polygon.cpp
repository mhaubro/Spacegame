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
		if (length > d) {
			d = length;
		}
		vertex[i] = Vector2f(data[i]);
	}
	hitRadius = d;
}

Polygon::~Polygon() {
	// TODO Auto-generated destructor stub
}

float Polygon::getHitradius() {
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

	Vector2f Axis[32];
	int iNumAxis = 0;

	//TODO Optimize with direction. no reason to test a normal, that points away.
	//Vector2f dir = A.Position - B.Position;
	for (int i = 0; i < A.numVertexs; i++) {
		Vector2f E = A.getVertexTransformed((i + 1) % A.numVertexs)
				- A.getVertexTransformed(i);
		Vector2f N = Vector2f(-E.y, E.x);

		if (AxisSeparatePolygons(N, A, B))
			return false;

		Axis[iNumAxis++] = N;
	}
	for (int i = 0; i < B.numVertexs; i++) {
		Vector2f E = B.getVertexTransformed((i + 1) % B.numVertexs)
				- B.getVertexTransformed(i);
		Vector2f N = Vector2f(-E.y, E.x);

		if (AxisSeparatePolygons(N, A, B))
			return false;

		Axis[iNumAxis++] = N;
	}

	// find the MTD among all the separation vectors
	MTD = FindMTD(Axis, iNumAxis);

	// makes sure the push vector is pushing A away from B
	Vector2f D = Vector2f() + A.Position - B.Position;
	if (D.dotProduct(MTD) < 0.0f)
		MTD = -MTD;

	return true;
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

bool Polygon::AxisSeparatePolygons(Vector2f& Axis, Polygon A, Polygon B) {
	float mina, maxa;
	float minb, maxb;

	CalculateInterval(Axis, A, mina, maxa);
	CalculateInterval(Axis, B, minb, maxb);

	if (mina > maxb || minb > maxa)
		return true;

	// find the interval overlap
	float d0 = maxa - minb;
	float d1 = maxb - mina;
	float depth = (d0 < d1) ? d0 : d1;

	// convert the separation axis into a push vector (re-normalise
	// the axis and multiply by interval overlap)
	float axis_length_squared = Axis.x * Axis.x + Axis.y * Axis.y;

	Axis *= depth / axis_length_squared;

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

bool Polygon::RayIntersectsSegment(Ray ray, Vector2f pt0, Vector2f pt1,
		float &t) {
	Vector2f edge = pt1 - pt0;
	Vector2f edgeNormal = Vector2f::LeftNormal(edge);

	Vector2f d = ray.origin - pt0;
	float div = edge.dotProduct(Vector2f::LeftNormal(ray.direction));

	// if the edge and the ray direction is parallel, they will not cross.
	if (Equals(div, 0.0f, 0.001f)) {
		t = FLOAT_MAX;
		return false;
	}

	float u = determinant(edge, d) / div;
	float v = d.dotProduct(Vector2f::LeftNormal(ray.direction)) / div;

	t = u;

	return u > 0 && v > 0.0f && v <= 1.0f;
}

bool Polygon::RayCast(Ray ray, Polygon polygon, float &t, Vector2f& normal) {
	int crossings = 0;

	float distance;

	for (int i = 0; i < polygon.numVertexs; i++) {
		int j = (i + 1) % polygon.numVertexs;
		if (RayIntersectsSegment(ray, polygon.getVertexTransformed(i),
				polygon.getVertexTransformed(j), distance)) {
			crossings++;
			if (distance < t && distance < FLOAT_MAX) {
				t = distance;
				normal = Vector2f::RightNormal(
						polygon.getVertexTransformed(j)
								- polygon.getVertexTransformed(i));
			}
		}
	}

	return (crossings > 0) && ((crossings % 2) != 0);
}

