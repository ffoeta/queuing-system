#ifndef RECORD_HPP
#define RECORD_HPP 

class Package {
public:

	Package();

	void 	_activate(int n, float time);
	bool 	_isActive();
	void 	_reboot();

	int 	_getNofSource();
	float 	_getArrivedBuffer();
	float 	_getArrivedDevice();
	float 	_getDone();
	float 	_getDropped();

	void 	_setArrivedDevice(float time);
	void 	_setDone(float time);
	void 	_setDropped(float time);

private:

	void 	_setNofSource(int n);
	void 	_setArrivedBuffer(float time);	

	int 			n_of_source;
	float			arrived_on_buffer;
	float 			arrived_on_device;
	float 			done;
	float 			dropped;

	bool 			active;	
};


#endif
