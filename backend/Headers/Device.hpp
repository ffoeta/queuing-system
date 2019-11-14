#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "Buffer.hpp"

class Device {
private:
	int 			N_;
	float 			time_;
	int 			current_;

	float 			l_;

	Package 	* 	array_;

	Run_Type 		debug_;
	Buffer 		* 	buffer_;
	Superviser 	* 	superviser_;
	
public:

	void 	set(Superviser * superviser, Buffer * buffer, int N);
	
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
	void 	setConstant(float l);

	int 	capacity();
	bool 	done();
	

	

};



#endif
