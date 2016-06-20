//Author: MG

#ifndef SRC_MATH_RANDOM_H_
#define SRC_MATH_RANDOM_H_

class Random {
protected:
	unsigned char recVal;
	unsigned char index;
	char getRecVal();

public:
	Random();
	virtual ~Random();

	float Float(int x);
	float FloatOLD(int x);
	float FloatRec();

	void setSeed(int x);
};

extern Random ran;

#endif /* SRC_MATH_RANDOM_H_ */
