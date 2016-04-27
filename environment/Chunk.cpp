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
#include "Mathmatics.h"

Chunk::Chunk(int _index) :
		index(_index) {
	rewrite(index);
}

Chunk::~Chunk() {
	// TODO Auto-generated destructor stub
}

void Chunk::render() {

	//renders the main color of the chunk
	GD.Begin(EDGE_STRIP_B);
	GD.ColorRGB(BROWN);
	for (int var = 0; var < VERTEX_NUMBER; var++) {
		cam.Vertex2f((float) var * VERTEX_SEPERATION + index * CHUNK_SIZE,
				(heightMap[var]));
	}

	//renders the line between ground and air
	GD.Begin(LINE_STRIP);
	GD.ColorRGB(GREEN);
	for (int var = 0; var < VERTEX_NUMBER; var++) {
		cam.Vertex2f(((float) var * VERTEX_SEPERATION + index * CHUNK_SIZE),
				(heightMap[var]));
	}

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

	int i = (int) ((x * (VERTEX_NUMBER-1)) / CHUNK_SIZE);
	float y1 = heightMap[i];
	float y2 = heightMap[i + 1];
	float x1 = i * VERTEX_SEPERATION;
	float v = (x - x1) / VERTEX_SEPERATION;

	return (y1*(1-v)) + (y2*v);

}

