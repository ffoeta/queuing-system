#ifndef SOURCE_HPP
#define SOURCE_HPP

#include <math.h>
#include <cmath>
#include "Buffer.hpp"
#include "Superviser.hpp"

class Source {
public:
	//конструктор 
	Source(Superviser * superviser, Buffer * buffer, int n_sources, float a, float b);

	//отработать цикл
	void 	_work();
	//fx
	float  	_fx();
	//состояние
	int 	_free();
	bool 	_done();
	
private:
	int 		n_sources_;
	Package  *  array_;

	float		a_;
	float		b_;

	Buffer 		* 	buffer_;
	Superviser 	* 	superviser_;
};



#endif
