#include "../headers/Device.hpp"
#include <iostream>

//конструктор 
Device::Device(Superviser * superviser, Buffer * buffer, int n_devices, float l) :
	superviser_(superviser), buffer_(buffer), n_devices_(n_devices), l_(l), current_(0)
	{
		device_packages_ = new Package[n_devices_];
	};


// управление через current_
void Device::_findPlaceForNewPackage()
{
	if (!device_packages_[current_]._isActive()) 
	{
		return;
	}
	int origin = this -> current_;
	do {
		_inc();
	} while((this->current_ != origin) && (device_packages_[this -> current_]._isActive()));
}

void Device::_inc() 
{
	if (current_ + 1 == n_devices_)
	{
		current_ = 0;
	} else 
	{
		current_++;
	}
};

void Device::_dec() 
{
	if (current_ - 1 < 0) 
	{
		current_ = n_devices_-1;
	} else
	{
		current_--;
	}
}


void Device::_request()
{
	int packages_requested = this->_free();

	if (packages_requested == 0) 
	{
		return;
	}

	auto buffer_response = this -> buffer_ ->_sendPackages(packages_requested);

	if (buffer_response.empty())
	{
		return;
	}

	int time = this -> superviser_ -> _getCurrentTime();

	for (int i = 0; i < buffer_response.size(); i++)
	{
		this -> _findPlaceForNewPackage();

		device_packages_[current_] = buffer_response.front();

		buffer_response.pop_front();

		device_packages_[current_]._setArrivedDevice(time);
		device_packages_[current_]._setDone(time + this -> _fx());

		this->superviser_ -> _addEvent(device_packages_[current_]._getDone());
	}
	this -> superviser_ -> _addDevicePicture(this -> device_packages_);
}

void Device::_exec()
{
	float time = this -> superviser_ -> _getCurrentTime();
	for (int i = 0; i <n_devices_; i++ )
	{
		if (device_packages_[i]._isActive()) 
		{
			if (device_packages_[i]._getDone() == time)
			{
				this -> superviser_ -> _addPackage(&device_packages_[i]);
				this -> device_packages_[i]._reboot();
				_inc();
			}
		}
	}
}


//fx
float Device::_fx()
{
	return (-1.0 / this->l_*log(rand()/(double)RAND_MAX));
};

//состояние
void Device::_picture()
{
	this -> superviser_ -> _addDevicePicture(this -> device_packages_);
}

int Device::_free()
{
	int count = 0;
	for (int i = 0; i < n_devices_; i++)
	{
		if (!device_packages_[i]._isActive()) 
		{
			count++;
		}
	}
	return count;
};
