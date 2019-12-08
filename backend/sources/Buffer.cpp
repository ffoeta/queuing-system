#include "../headers/Buffer.hpp"
#include <iostream>
//конструктор деструктор
Buffer::Buffer(Superviser * superviser, int n_buffers) : 
 	superviser_(superviser), n_buffers_(n_buffers), current_(0)
	{
		array_ = new Package[n_buffers];
	}

//принять посылку
void Buffer::_recievePackage(Package package) 
{
	this->_find();

	if (array_[current_]._isActive()) 
	{
		this -> superviser_ -> _droppPackage(&array_[current_]);
		_dec();
	}
		
	array_[current_] = package;

	_inc();
};


//выбираем по заказу устройства f посылок из буфера
std::list<Package> Buffer::_sendPackages(int f)
{
	std::list<Package> result(0);

	int r = 0;

	for (int i = 0; i < f; ++i) 
	{
		while(r != -1)
		{
			r = this->_choose();

			if (r != -1)
			{
				result.push_back(array_[r]);
				array_[r]._reboot();
			};

		};
	};
	return result;
};


//поиск и управление через current_
void Buffer::_find() 
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


int Buffer::_choose() 
{
	if (this->_done()) 
	{
		return -1;
	}

	int value = RAND_MAX;
	int k = -1;
	int n = -1;

	for (int i = 0; i < n_buffers_; ++i)
	{
		if (array_[i]._isActive()) 
		{
			n = array_[i]._getNofSource();
			
			if (n < value) 
			{
				value = n;
				k = i;
			}
		}

	}

	return k;
};


void Buffer::_inc() 
{
	if (current_ + 1 == n_buffers_) 
	{
		current_ = 0;
	} else 
	{
		current_++;
	}
};

void Buffer::_dec() 
{
	if (current_ - 1 < 0) 
	{
		current_ = n_buffers_-1;
	} else 
	{
		current_--;
	}
}


//состояние
int Buffer::_capacity()
{
	int count = 0;

	for (int i = 0; i < n_buffers_; ++i)
	{
		if (!array_[i]._isActive()) 
		{
			count++;
		};
	}
	
	return count;
};

bool Buffer::_done() 
{
	return (this->_capacity() == n_buffers_)?true:false;
};
