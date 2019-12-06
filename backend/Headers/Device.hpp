#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <math.h>
#include <cmath>
#include "Buffer.hpp"
#include "Superviser.hpp"

class Device 
{
private:
	int 			N_;

	int 			current_;
	float 			l_;

	Package 	* 	array_;

	Buffer 		* 	buffer_;
	Superviser 	* 	superviser_;
	
public:
	//констрктор деструктор
	Device();
	~Device();

	//сеттер
	void 	set(Superviser * superviser, Buffer * buffer, int N);

	//управление через current_
	void 	find();
	void 	inc();
	void 	dec();

	//отработать цикл
	void 	work();
	
	//fx	
	float 	fx();
	void 	setConstant(float l);

	//состояние
	int 	capacity();
	bool 	done();
};



#endif
