//Author: MG

#ifndef SRC_MATH_RANDOM_H_
#define SRC_MATH_RANDOM_H_

class Random {
protected:

public:
	Random();
	virtual ~Random();

	float Float(int x);
};

extern Random ran;


#endif /* SRC_MATH_RANDOM_H_ */
