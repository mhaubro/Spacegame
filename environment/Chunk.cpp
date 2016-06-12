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

Chunk::Chunk(int _index) {
	rewrite(_index);
}

Chunk::~Chunk() {
	// TODO Auto-generated destructor stub
}

void Chunk::render() {

	GD.RestoreContext();

	//renders the main color of the chunk
	GD.Begin(EDGE_STRIP_B);
	GD.ColorRGB(0xD4772A);
	for (int var = 0; var < VERTEX_NUMBER; var++) {
		cam.Vertex2f((float) var * VERTEX_SEPERATION + index * CHUNK_SIZE,
				(heightMap[var]));
	}

	//renders the line between ground and air
	GD.Begin(LINE_STRIP);
	GD.ColorRGB(0xDE9357);
	for (int var = 0; var < VERTEX_NUMBER; var++) {
		cam.Vertex2f(((float) var * VERTEX_SEPERATION + index * CHUNK_SIZE),
				(heightMap[var]));
	}

#if DEBUG
	GD.Begin(POINTS);
	GD.ColorRGB(BLUE);
	cam.Vertex2f(index * CHUNK_SIZE, heightMap[0]);
#endif

	// TODO render details in chunks
//	GD.ColorRGB(WHITE);
//	GD.Begin(BITMAPS);
//	for (int i = 0; i < NUM_DETAILS; i++) {
//		GD.BitmapHandle(details[i].handle);
//		GD.Cell(details[i].cell);
//		GD.BitmapSize(BILINEAR, BORDER, BORDER, 32, 32);
//		GD.cmd_loadidentity();
//		GD.cmd_scale(F16(2), F16(2));
//		GD.cmd_setmatrix();
//		cam.Vertex2f(details[i].x, details[i].y);
//	}

}

void Chunk::update(float x) {
	float d = index * CHUNK_SIZE - x;

	while (d < -(WORLD_SIZE * CHUNK_SIZE) / 2) {
		d += (WORLD_SIZE * CHUNK_SIZE);
	}

	while (d > (WORLD_SIZE * CHUNK_SIZE) / 2) {
		d -= (WORLD_SIZE * CHUNK_SIZE);
	}

	if (d < -(CHUNKS_FROM_CENTER + 1) * CHUNK_SIZE) {
		rewrite(index + NUMBER_OF_CHUNKS_LOADED);
	}
	if (d > (CHUNKS_FROM_CENTER) * CHUNK_SIZE) {
		rewrite(index - NUMBER_OF_CHUNKS_LOADED);
	}
}

void Chunk::rewrite(int _index) {

	index = _index;
	while (index < 0) {
		index += WORLD_SIZE;
	}
	while (index >= WORLD_SIZE) {
		index -= WORLD_SIZE;
	}

	static PerlinNoise pn = PerlinNoise();
	for (int var = 0; var < VERTEX_NUMBER; ++var) {
		heightMap[var] = pn.noise(var * VERTEX_SEPERATION + index * CHUNK_SIZE);
	}

//	for (int i = 0; i < NUM_DETAILS; i++) {
//		details[i].handle = SPRITESHEET_HANDLE;
//		details[i].cell = 0;
//		float rx = ran.Float(index + i * 42);
//		float ry = ran.Float(index + 2*i * 13);
//		details[i].x = (rx + index) * CHUNK_SIZE;
//		details[i].y = ry * getHeight(rx * CHUNK_SIZE) + .25;
//	}
}

float Chunk::getHeight(float x) {

	int i = (int) ((x * (VERTEX_NUMBER - 1)) / CHUNK_SIZE);
	if (i >= 0 && i < VERTEX_NUMBER) {
		float y1 = heightMap[i];
		float y2 = heightMap[i + 1];
		float x1 = i * VERTEX_SEPERATION;
		float v = (x - x1) / VERTEX_SEPERATION;

		return (y1 * (1 - v)) + (y2 * v);
	}
	return 0;

}

Vector2f& Chunk::getNormal(float x, Vector2f &vec) {
	int i = (int) ((x * (VERTEX_NUMBER - 1)) / CHUNK_SIZE);
	if (i >= 0 && i < VERTEX_NUMBER) {
		float dy = heightMap[i + 1] - heightMap[i];

		float angle = atan2f(VERTEX_SEPERATION, dy) + PI;
		vec = FromAngle(1, angle);

		return vec;
	}
	return vec = Vector2f(0, -1);
}

int Chunk::getIndex() {
	return index;
}

