#include "../headers/Device.hpp"

//конструктор деструктор
Device::Device() :
	N_(0), current_(0), l_(0), superviser_(nullptr), buffer_(nullptr), array_(nullptr)
	{};

Device::~Device()
{
	if (array_ != nullptr)
	{
		delete array_;
	}
}

//сеттер
void Device::set(Superviser * superviser, Buffer * buffer, int N) 
{
	this -> superviser_ = superviser;
	this -> buffer_ = buffer;

	this -> N_ = N; 

	this -> l_ = 0;
	array_ = new Package[N_];
};

// управление через current_
void Device::find() 
{
	if (!array_[current_].isActive()) 
	{
		return;
	}

	int temp = current_;

	do{
		inc();
	} while ( (array_[current_].isActive()) && (current_ != temp) );
};

void Device::inc() 
{
	if (current_ + 1 == N_) 
	{
		current_ = 0;
	} else 
	{
		current_++;
	}
};

void Device::dec() 
{
	if (current_ - 1 < 0) 
	{
		current_ = N_-1;
	} else
	{
		current_--;
	}
}

//отработать цикл
void Device::work() 
{
	int time = this->superviser_->getCurrentTime();

	for (int i = 0; i < N_; ++i)
	{
		if (array_[i].getDone() == time) 
		{
			superviser_->addPackage(array_[i]);
			array_[i].reboot();
		};
	};

	int f = this->capacity();
	auto packages = buffer_->select(f);

	
	if (packages.empty()) 
	{
		// std::cout << "empty:" << std::endl;
		// std::cout << packages.size()<< std::endl;
		return;
	}

	for (std::list<Package>::iterator package = packages.begin(); package != packages.end(); ++package)
	{
		//находим место. оно гарантированное есть, мы взяли столько сколько смогли
		this->find();
		
		array_[current_] = *package;
		array_[current_].setArrivedDevice(time);
		array_[current_].setDone(time + this->fx());
		
		//добавляем время
		this->superviser_ -> addEvent(array_[current_].getDone());

		inc();
	}
};


//fx
float Device::fx()
{
	return (-1.0 / this->l_*log(rand()/(double)RAND_MAX));
};

void Device::setConstant(float l) 
{
	this->l_ = l;
}


//состояние
int Device::capacity()
{
	int count = 0;
	for (int i = 0; i < N_; i++)
	{
		if (!array_[i].isActive()) 
		{
			count++;
		}
	}
	return count;
};

bool Device::done() 
{
	return (this->capacity() == N_)?true:false;
};
