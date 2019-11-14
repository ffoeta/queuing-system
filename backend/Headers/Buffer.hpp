#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "Superviser.hpp"
#include <iostream>
#include <math.h>
#include <cmath>
#include <string>

class Buffer {
private:
	int 			N_;
	Package  *	array_;
	int 		current_;
	Run_Type 	debug_;

	Superviser * 	superviser_;
public:
	void 				set(Superviser * superviser, int N);
	
	std::string 		stat();

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
