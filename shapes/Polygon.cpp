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

void Polygon::render(Vector2f position, float angle) {
	GD.ColorRGB(GREEN);
	GD.Begin(LINE_STRIP);

	for (std::vector<Vector2f>::iterator i = vertex.begin(); i != vertex.end(); i++){
		Vector2f v = FromAngle(i->length(), i->angle() + angle);


		cam.Vertex2f(v + position);
	}
	Vector2f v = FromAngle(vertex.begin()->length(), vertex.begin()->angle() + angle);

	cam.Vertex2f(v+position);	GD.ColorRGB(0xffffff);
}


