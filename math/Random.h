/*
 * Random.h
 *
 *  Created on: Apr 20, 2016
 *      Author: mathi
 */

#ifndef SRC_MATH_RANDOM_H_
#define SRC_MATH_RANDOM_H_

class Random {
protected:

public:
	Random();
	virtual ~Random();

	float randomF(int x);
};

extern Random ran;


#endif /* SRC_MATH_RANDOM_H_ */
