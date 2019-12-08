#include "../headers/Source.hpp"
#include <iostream>
//конструктов
Source::Source(Superviser * superviser, Buffer * buffer, int n_sources, float a, float b) : 
	superviser_(superviser), buffer_(buffer), n_sources_(n_sources), 
	a_(a), b_(b)
	{
		source_packages_ = new Package[n_sources];
	}

//отработать цикл

void Source::_produce() 
{
	float time = this -> superviser_ -> _getCurrentTime();

	for (int i = 0; i < n_sources_; i++)
	{
		if (!source_packages_[i]._isActive())
		{
			//активировали
			source_packages_[i]._activate(i+1, time + this->_fx());

			//	добавили время в очередь
			this->superviser_->_addEvent(source_packages_[i]._getArrivedBuffer());
		}
	}
}

void Source::_collect()
{
	float time = this -> superviser_ -> _getCurrentTime();

	for (int i = 0; i < n_sources_; i++) 
	{
		if (source_packages_[i]._isActive())
		{
			if (source_packages_[i]._getArrivedBuffer() == time) 
			{
				//добавили в счетчик и отправили
				this->superviser_ -> _addGenerated();
				this->buffer_ -> _recievePackage(source_packages_[i]);

				//обнулили
				source_packages_[i]._reboot();
			}

		} 
	}
}


//fx
float Source::_fx()
{
	return a_+(b_-a_)*(rand()%100)/100;;
}

//состояние
void Source::_picture()
{
	this -> superviser_ -> _addSourcePicture(this -> source_packages_);
};
