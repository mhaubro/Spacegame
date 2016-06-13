/*
 * CollisionDetection.cpp
 *
 *  Created on: 13/06/2016
 *      Author: Martin
 */
#include <vector>
#include "CollisionDetection.h"
#include "arduino.h"
#include "Polygon.h"


//Empty namespace, file-only.
namespace {
Vector2f getVertexTransformed(Polygon & A, Vector2f positionA, float angleA, Vector2f vertex);
bool AxisSeparatePolygons(Vector2f Axis, Polygon & A, Vector2f positionA, Polygon & B, Vector2f positionB);
bool AxisSeparatePolygons(Vector2f Axis, Polygon & A, Vector2f positionB, Vector2f B, float radius);
static Vector2f FindMTD(Vector2f* PushVectors, int iNumVectors);
void CalculateInterval(Vector2f Axis, Polygon & P, Vector2f positionP, float& min,	float& max);
void CalculateInterval(Vector2f Axis, Vector2f Point, float radius, float& min, float& max);
}





bool collide(Polygon & A, Vector2f positionA, float angleA, Polygon & B, Vector2f positionB, float angleB, Vector2f MTD){

	if (((positionA) - (positionB)).length() > A.getHitradius() + B.getHitradius())
		return false;

	Vector2f Axis[32];
	int iNumAxis = 0;

	//TODO Optimize with direction. no reason to test a normal, that points away.
	//Vector2f dir = A.Position - B.Position;

	for (std::vector<Vector2f>::iterator i = A.getVertex().begin(); i != A.getVertex().end(); ++i) {
		std::vector<Vector2f>::iterator itcopy = i+=1;
		if (itcopy == A.getVertex().end()){
			itcopy = A.getVertex().begin();
		}
		Vector2f E = getVertexTransformed(A, positionA, angleA, (*itcopy)) -
				getVertexTransformed(A, positionA, angleA, (*i));
		Vector2f N = Vector2f(-E.y, E.x);

		if (AxisSeparatePolygons(N, A, positionA, B, positionB))
			return false;

		Axis[iNumAxis++] = N;
	}
	for (std::vector<Vector2f>::iterator i = B.getVertex().begin()+1; i != B.getVertex().end(); ++i) {
		std::vector<Vector2f>::iterator itcopy = i+=1;
		if (itcopy == B.getVertex().end()){
			itcopy = B.getVertex().begin();
		}

		Vector2f E = getVertexTransformed(B, positionB, angleB, (*itcopy))
			- getVertexTransformed(B, positionB, angleB, (*i));
		Vector2f N = Vector2f(-E.y, E.x);
		if (AxisSeparatePolygons(N, A, positionA, B, positionB))
			return false;

		Axis[iNumAxis++] = N;
	}

	// find the MTD among all the separation vectors
	MTD = FindMTD(Axis, iNumAxis);

	// makes sure the push vector is pushing A away from B
	Vector2f D = positionA - positionB;
	if (D.dotProduct(MTD) < 0.0f)
		MTD = -MTD;

	return true;
}


//COLLISION BETWEEN POLYGON AND CIRCLE
bool collide(Polygon & A, Vector2f positionA, float angleA, Vector2f positionCircle, float radius, Vector2f MTD ){
	if ((positionCircle - (positionA)).length() > A.getHitradius() + radius) return false;

	Vector2f Axis[32];
	int iNumAxis = 0;

	//TODO Optimize with direction. no reason to test a normal, that points away.
	//Vector2f dir = A.Position - B.Position;
	for (std::vector<Vector2f>::iterator i = A.getVertex().begin(); i != A.getVertex().end(); i++) {
		std::vector<Vector2f>::iterator itcopy = i+=1;
		if (itcopy == A.getVertex().end()){
			itcopy = A.getVertex().begin();
		}

		Vector2f E = getVertexTransformed(A, positionA, angleA, *itcopy)
				- getVertexTransformed(A, positionA, angleA, *i);
		Vector2f N = Vector2f(-E.y, E.x);

		if (AxisSeparatePolygons(N, A, positionA, positionCircle, radius))
			return false;

		Axis[iNumAxis++] = N;
	}


	for (std::vector<Vector2f>::iterator i = A.getVertex().begin(); i != A.getVertex().end(); i++){
		//TODO Fix push-vector
		float dist = (getVertexTransformed(A, positionA, angleA, *i) - positionCircle).length();
		if (dist < radius){
			return true;
		}
	}

	// find the MTD among all the separation vectors
	MTD = FindMTD(Axis, iNumAxis);

	// makes sure the push vector is pushing A away from B
	//TODO fix pushvector
	Vector2f D = Vector2f() + positionA - positionCircle;
	if (D.dotProduct(MTD) < 0.0f)
		MTD = -MTD;

	return true;
}


//COLLISION BETWEEN THROUGH CIRCLES WITH RADIA.
bool collide(Vector2f positionACircle, float radiusA, Vector2f positionBCircle, float radiusB, Vector2f & MTD){
	//TODO Edit MTD maybe?
	MTD = FromAngle((radiusA + radiusB) - (positionACircle - positionBCircle).length(),(positionACircle - positionBCircle).angle());
	return (((positionACircle - positionBCircle).length()) < ( radiusA + radiusB));
}







//PRIVATE FUNCTIONS, INTERNAL
namespace {
//Head



//Function bodies
Vector2f getVertexTransformed(Vector2f positionP, float angle, Vector2f vertex) {
	return Vector2f(
			FromAngle(1, angle) * vertex.x
					+ FromAngle(1, angle - PI / 2) * vertex.y) + positionP;
}




bool AxisSeparatePolygons(Vector2f& Axis, Polygon & A, Vector2f PositionA, Polygon & B, Vector2f PositionB) {
	float mina, maxa;
	float minb, maxb;

	CalculateInterval(Axis, A, PositionA, mina, maxa);
	CalculateInterval(Axis, B, PositionB, minb, maxb);

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

bool AxisSeparatePolygons(Vector2f Axis, Polygon & A, Vector2f positionA, Vector2f & Point, float radius) {
	float mina, maxa;
	float minb, maxb;

	CalculateInterval(Axis, A, positionA, mina, maxa);
	CalculateInterval(Axis, Point, radius, minb, maxb);

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



Vector2f FindMTD(Vector2f* PushVectors, int iNumVectors) {
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

void CalculateInterval(Vector2f & Axis, Polygon & P, Vector2f positionP, float angleP, float& min,
		float& max) {
	std::vector<Vector2f> vertexes = P.getVertex();
	float d = Axis.dotProduct(getVertexTransformed(positionP, angleP, (*vertexes.begin())));
	min = max = d;
	for (std::vector<Vector2f>::iterator i = vertexes.begin(); i != vertexes.end(); ++i) {
		d = Axis.dotProduct(getVertexTransformed(positionP, angleP, *i));
		if (d < min)
			min = d;
		else if (d > max)
			max = d;
	}
}


void CalculateInterval(Vector2f & Axis, Vector2f & Point, float radius, float& min,
		float& max) {
	float d = Axis.dotProduct(Point);
	float r = radius * Axis.length();
	min = d - r;
	max = d + r;
}
}//Ends namespace
