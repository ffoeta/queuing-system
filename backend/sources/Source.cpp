#include "../headers/Source.hpp"

//конструктов
Source::Source() : 
	N_(0), a_(0), b_(0), array_(nullptr), buffer_(nullptr), superviser_(nullptr)
	{}

Source::~Source()
{
	if (array_ != nullptr)
	{
		delete array_;
	}
}

//сеттер
void Source::set(Superviser * superviser, Buffer * buffer, int N) 
{
	superviser_ = superviser;

	buffer_ = buffer;
	N_ = N;

	array_ = new Package[N_];
}

//отработать цикл
void Source::work()
{
	float time = superviser_->getCurrentTime();

	for (int i = 0; i < N_; i++) 
	{
		if (!array_[i].isActive()) continue;

		if (array_[i].getArrivedBuffer() == time) 
		{
			//добавили в счетчик и отправили
			this->superviser_ -> addGenerated();
			this->buffer_ -> recievePackage(array_[i]);

			//обнулили
			array_[i].reboot();
		}
	}

	if (this->superviser_->over()) return;

	for (int i = 0; i < N_; i++) 
	{
		if (!array_[i].isActive()) 
		{	
			//активировали
			array_[i].activate(i+1, time + this->fx());

			//	добавили время
			this->superviser_->addEvent(time + this->fx());
		}
	}
}

//fx
float Source::fx()
{
	return a_+(b_-a_)*(rand()%100)/100;;
}

void Source::setConstants(float a, float b) 
{
	this->a_ = a;
	this->b_ = b;
}

//состояние
int Source::free()
{
	
	int count = 0;

	for (int i = 0; i < N_; ++i) 
	{
		if (!array_[i].isActive()) 
		{
			count++;
		}
	};
	
	return count;

};

bool Source::done() 
{
	return (this->free() == N_)?true:false;
};
