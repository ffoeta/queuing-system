#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "Superviser.hpp"
#include "Buffer.hpp"
#include <iostream>
#include <math.h>
#include <cmath>

class Device {
private:
	int 			N_;
	float 			time_;
	int 			current_;

	Package 	* 	array_;

	bool 			doPrint_;
	Buffer 		* 	buffer_;
	Superviser 	* 	superviser_;
	
public:
	Device(Superviser * superviser, Buffer * buffer, int N);
	~Device();

	void 	inc();
	void 	dec();
	void 	find();
	void 	place(std::list<Package> packages);

	void 	work();
	void 	collect();
	void 	finish();
	void 	free(Package * package);
	
	float 	fx();

	int 	capacity();
	bool 	done();
	

	

};



#endif
