#ifndef SOURCE_HPP
#define SOURCE_HPP

#include "Father.hpp"
#include "Superviser.hpp"
#include <iostream>
#include <math.h>
#include <cmath>

class Source : public Father {
private:
	int 	N_;
	int 	time_;
	int * 	array_;
	bool 	doPrint_;

	Father * 		buffer;
	Superviser * 	superviser;
public:
	Source(Superviser * superviser, int N);
	~Source();

	void 	init(Father * obj) 	override;
	void 	send(int i) 		override;
	void 	get(int i) 			override;
	int  	ask() 				override;

	void 	generate();
	void 	collect();

	int  	fx();
	void 	set(int i);
	void 	free(int i);
	void 	work();
	
	int 	capacity();
	bool 	done();
};



#endif
