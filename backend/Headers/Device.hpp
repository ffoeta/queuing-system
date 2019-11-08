#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "../Interface/TimeStackInterface.hpp"
#include "Buffer.hpp"

class Device : public TimeStackInterface {
private:
	int 			N_;
	float 			time_;
	int 			current_;

	Package 	* 	array_;

	Run_Type 		debug_;
	Buffer 		* 	buffer_;
	Superviser 	* 	superviser_;
	
public:
	Device(Superviser * superviser, Buffer * buffer, int N);
	~Device();

	std::string stat();

	void 	notify(float time);

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
