/*
 * Polygon.cpp
 *
 *  Created on: May 2, 2016
 *      Author: mathi
 */

#include <math.h>

#include "Polygon.h"
#include "GD2.h"
#include "Graphics.h"
#include "Mathematics.h"

#define FLOAT_MAX 10000000

Polygon::Polygon(int numVertex,
		std::vector<Vector2f> data) : numVertexs(numVertex) {
	vertex.resize(numVertex);
	vertex = data;

	float d = 0;
	float length;
	for (std::vector<Vector2f>::iterator it = vertex.begin(); it != vertex.end(); ++it ){
		Vector2f & vec = *it;
		length = vec.length();
		if (length > d){
			d = length;
		}
	}
	hitRadius = d;
}

int Polygon::getNumberVertexes(){
	return numVertexs;
}

void Polygon::operator=(const Polygon & polygon){
	this->hitRadius = polygon.hitRadius;
	this->numVertexs = polygon.numVertexs;
	vertex.resize(polygon.vertex.size());
	vertex = polygon.vertex;
}

Polygon::~Polygon() {
	// TODO Auto-generated destructor stub
	//TODO CAUSES PROGRAM CRASH AS OF 07/06
}

std::vector<Vector2f> Polygon::getVertex(){
	return vertex;
}


float Polygon::getHitradius() {
	return hitRadius;
}

Vector2f Polygon::getVertexIndex(int index){
	return vertex[index];
}

void Polygon::render(Vector2f position) {
	GD.ColorRGB(GREEN);
	GD.Begin(LINE_STRIP);

	for (std::vector<Vector2f>::iterator i = vertex.begin(); i != vertex.end(); i++){
		cam.Vertex2f(*i+position);
	}
	cam.Vertex2f(*vertex.begin()+position);
	GD.ColorRGB(0xffffff);
}

//	GD.Begin(LINE_STRIP);
//	for (std::vector<Vector2f>::iterator i = vertex.begin(); i != vertex.end(); ++i) {
//		cam.Vertex2f(getVertexTransformed(i));
//	}
//	cam.Vertex2f(getVertexTransformed(vertex.begin() ));


//bool Polygon::Collide(Polygon A, Polygon B, Vector2f& MTD) {
//
//	if (((*A.Position) - (*B.Position)).length() > A.hitRadius + B.hitRadius) return false;
//
//	Vector2f Axis[32];
//	int iNumAxis = 0;
//
//	//TODO Optimize with direction. no reason to test a normal, that points away.
//	//Vector2f dir = A.Position - B.Position;
//	for (std::vector<Vector2f>::iterator i = A.vertex.begin(); i != A.vertex.end(); ++i) {
//		std::vector<Vector2f>::iterator itcopy = i+=1;
//		if (itcopy == A.vertex.end()){
//			itcopy = A.vertex.begin();
//		}
//		Vector2f E = A.getVertexTransformed(i)
//				- A.getVertexTransformed(i);
//		Vector2f N = Vector2f(-E.y, E.x);
//
//		if (AxisSeparatePolygons(N, A, B))
//			return false;
//
//		Axis[iNumAxis++] = N;
//	}
//	for (std::vector<Vector2f>::iterator i = B.vertex.begin()+1; i != B.vertex.end(); ++i) {
//		std::vector<Vector2f>::iterator itcopy = i+=1;
//		if (itcopy == B.vertex.end()){
//			itcopy = B.vertex.begin();
//		}
//
//		Vector2f E = B.getVertexTransformed(itcopy)
//			- B.getVertexTransformed(i);
//		Vector2f N = Vector2f(-E.y, E.x);
//		if (AxisSeparatePolygons(N, A, B))
//			return false;
//
//		Axis[iNumAxis++] = N;
//	}
//
//	// find the MTD among all the separation vectors
//	MTD = FindMTD(Axis, iNumAxis);
//
//	// makes sure the push vector is pushing A away from B
//	Vector2f D = Vector2f() + *A.Position - *B.Position;
//	if (D.dotProduct(MTD) < 0.0f)
//		MTD = -MTD;
//
//	return true;
//}

//bool Polygon::TerrainCollide(Polygon& A, Vector2f& MTD, Vector2f& Normal, Vector2f& Point) {
//
//	float height = world.getHeight((*A.Position).x);
//
//	if ((*A.Position).y - height > A.hitRadius * 2) return false;
//
//	bool collision = false;
//	float maxDepth = -1;
//	Vector2f temp;
//
//	for (std::vector<Vector2f>::iterator i = A.vertex.begin(); i != A.vertex.end(); ++i) {
//		temp = A.getVertexTransformed(i);
//		height = world.getHeight(temp.x);
//		if (height > temp.y) {
//			if (height - temp.y > maxDepth){
//				maxDepth = height - temp.y;
//				Point = Vector2f(temp.x,height);
//				world.getNormal(temp.x,Normal);
//			}
//			collision = true;
//		}
//	}
//
//	//TODO check if the terrains points is in the polygon.
//
//	MTD = Vector2f(0,maxDepth);
//	return collision;
//}
//
//Vector2f Polygon::FindMTD(Vector2f* PushVectors, int iNumVectors) {
//	Vector2f MTD = PushVectors[0];
//	float mind2 = PushVectors[0].dotProduct(PushVectors[0]);
//	for (int i = 1; i < iNumVectors; i++) {
//		float d2 = PushVectors[i].dotProduct(PushVectors[i]);
//		if (d2 < mind2) {
//			mind2 = d2;
//			MTD = PushVectors[i];
//		}
//	}
//	return MTD;
//}
//
//bool Polygon::AxisSeparatePolygons(Vector2f& Axis, Polygon A, Polygon B) {
//	float mina, maxa;
//	float minb, maxb;
//
//	CalculateInterval(Axis, A, mina, maxa);
//	CalculateInterval(Axis, B, minb, maxb);
//
//	if (mina > maxb || minb > maxa)
//		return true;
//
//	// find the interval overlap
//	float d0 = maxa - minb;
//	float d1 = maxb - mina;
//	float depth = (d0 < d1) ? d0 : d1;
//
//	// convert the separation axis into a push vector (re-normalise
//	// the axis and multiply by interval overlap)
//	float axis_length_squared = Axis.x * Axis.x + Axis.y * Axis.y;
//
//	Axis *= depth / axis_length_squared;
//
//	return false;
//}
//
//void Polygon::CalculateInterval(Vector2f Axis, Polygon P, float& min,
//		float& max) {
//	float d = Axis.dotProduct(P.getVertexTransformed(P.vertex.begin()));
//	min = max = d;
//	for (std::vector<Vector2f>::iterator i = P.vertex.begin(); i != P.vertex.end(); ++i) {
//		d = Axis.dotProduct(P.getVertexTransformed(i));
//		if (d < min)
//			min = d;
//		else if (d > max)
//			max = d;
//	}
//}
//
//bool Polygon::RayIntersectsSegment(Ray ray, Vector2f pt0, Vector2f pt1,
//		float &t) {
//	Vector2f edge = pt1 - pt0;
//	Vector2f edgeNormal = edge.leftNormal();
//
//	Vector2f d = ray.origin - pt0;
//	float div = edge.dotProduct(ray.direction.leftNormal());
//
//	// if the edge and the ray direction is parallel, they will not cross.
//	if (Equals(div, 0.0f, 0.001f)) {
//		t = FLOAT_MAX;
//		return false;
//	}
//
//	float u = determinant(edge, d) / div;
//	float v = d.dotProduct(ray.direction.leftNormal()) / div;
//
//	t = u;
//
//	return u > 0 && v > 0.0f && v <= 1.0f;
//}
//
//bool Polygon::RayCast(Ray ray, Polygon polygon, float &t, Vector2f& normal) {
//	int crossings = 0;
//
//	float distance;
////BROKEN DUE TO CHANGE TO ITERATOR FOCUS. EASILY FIXABLE, BUT UNUSED.
///*	for (int i = 0; i < polygon.numVertexs; i++) {
//		int j = (i + 1) % polygon.numVertexs;
//		if (RayIntersectsSegment(ray, polygon.getVertexTransformed(i),
//				polygon.getVertexTransformed(j), distance)) {
//			crossings++;
//			if (distance < t && distance < FLOAT_MAX) {
//				t = distance;
//				normal = (polygon.getVertexTransformed(j) - polygon.getVertexTransformed(i)).rightNormal();
//			}
//		}
//	}*/
//
//	return (crossings > 0) && ((crossings % 2) != 0);
//}
//
////##############################################
////##############################################
////##METHODS FOR POINTS COLLIDING WITH POLYGONS##
////##############################################
////##############################################
//
//bool Polygon::Collide(Polygon A, Vector2f Point, float radius, Vector2f& MTD) {
//
//	if ((Point - (*A.Position)).length() > A.hitRadius + radius) return false;
//
//	Vector2f Axis[32];
//	int iNumAxis = 0;
//
//	//TODO Optimize with direction. no reason to test a normal, that points away.
//	//Vector2f dir = A.Position - B.Position;
//	for (std::vector<Vector2f>::iterator i = A.vertex.begin(); i != A.vertex.end(); i++) {
//		std::vector<Vector2f>::iterator itcopy = i+=1;
//		if (itcopy == A.vertex.end()){
//			itcopy = A.vertex.begin();
//		}
//
//		Vector2f E = A.getVertexTransformed(itcopy)
//				- A.getVertexTransformed(i);
//		Vector2f N = Vector2f(-E.y, E.x);
//
//		if (AxisSeparatePolygons(N, A, Point, radius))
//			return false;
//
//		Axis[iNumAxis++] = N;
//	}
//
//
//	for (std::vector<Vector2f>::iterator i = A.vertex.begin(); i != A.vertex.end(); i++){
//		//TODO Fix push-vector
//		float dist = (A.getVertexTransformed(i) - Point).length();
//		if (dist < radius){
//			return true;
//		}
//	}
//
//	// find the MTD among all the separation vectors
//	MTD = FindMTD(Axis, iNumAxis);
//
//	// makes sure the push vector is pushing A away from B
//	//TODO fix pushvector
//	Vector2f D = Vector2f() + *A.Position - Point;
//	if (D.dotProduct(MTD) < 0.0f)
//		MTD = -MTD;
//
//	return true;
//}
//
//
//
//bool Polygon::AxisSeparatePolygons(Vector2f& Axis, Polygon A, Vector2f Point, float radius) {
//	float mina, maxa;
//	float minb, maxb;
//
//	CalculateInterval(Axis, A, mina, maxa);
//	CalculateInterval(Axis, Point, radius, minb, maxb);
//
//	if (mina > maxb || minb > maxa)
//		return true;
//
//	// find the interval overlap
//	float d0 = maxa - minb;
//	float d1 = maxb - mina;
//	float depth = (d0 < d1) ? d0 : d1;
//
//	// convert the separation axis into a push vector (re-normalise
//	// the axis and multiply by interval overlap)
//	float axis_length_squared = Axis.x * Axis.x + Axis.y * Axis.y;
//
//	Axis *= depth / axis_length_squared;
//
//	return false;
//}
//
//void Polygon::CalculateInterval(Vector2f Axis, Vector2f Point, float radius, float& min,
//		float& max) {
//	float d = Axis.dotProduct(Point);
//	float r = radius * Axis.length();
//	min = d - r;
//	max = d + r;
//}
