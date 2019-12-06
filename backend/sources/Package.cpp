#include "../headers/Package.hpp"


	Package::Package() :
		n_of_source(0), arrived_on_buffer(0), arrived_on_device(0), done(0), dropped(0), active(false)
	{};

	//управление

	bool 	Package::isActive() 
	{
		return this -> active;
	}

	void 	Package::activate(int n, float time) 
	{
		this -> reboot();

		this -> setNofSource(n);
		this -> setArrivedBuffer(time);

		this -> active = true;
	}

	void 	Package::reboot() 
	{
		this -> active = false;
		
		this -> n_of_source = 0;
		this -> arrived_on_buffer = 0;
		this -> arrived_on_device = 0;
		this -> dropped = 0;
		this -> done = 0;
	}

	//геттеры

	int 	Package::getNofSource() 
	{
		return this -> n_of_source;
	}

	float 	Package::getArrivedBuffer() 
	{
		return this -> arrived_on_buffer;
	}

	float 	Package::getArrivedDevice() 
	{
		return this -> arrived_on_device;
	}

	float 	Package::getDone() 
	{
		return this -> done;
	}

	float 	Package::getDropped() 
	{
		return this -> dropped;
	}

	//сеттеры

	void 	Package::setNofSource(int n) 
	{
		this -> n_of_source = n;
	}

	void 	Package::setArrivedBuffer(float time)
	{
		this -> arrived_on_buffer = time;
	}

	void 	Package::setArrivedDevice(float time) 
	{
		this -> arrived_on_device = time;
	}

	void 	Package::setDone(float time) 
	{
		this -> done = time;
	}

	void 	Package::setDropped(float time) 
	{
		this -> dropped = time;
	}