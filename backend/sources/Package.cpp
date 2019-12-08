#include "../headers/Package.hpp"
#include <iostream>

	Package::Package() :
		n_of_source(0), arrived_on_buffer(0), arrived_on_device(0), done(0), dropped(0), active(false)
	{};

	//управление

	bool 	Package::_isActive() 
	{
		return this -> active;
	}

	void 	Package::_activate(int n, float time) 
	{
		this -> _reboot();

		this -> _setNofSource(n);
		this -> _setArrivedBuffer(time);

		this -> active = true;
	}

	void 	Package::_reboot() 
	{
		this -> active = false;
		
		this -> n_of_source = 0;
		this -> arrived_on_buffer = 0;
		this -> arrived_on_device = 0;
		this -> dropped = 0;
		this -> done = 0;
	}

	//геттеры

	int 	Package::_getNofSource() 
	{
		return this -> n_of_source;
	}

	float 	Package::_getArrivedBuffer() 
	{
		return this -> arrived_on_buffer;
	}

	float 	Package::_getArrivedDevice() 
	{
		return this -> arrived_on_device;
	}

	float 	Package::_getDone() 
	{
		return this -> done;
	}

	float 	Package::_getDropped() 
	{
		return this -> dropped;
	}

	//сеттеры

	void 	Package::_setNofSource(int n) 
	{
		this -> n_of_source = n;
	}

	void 	Package::_setArrivedBuffer(float time)
	{
		this -> arrived_on_buffer = time;
	}

	void 	Package::_setArrivedDevice(float time) 
	{
		this -> arrived_on_device = time;
	}

	void 	Package::_setDone(float time) 
	{
		this -> done = time;
	}

	void 	Package::_setDropped(float time) 
	{
		this -> dropped = time;
	}