#ifndef INNERAPI_HPP
#define INNERAPI_HPP

#include "ResultPack.hpp"
#include "RunType.hpp"
#include "Source.hpp"
#include "Device.hpp"
#include "Buffer.hpp"

class InnerAPI
{
public:
	//конструктор деструктор
	InnerAPI();
	~InnerAPI();

	//ребут
	void 		reboot();

	//сеттеры
	void 		set(int n_sources, int n_buffers, 
					int n_devices, int n_requests, 
					float a, float b, float l);

	void 		setRunType(Run_Type run_type);
	
	//геттеры
	int 		getNSources();
	int 		getNBuffers();
	int 		getNDevices();


	
	//исполнение программы
	State  		run();
	State	   	next();

private:
    Superviser 	* 	superviser_;
	Buffer 		*	buffer_;
	Source 		*	source_;
	Device 		*	device_;

	Run_Type 		run_type_;

	int 			n_sources_;
	int 			n_devices_;
	int 			n_buffers_;
	int 			n_requests_;

	float 			a_;
	float 			b_;
	float 			l_;
};


#endif