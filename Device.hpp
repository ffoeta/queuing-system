#ifndef DEVICE_HPP

#include "Father.hpp"
#include "Superviser.hpp"
#include <iostream>
#include <math.h>
#include <cmath>

class Device : public Father {
private:
	int 	N_;
	int 	time_;
	int 	current_;
	int * 	array_;
	int * 	wait_;
	bool 	doPrint_;

	Father * 		buffer;
	Superviser * 	superviser;
	
public:
	Device(Superviser * superviser, int N);
	~Device();

	void 	init(Father * obj) 	override;
	void 	send(int i) 		override;
	void 	get(int i) 			override;
	int 	ask() 				override;

	void 	inc();
	void 	dec();
	void 	find();

	void 	work();
	void 	collect();
	void 	finish();
	void 	free(int i);
	
	int 	fx();

	int 	capacity();
	bool 	done();
	

	

};


#define DEVICE_HPP
#endif