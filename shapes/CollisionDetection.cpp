//Author: MH

#include <vector>
#include "CollisionDetection.h"
#include "arduino.h"
#include "Polygon.h"
#include "Graphics.h"
#include "GD2.h"
#include "Mathematics.h"
#include "player.h"

//Empty namespace, file-only.
namespace {
Vector2f getVertexTransformed(Vector2f positionA, float angleA,
		Vector2f vertex);
bool AxisSeparatePolygons(Vector2f& Axis, Polygon * A, Vector2f PositionA,
		float angleA, Polygon * B, Vector2f PositionB, float angleB);
bool AxisSeparatePolygons(Vector2f Axis, Polygon * A, Vector2f positionA,
		float angleA, Vector2f positionB, float radius);
void FindData(Vector2f* Axis, int iNumVectors, Vector2f & Normal,
		Vector2f & point, Vector2f & MTD, Polygon * A, Vector2f positionA,
		Polygon * B, Vector2f positionB);
void FindData(Vector2f* PushVectors, int iNumVectors, Vector2f & Normal,
		Vector2f & point, Vector2f & MTD, Polygon * A, Vector2f positionA,
		Vector2f positionB, float radiusB);
void CalculateInterval(Vector2f & Axis, Polygon * P, Vector2f positionP,
		float angleP, float& min, float& max);
void CalculateInterval(Vector2f & Axis, Vector2f & Point, float radius,
		float& min, float& max);
//Polygon
bool TerrainCollide(Polygon * A, Vector2f positionA, float angleA,
		Vector2f& Normal, Vector2f& Point, Vector2f& MTD);

//#######################################
//###########COLLIDING METHODS###########

//Collision between two polygons
bool collide(Polygon * A, Vector2f positionA, float angleA, Polygon * B,
		Vector2f positionB, float angleB, Vector2f& Normal, Vector2f& Point,
		Vector2f & MTD);
//Collision between polygon and circle
bool collide(Polygon * A, Vector2f positionA, float angleA,
		Vector2f positionSphere, float radius, Vector2f& Normal,
		Vector2f& Point, Vector2f & MTD);
//Collision between two circles.
bool collide(Vector2f positionACircle, float radiusA, Vector2f positionBCircle,
		float radiusB, Vector2f& Normal, Vector2f& Point, Vector2f & MTD);
bool collide(Vector2f positionACircle, float radiusA, Vector2f positionBCircle,
		float radiusB);
}

//PLAYER-ENEMY COLLISION and ENEMY-ENEMY-COLLISION
//############################################
//############################################
//############################################
bool collide(Enemy * e1, Enemy * e2, Vector2f & Normal, Vector2f & Point,
		Vector2f & MTD) {
	return collide(e1->getPolygon(), e1->getPosition(), e1->getAngle(),
			e2->getPolygon(), e2->getPosition(), e2->getAngle(), Normal, Point,
			MTD);
}

bool playerCollide(Enemy * e1, Vector2f & Normal, Vector2f & Point,
		Vector2f & MTD) {
	return collide(player.getPolygon(), player.getPosition(), player.getAngle(),
			e1->getPolygon(), e1->getPosition(), e1->getAngle(), Normal, Point,
			MTD);
}

//PLAYER-BULLET COLLISION
bool collidePlayerBullet(Bullet * b, Vector2f & Normal, Vector2f & Point,
		Vector2f & MTD) {
	return collide(player.getPolygon(), player.getPosition(), player.getAngle(),
			b->getPosition(), b->getRadius(), Normal, Point, MTD);
}

//ENEMY-BULLET COLLISION
bool collide(Enemy * e, Bullet * b, Vector2f & Normal, Vector2f & Point,
		Vector2f & MTD) {
	return collide(e->getPolygon(), e->getPosition(), e->getAngle(),
			b->getPosition(), b->getRadius(), Normal, Point, MTD);
}

//###########################################
//#######TERRAINCOLLISION####################

//Enemy
bool TerrainCollide(Enemy * e, Vector2f& Normal, Vector2f& Point,
		Vector2f& MTD) {
	return TerrainCollide(e->getPolygon(), e->getPosition(), e->getAngle(),
			Normal, Point, MTD);
}
//Player
bool TerrainCollidePlayer(Vector2f& Normal, Vector2f& Point, Vector2f& MTD) {
	return TerrainCollide(player.getPolygon(), player.getPosition(),
			player.getAngle(), Normal, Point, MTD);
}
//Bullet
bool TerrainCollide(Bullet * b, Vector2f & Normal, Vector2f & Point,
		Vector2f & MTD) {
	return TerrainCollide(b->getPosition(), b->getRadius()); //TODO Maybe add Point/MTD for this?
}

bool TerrainCollide(Vector2f positionA, float radiusA) {
	//Tests against five locations - 0 degrees, 180 degrees, 235 degrees, 270 degrees and 315 degrees (All classical degrees).
	if (positionA.y > world.getHeight(positionA.x) + 2) { //May give a false result, but is very highly unlikely.
		return false;
	}

	if (positionA.y < world.getHeight(positionA.x + radiusA) or //0 degrees
			positionA.y < world.getHeight(positionA.x - radiusA) or //180 degrees
			positionA.y - radiusA < world.getHeight(positionA.x) or //270 degrees (Straight down)
			positionA.y - radiusA * SQRT2HALF
					< world.getHeight(positionA.x - radiusA * SQRT2HALF) or //235 degrees
			positionA.y - radiusA * SQRT2HALF
					< world.getHeight(positionA.x + radiusA * SQRT2HALF)) { //315 degrees
		return true;
	}
	return false;
}

//PRIVATE FUNCTIONS, INTERNAL
namespace {
//POLYGON-POLYGON COLLISION AS WELL AS HELPING FUNCTIONS
bool collide(Polygon * A, Vector2f positionA, float angleA, Polygon * B,
		Vector2f positionB, float angleB, Vector2f& Normal, Vector2f& Point,
		Vector2f & MTD) {

	if (((positionA) - (positionB)).length()
			> A->getHitradius() + B->getHitradius())
		return false;

	Vector2f Axis[32];

	int iNumAxis = 0;

	for (std::vector<Vector2f>::iterator i = A->getVertex().begin();
			i != A->getVertex().end(); ++i) {
		std::vector<Vector2f>::iterator itcopy = i;
		itcopy++;
		if (itcopy == A->getVertex().end()) {
			itcopy = A->getVertex().begin();
		}
		Vector2f E = getVertexTransformed(positionA, angleA, (*itcopy))
				- getVertexTransformed(positionA, angleA, (*i));
		Vector2f N = Vector2f(-E.y, E.x);

		if (AxisSeparatePolygons(N, A, positionA, angleA, B, positionB, angleB))
			return false;

		Axis[iNumAxis++] = N;
	}

	for (std::vector<Vector2f>::iterator i = B->getVertex().begin() + 1;
			i != B->getVertex().end(); ++i) {
		std::vector<Vector2f>::iterator itcopy = i;
		itcopy++;
		if (itcopy == B->getVertex().end()) {
			itcopy = B->getVertex().begin();
		}

		Vector2f E = getVertexTransformed(positionB, angleB, (*itcopy))
				- getVertexTransformed(positionB, angleB, (*i));
		Vector2f N = Vector2f(-E.y, E.x);
		if (AxisSeparatePolygons(N, B, positionB, angleB, A, positionA, angleA))
			return false;

		Axis[iNumAxis++] = N;
	}

	// find the MTD among all the separation vectors
	FindData(Axis, iNumAxis, Normal, Point, MTD, A, positionA, B, positionB);

	// makes sure the push vector is pushing A away from B


	return true;
}

//COLLISION BETWEEN POLYGON AND CIRCLE
bool collide(Polygon * A, Vector2f positionA, float angleA,
		Vector2f positionCircle, float radius, Vector2f& Normal,
		Vector2f& Point, Vector2f &MTD) {

	if ((positionCircle - positionA).length() > A->getHitradius() + radius)
		return false;

	Vector2f Axis[32];
	int iNumAxis = 0;

	//TODO Optimize with direction. no reason to test a normal, that points away.
	//Vector2f dir = A.Position - B.Position;

	for (std::vector<Vector2f>::iterator i = A->getVertex().begin();
			i != A->getVertex().end(); ++i) {

		std::vector<Vector2f>::iterator itcopy = i += 1;

		if (itcopy == A->getVertex().end()) {
			itcopy = A->getVertex().begin();
		}

		Vector2f E = getVertexTransformed(positionA, angleA, *itcopy)
				- getVertexTransformed(positionA, angleA, *i);
		Vector2f N = Vector2f(-E.y, E.x);

		if (AxisSeparatePolygons(N, A, positionA, angleA, positionCircle,
				radius))
			return false;

		Axis[iNumAxis++] = N;
	}

	for (std::vector<Vector2f>::iterator i = A->getVertex().begin();
			i != A->getVertex().end(); i++) {
		//TODO Fix push-vector
		float dist = (getVertexTransformed(positionA, angleA, *i)
				- positionCircle).length();
		if (dist < radius) {
			return true;
		}
	}

	// find the MTD among all the separation vectors
	FindData(Axis, iNumAxis, Normal, Point, MTD, A, positionA, positionCircle,
			radius);

	// makes sure the push vector is pushing A away from B
	//TODO fix pushvector
	Vector2f D = Vector2f() + positionA - positionCircle;

	return true;
}

//COLLISION BETWEEN THROUGH CIRCLES WITH RADIA.
bool collide(Vector2f positionACircle, float radiusA, Vector2f positionBCircle,
		float radiusB, Vector2f& Normal, Vector2f& Point, Vector2f & MTD) {
	//TODO Edit MTD maybe? Should work, but is MTD, Point and Normal necessary?
	MTD = FromAngle(
			(radiusA + radiusB) - (positionACircle - positionBCircle).length(),
			(positionACircle - positionBCircle).angle());

	//Pointet i cirkel A, hvor cirkel B går ind.
	Point = (positionACircle - positionBCircle) * radiusA
			/ (positionACircle - positionBCircle).length();

	Normal = MTD.normalized();

	return (((positionACircle - positionBCircle).length()) < (radiusA + radiusB));
}

bool collide(Vector2f positionACircle, float radiusA, Vector2f positionBCircle,
		float radiusB) {
	return (((positionACircle - positionBCircle).length()) < (radiusA + radiusB));
}

bool TerrainCollide(Polygon * A, Vector2f positionA, float angleA,
		Vector2f& Normal, Vector2f& Point, Vector2f& MTD) {

	float height = world.getHeight(positionA.x);

	if (positionA.y - height > A->getHitradius() * 2)
		return false;

	bool collision = false;
	float maxDepth = -1;
	Vector2f temp;

	for (std::vector<Vector2f>::iterator i = A->getVertex().begin();
			i != A->getVertex().end(); ++i) {
		temp = getVertexTransformed(positionA, angleA, *i);
		height = world.getHeight(temp.x);
		if (height > temp.y) {
			if (height - temp.y > maxDepth) {
				maxDepth = height - temp.y;
				Point = Vector2f(temp.x, height);
				world.getNormal(temp.x, Normal);
			}
			collision = true;
		}
	}

	//TODO check if the terrains points is in the polygon.

	MTD = Vector2f(0, maxDepth);
	return collision;
}
//
//bool TerrainCollide(Vector2f positionA, float radiusA){
//	//Tests against five locations - 0 degrees, 180 degrees, 235 degrees, 270 degrees and 315 degrees (All classical degrees).
//	if (positionA.y < world.getHeight(positionA.x) + 2){//May give a false result, but is very highly unlikely.
//		return false;
//	}
//
//	if (positionA.y < world.getHeight(positionA.x+radiusA) or //0 degrees
//			positionA.y < world.getHeight(positionA.x - radiusA) or//180 degrees
//			positionA.y - radiusA < world.getHeight(positionA.x) or//270 degrees (Straight down)
//			positionA.y - radiusA*SQRT2HALF < world.getHeight(positionA.x - radiusA*SQRT2HALF) or//235 degrees
//			positionA.y - radiusA*SQRT2HALF < world.getHeight(positionA.x + radiusA*SQRT2HALF)){//315 degrees
//		return true;
//	}
//	return false;
//}
//
////PRIVATE FUNCTIONS, INTERNAL
//namespace {
//Head

//Function bodies
Vector2f getVertexTransformed(Vector2f positionP, float angle,
		Vector2f vertex) {
	return Vector2f(
			FromAngle(1, angle) * vertex.x
					+ FromAngle(1, angle - PI / 2) * vertex.y) + positionP;
}

bool AxisSeparatePolygons(Vector2f& Axis, Polygon * A, Vector2f PositionA,
		float angleA, Polygon * B, Vector2f PositionB, float angleB) {
	float mina, maxa;
	float minb, maxb;

	CalculateInterval(Axis, A, PositionA, angleA, mina, maxa);
	CalculateInterval(Axis, B, PositionB, angleB, minb, maxb);

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

bool AxisSeparatePolygons(Vector2f Axis, Polygon * A, Vector2f positionA,
		float angleA, Vector2f positionB, float radius) {
	float mina, maxa;
	float minb, maxb;

	CalculateInterval(Axis, A, positionA, angleA, mina, maxa);
	CalculateInterval(Axis, positionB, radius, minb, maxb);

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

void FindData(Vector2f* Axis, int iNumVectors, Vector2f & Normal,
		Vector2f & point, Vector2f & MTD, Polygon * A, Vector2f positionA,
		Polygon * B, Vector2f positionB) {
	MTD = Axis[0];
	float mind2 = Axis[0].dotProduct(Axis[0]);
	point = A->getVertexIndex(0) + positionA + MTD;
	int aNumVertexes = A->getNumberVertexes();
	int index = 0;
	bool AinB = false;
	for (int i = 1; i < iNumVectors; i++) {
		float d2 = Axis[i].dotProduct(Axis[i]);
		if (d2 < mind2) {
			index = i;
			mind2 = d2;
			MTD = Axis[i];
			if (i < aNumVertexes) {
				AinB = false;
			} else {
				AinB = true;
			}
		}
	}

//	Vector2f D = positionB - positionA;
	if (AinB){
		MTD *= -1;
	}


	Normal = (MTD.normalized());

	//Finding point, linear time. Done by iterating through the opposing polygon, the one "inside" (Which a pushvector will push out)
	//http://elancev.name/oliver/2D%20polygon_files/image006a.gif -> Done by iterating through the
	//Equivalent of Vertex A. The correct point is the point where the dotproduct of the normal
	//And the point-coordinate is the smallest.
	Polygon * pushOutPoly = 0;
	Vector2f pushOutPos;

	//Selects the right polygon, the one "inside" the other.
	if (!AinB) {
		pushOutPoly = B;
		pushOutPos = positionB;
	} else {
		pushOutPoly = A;
		pushOutPos = positionA;
	}

	float minDot = Normal.dotProduct(pushOutPoly->getVertex()[0]);
	point = pushOutPos + pushOutPoly->getVertex()[0] + MTD;

	for (std::vector<Vector2f>::iterator i = pushOutPoly->getVertex().begin()
			+ 1;//TODO Make more safe (Starting at begin + 1 may be ill advised if the vector only has 1 vertex. This should not be possible, though.
	i != pushOutPoly->getVertex().end(); ++i) {
		float val = Normal.dotProduct(*i);
		if (val < minDot) {
			minDot = val;
			point = pushOutPos + *i + MTD;
		}
	}

}


void FindData(Vector2f* PushVectors, int iNumVectors, Vector2f & Normal,
		Vector2f & point, Vector2f & MTD, Polygon * A, Vector2f positionA,
		Vector2f positionB, float radiusB) {
	MTD = PushVectors[0];
	float mind2 = PushVectors[0].dotProduct(PushVectors[0]);
	point = A->getVertexIndex(0) + positionA;
	for (int i = 1; i < iNumVectors; i++) {
		float d2 = PushVectors[i].dotProduct(PushVectors[i]);
		if (d2 < mind2) {
			mind2 = d2;
			MTD = PushVectors[i];
			//Since
		}
	}

	Vector2f D = positionA - positionB;

	if (D.dotProduct(MTD) < 0.0f)
		MTD = -MTD;


	Normal = (MTD.normalized());
	point = positionB + ((positionA - positionB).normalized()) * radiusB;

}

void CalculateInterval(Vector2f & Axis, Polygon * P, Vector2f positionP,
		float angleP, float& min, float& max) {
	std::vector<Vector2f> vertexes = P->getVertex();
	float d = Axis.dotProduct(
			getVertexTransformed(positionP, angleP, (*vertexes.begin())));
	min = max = d;
	for (std::vector<Vector2f>::iterator i = vertexes.begin();
			i != vertexes.end(); ++i) {
		d = Axis.dotProduct(getVertexTransformed(positionP, angleP, *i));
		if (d < min)
			min = d;
		else if (d > max)
			max = d;
	}
}

void CalculateInterval(Vector2f & Axis, Vector2f & Point, float radius,
		float& min, float& max) {
	float d = Axis.dotProduct(Point);
	float r = radius * Axis.length();
	min = d - r;
	max = d + r;
}
}	//Ends namespace
