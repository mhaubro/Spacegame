/*
 * Random.cpp
 *
 *  Created on: Apr 20, 2016
 *      Author: mathi
 */

#include "Random.h"

Random ran;

Random::Random() {

}

Random::~Random() {
	// TODO Auto-generated destructor stub
}

float Random::Float(int x){
	static short v1[] = {5,2,8,2,1,9,6,3,9,1,3,8,4,2,8,5,9,3,5,4};
	static short v2[] = {12, 5, 0, 2, 7, 9};
	int y = (x >> 1) ^ (-(x & 1u) & 0xB400u);
	return ((float) 1) / v1[(y+(v2[v1[x]%6]))%20];
}

