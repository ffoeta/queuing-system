#include "../headers/Engine.hpp"
#include <numeric>


//коснтруктор деструктор
Engine::Engine() : 
	 n_sources_(3), n_buffers_(3), n_devices_(3), n_requests_(10000), a_(0), b_(1), l_(3)
{
    this -> superviser_ = new Superviser(3, 3, 3, 1000);
    this -> buffer_     = new Buffer(superviser_, 3);
    this -> source_     = new Source(superviser_, buffer_, 3, 0, 1);
	this -> device_     = new Device(superviser_, buffer_, 3, 3);
}


//ребут
void Engine::_reboot()
{
  	this -> _reboot(n_sources_, n_buffers_, n_devices_, n_requests_, a_, b_, l_);
};

void Engine::_reboot(int n_sources, int n_buffers, int n_devices, int n_requests, 
			float a, float b, float l){

        delete superviser_;
		delete buffer_;
		delete source_;
		delete device_;
			
		this -> n_sources_ = n_sources;
		this -> n_buffers_ = n_buffers;
		this -> n_devices_ = n_devices;
		this -> n_requests_ = n_requests;
		this -> a_ = a;
		this -> b_ = b;
		this -> l_ = l;

        this -> superviser_ = new Superviser(n_sources_, n_buffers_, n_devices_, n_requests_);
        this -> buffer_     = new Buffer(superviser_, n_buffers_);
        this -> source_     = new Source(superviser_, buffer_, n_sources_, a_, b_);
	    this -> device_     = new Device(superviser_, buffer_, n_devices_, l_);
}


//исполнение программы
void Engine::_auto()
{
	while (!superviser_ -> _over()) 
	{
		source_ 			-> 	_collect();
		source_ 			-> 	_produce();

		device_ 			-> 	_exec();
		device_ 			-> 	_request();

		source_ 			-> 	_picture();
		buffer_				->	_picture();
		device_ 			-> 	_picture();

		superviser_ 		-> 	_next();
	}
}

void Engine::_manual()
{
	if (!superviser_ -> _over())
	{
		source_ 			-> 	_collect();
		source_ 			-> 	_produce();

		device_ 			-> 	_exec();
		device_ 			-> 	_request();

		source_ 			-> 	_picture();
		buffer_				->	_picture();
		device_ 			-> 	_picture();

		superviser_ 		-> 	_next();
	}
}


State	Engine::_state()
{
	return	superviser_ -> _sample();
}

Picture	Engine::_picture()
{
	return	superviser_ -> _picture();
}

//состояние
int Engine::_getNSources()
{
    return this -> n_sources_;
}
int Engine::_getNBuffers()
{
    return this -> n_buffers_;
}
int Engine::_getNDevices()
{
    return this -> n_devices_;
}


