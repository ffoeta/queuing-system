#include "../headers/Device.hpp"

//конструктор деструктор
Device::Device(Superviser * superviser, Buffer * buffer, int n_devices, float l) :
	superviser_(superviser), buffer_(buffer), n_devices_(n_devices), l_(l), array_(new Package[n_devices_]), current_(0)
	{};


// управление через current_
void Device::_find() 
{
	if (!array_[current_]._isActive()) 
	{
		return;
	}

	int temp = current_;

	do{
		_inc();
	} while ( (array_[current_]._isActive()) && (current_ != temp) );
};

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

//отработать цикл
void Device::_work() 
{
	if (this->superviser_->_over()) return;

	int time = this->superviser_->_getCurrentTime();

	for (int i = 0; i < n_devices_; ++i)
	{
		if (array_[i]._getDone() == time) 
		{
			superviser_->_addPackage(&array_[i]);
			array_[i]._reboot();
		};
	};

	int f = this->_capacity();
	auto packages = buffer_ -> _sendPackages(f);

	
	if (packages.empty()) 
	{
		// std::cout << "empty:" << std::endl;
		// std::cout << packages.size()<< std::endl;
		return;
	}

	for (std::list<Package>::iterator package = packages.begin(); package != packages.end(); package++)
	{
		//находим место. оно гарантированное есть, мы взяли столько сколько смогли
		this->_find();
		
		array_[current_] = *package;
		array_[current_]._setArrivedDevice(time);
		array_[current_]._setDone(time + this->_fx());
		
		//добавляем время
		this->superviser_ -> _addEvent(array_[current_]._getDone());

		_inc();
	}
};


//fx
float Device::_fx()
{
	return (-1.0 / this->l_*log(rand()/(double)RAND_MAX));
};

//состояние
int Device::_capacity()
{
	int count = 0;
	for (int i = 0; i < n_devices_; i++)
	{
		if (!array_[i]._isActive()) 
		{
			count++;
		}
	}
	return count;
};
