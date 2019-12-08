#include "../headers/Source.hpp"
#include <iostream>
//конструктов
Source::Source(Superviser * superviser, Buffer * buffer, int n_sources, float a, float b) : 
	superviser_(superviser), buffer_(buffer), n_sources_(n_sources), 
	a_(a), b_(b)
	{
		array_ = new Package[n_sources];
	}

//отработать цикл
void Source::_work()
{
	float time = superviser_->_getCurrentTime();

	if (this->superviser_->_over()) return;

	for (int i = 0; i < n_sources_; i++) 
	{
		if (!array_[i]._isActive()) 
		{
			continue;
		}
		if (array_[i]._getArrivedBuffer() == time) 
		{
			//добавили в счетчик и отправили
			std::cout << "source time is " << time << " package " << array_[i]._getNofSource() << " sent." << std::endl;
			this->superviser_ -> _addGenerated();
			this->buffer_ -> _recievePackage(array_[i]);

			//обнулили
			array_[i]._reboot();
		}
	}

	for (int i = 0; i < n_sources_; i++) 
	{
		if (!array_[i]._isActive()) 
		{	
			//активировали
			array_[i]._activate(i+1, time + this->_fx());

			//	добавили время
			std::cout << "for source "<< array_[i]._getNofSource() << " ";
			this->superviser_->_addEvent(array_[i]._getArrivedBuffer());
		}
	}
}

//fx
float Source::_fx()
{
	return a_+(b_-a_)*(rand()%100)/100;;
}

//состояние
int Source::_free()
{
	
	int count = 0;

	for (int i = 0; i < n_sources_; ++i) 
	{
		if (!array_[i]._isActive()) 
		{
			count++;
		}
	};
	
	return count;

};
