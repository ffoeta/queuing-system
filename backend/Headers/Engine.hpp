#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "State.hpp"
#include "Package.hpp"
#include "Source.hpp"
#include "Device.hpp"
#include "Buffer.hpp"

class Engine
{
public:
	//конструктор деструктор
	Engine();
	//сеттеры
	void 		_reboot();
	void 		_reboot(int n_requests, int n_sources, int n_buffers, int n_devices, float a, float b, float l);
	//исполнение программы
	void  		_auto();
	void	   	_manual();

	State		_state();
	Picture		_picture();
	//состояния
	int 		_getNSources();
	int 		_getNBuffers();
	int 		_getNDevices();	
	//расчеты статистики


private:
    Superviser 	* 	superviser_;
	Buffer 		*	buffer_;
	Source 		*	source_;
	Device 		*	device_;

	int 			n_sources_;
	int 			n_devices_;
	int 			n_buffers_;
	int 			n_requests_;
	float 			a_;
	float 			b_;
	float 			l_;
};


#endif