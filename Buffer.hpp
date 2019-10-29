#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "Superviser.hpp"
#include <iostream>
#include <math.h>
#include <cmath>

class Buffer {
private:
	int 			N_;
	Package  *	array_;
	int 		current_;
	bool 		doPrint_;

	Superviser * 	superviser_;
public:
	Buffer(Superviser * superviser, int N);
	~Buffer();

	void 				get(Package package);
	std::list<Package> 	select(int f);
	int 				search();

	void 				inc();
	void 				dec();
	void 				find();

	void				free(int i);

	int 				capacity();
	bool 				done();
};



#endif
