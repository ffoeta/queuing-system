#ifndef SOURCE_HPP
#define SOURCE_HPP

#include "TimeStackInterface.hpp"
#include "Buffer.hpp"

#include <iostream>
#include <math.h>
#include <cmath>

class Source : public TimeStackInterface {
private:
	int 		N_;
	float 		time_;
	Package  *  array_;
	bool 		doPrint_;

	Buffer 		* 	buffer_;
	Superviser 	* 	superviser_;
public:
	Source(Superviser * superviser, Buffer * buffer, int N);
	~Source();


	void 	create(Package * package);
	void 	send(Package * package);

	void 	generate();
	void 	collect();

	float  	fx();

	void 	notify(float time);

	void 	free(Package * package);
	void 	work();
	
	int 	capacity();
	bool 	done();
};



#endif
