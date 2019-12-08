#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <math.h>
#include <cmath>
#include "Buffer.hpp"
#include "Superviser.hpp"

class Device 
{
public:
	//констрктор 
	Device(Superviser * superviser, Buffer * buffer, int n_devices, float l);

	//управление через current_
	void 	_findPlaceForNewPackage();
	void 	_inc();
	void 	_dec();

	//отработать цикл
	void 	_request();
	void 	_exec();
	
	//fx	
	float 	_fx();

	//состояние
	void	_picture();
	int 	_free();
	

private:
	int 			n_devices_;
	float 			l_;
	int 			current_;

	Package 	* 	device_packages_;
	Buffer 		* 	buffer_;
	Superviser 	* 	superviser_;
};



#endif
