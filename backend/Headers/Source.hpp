#ifndef SOURCE_HPP
#define SOURCE_HPP

#include <math.h>
#include <cmath>
#include "Buffer.hpp"
#include "Superviser.hpp"

class Source {
private:
	int 		N_;
	Package  *  array_;

	float		a_;
	float		b_;

	Buffer 		* 	buffer_;
	Superviser 	* 	superviser_;
public:
	//конструктор деструктор
	Source();
	~Source();
	//сеттер
	void 	set(Superviser * superviser, Buffer * buffer, int N);

	//отработать цикл
	void 	work();
	//fx
	float  	fx();
	void 	setConstants(float a, float b);
	//состояние
	int 	free();
	bool 	done();
};



#endif
