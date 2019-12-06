#ifndef RECORD_HPP
#define RECORD_HPP 

class Package {
public:

	Package();

	void 	activate(int n, float time);
	bool 	isActive();
	void 	reboot();

	int 	getNofSource();
	float 	getArrivedBuffer();
	float 	getArrivedDevice();
	float 	getDone();
	float 	getDropped();

	void 	setArrivedDevice(float time);
	void 	setDone(float time);
	void 	setDropped(float time);

private:

	void 	setNofSource(int n);
	void 	setArrivedBuffer(float time);	

	int 			n_of_source;
	float			arrived_on_buffer;
	float 			arrived_on_device;
	float 			done;
	float 			dropped;

	bool 			active;	
};


#endif
