#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <math.h>
#include <cmath>
#include "Buffer.hpp"
#include "Superviser.hpp"

class Device 
{
private:
	int 			n_devices_;
	float 			l_;
	int 			current_;

	Package 	* 	array_;
	Buffer 		* 	buffer_;
	Superviser 	* 	superviser_;
	
public:
	//констрктор 
	Device(Superviser * superviser, Buffer * buffer, int n_devices, float l);

	//управление через current_
	void 	_find();
	void 	_inc();
	void 	_dec();

	//отработать цикл
	void 	_work();
	
	//fx	
	float 	_fx();

	//состояние
	int 	_capacity();
	bool 	_done();
};



#endif
