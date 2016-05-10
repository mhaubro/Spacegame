/*
 * Chunk.cpp
 *
 *  Created on: Apr 18, 2016
 *      Author: mathi
 */

#include "Chunk.h"
#include "GD2.h"
#include "Graphics.h"
#include "Random.h"
#include "PerlinNoise.h"
#include "Mathematics.h"

Chunk::Chunk(int _index) :
		index(_index) {
	rewrite(index);
}

Chunk::~Chunk() {
	// TODO Auto-generated destructor stub
}

void Chunk::render() {

	//GD.BitmapHandle(0);
	//GD.BitmapSize(NEAREST, REPEAT, REPEAT, 480, 272);

	//GD.ColorMask(0, 0, 0, 1);

	//GD.BlendFunc(ONE, ONE);
	//renders the main color of the chunk
	GD.Begin(EDGE_STRIP_B);
	GD.ColorRGB(0xD4772A);
	for (int var = 0; var < VERTEX_NUMBER; var++) {
		cam.Vertex2f((float) var * VERTEX_SEPERATION + index * CHUNK_SIZE,
				(heightMap[var]));
	}
	//GD.ColorMask(1, 1, 1, 0);
	//GD.BlendFunc(DST_ALPHA, ONE_MINUS_DST_ALPHA);
	//GD.Begin(BITMAPS);
	//GD.Vertex2ii(0, 0, 0);

	//renders the line between ground and air
	GD.Begin(LINE_STRIP);
	GD.ColorRGB(0xDE9357);
	for (int var = 0; var < VERTEX_NUMBER; var++) {
		cam.Vertex2f(((float) var * VERTEX_SEPERATION + index * CHUNK_SIZE),
				(heightMap[var]));
	}
	GD.ColorRGB(0x000000);
	//GD.ColorMask(1, 1, 1, 1);
	//GD.BitmapHandle(6);
	//GD.BitmapSize(NEAREST, REPEAT, REPEAT, 480, 272);
	GD.RestoreContext();
	// TODO render details in chunks
}

void Chunk::rewrite(int _index) {
	index = _index;

	static PerlinNoise pn = PerlinNoise();
	for (int var = 0; var < VERTEX_NUMBER; ++var) {
		heightMap[var] = pn.noise(var * VERTEX_SEPERATION + index * CHUNK_SIZE);
	}
}



float Chunk::getHeight(float x) {

	int i = (int) ((x * (VERTEX_NUMBER - 1)) / CHUNK_SIZE);
	float y1 = heightMap[i];
	float y2 = heightMap[i + 1];
	float x1 = i * VERTEX_SEPERATION;
	float v = (x - x1) / VERTEX_SEPERATION;

	return (y1 * (1 - v)) + (y2 * v);

}

Vector2f& Chunk::getNormal(float x, Vector2f &vec) {
	int i = (int) ((x * (VERTEX_NUMBER - 1)) / CHUNK_SIZE);
	float dy = heightMap[i + 1] - heightMap[i];

	float angle = atan2f(VERTEX_SEPERATION,dy) + PI;
	vec = FromAngle(1,angle);

	return vec;
}

