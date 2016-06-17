//Author: MH

#include "Bitmap.h"

Bitmap::Bitmap(unsigned char location, unsigned short width,
		unsigned short height) :
		location(location), width(width), height(height), cells(0) {

}

Bitmap::~Bitmap() {
	// TODO Auto-generated destructor stub
}

