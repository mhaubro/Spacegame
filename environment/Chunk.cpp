/*
 * Chunk.cpp
 *
 *  Created on: Apr 18, 2016
 *      Author: mathi
 */

#include "Chunk.h"
#include "GD2.h"
#include "Graphics.h"

Chunk::Chunk(short _index)
: index(_index)
{
	heightMap[0] = 1;
	heightMap[1] = 2;
	heightMap[2] = 1;
	heightMap[3] = 2;
	heightMap[4] = 1;
	heightMap[5] = 2;
	heightMap[6] = 1;
	heightMap[7] = 3;
	heightMap[8] = 1;
	heightMap[9] = 2;
	heightMap[10] = 1;
	heightMap[11] = 2;
	heightMap[12] = 1;
	heightMap[13] = 2;
	heightMap[14] = 1;
	heightMap[15] = 3;
	heightMap[16] = 1;
	heightMap[17] = 2;
	heightMap[18] = 1;
	heightMap[19] = 2;
	heightMap[20] = 1;
	heightMap[21] = 2;
	heightMap[22] = 1;
	heightMap[23] = 3;
	heightMap[24] = 1;
	heightMap[25] = 2;
	heightMap[26] = 1;
	heightMap[27] = 2;
	heightMap[28] = 1;
	heightMap[29] = 2;
	heightMap[30] = 1;
	heightMap[31] = 3;
	heightMap[32] = 1;
	heightMap[33] = 2;
	heightMap[34] = 1;
	heightMap[35] = 2;
	heightMap[36] = 1;
	heightMap[37] = 2;
	heightMap[38] = 1;
	heightMap[39] = 3;
	heightMap[40] = 1;
	heightMap[41] = 2;
	heightMap[42] = 1;
	heightMap[43] = 2;
	heightMap[44] = 1;
	heightMap[45] = 2;
	heightMap[46] = 1;
	heightMap[47] = 3;
	heightMap[48] = 1;
	heightMap[49] = 2;
	heightMap[50] = 1;
	heightMap[51] = 2;
	heightMap[52] = 1;
	heightMap[53] = 2;
	heightMap[54] = 1;
	heightMap[55] = 3;
	heightMap[56] = 1;
	heightMap[57] = 2;
	heightMap[58] = 1;
	heightMap[59] = 2;
	heightMap[60] = 1;
	heightMap[61] = 2;
	heightMap[62] = 1;
	heightMap[63] = 3;

}

Chunk::~Chunk() {
	// TODO Auto-generated destructor stub
}

void Chunk::render() {

	//renders the main color of the chunk
	GD.Begin(EDGE_STRIP_B);
	GD.ColorRGB(GREY);
	for (int var = 0; var < CHUNK_SIZE; var++) {
		//GD.Vertex2f(16 * 100 + 64 * var, 16 * 100 - 64 * heightMap[var]);
		cam.Vertex2f((float)var/4, (heightMap[var]));
	}

	//renders the line between ground and air
	GD.Begin(LINE_STRIP);
	GD.ColorRGB(GREEN);
	for (int var = 0; var < CHUNK_SIZE; var++) {
		cam.Vertex2f((float)var/4, (heightMap[var]));
	}

	// TODO render details in chunks
}

