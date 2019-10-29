#ifndef RECORD_HPP
#define RECORD_HPP 

#include <iostream>

class Package {
private:
	int 			n_;
	float			source_initiated_;
	float 			source_created_;
	float			device_arrived_;
	float 			device_done_;
	float 			dropped_;
public:
	Package();

	
	void 	init(int n);

	bool 	null();
	void 	reboot();

	float 	getSourceInitiated();
	float 	getSourceCreated();
	float 	getDeviceArrived();
	float 	getDeviceDone();
	float 	getDropped();
	int 	getN();

	void 	setSourceInitiated(float time);
	void 	setSourceCreated(float time);
	void 	setDeviceArrived(float time);
	void 	setDeviceDone(float time);
	void 	setDropped(float time);
	void 	setN(int n);
};


#endif
