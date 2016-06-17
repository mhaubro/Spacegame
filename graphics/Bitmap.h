//Author: MH

#ifndef SRC_GRAPHICS_BITMAP_H_
#define SRC_GRAPHICS_BITMAP_H_

class Bitmap {
protected:
	const unsigned char location;
	const unsigned short width, height;
	unsigned char cells;

public:
	Bitmap(unsigned char location, unsigned short width, unsigned short height);
	virtual ~Bitmap();

};

#endif /* SRC_GRAPHICS_BITMAP_H_ */
