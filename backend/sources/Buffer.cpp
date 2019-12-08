#include "../headers/Buffer.hpp"

//конструктор деструктор
Buffer::Buffer(Superviser * superviser, int n_buffers) : 
 	superviser_(superviser), n_buffers_(n_buffers), current_(0)
	{
		this -> buffer_packages_ = new Package[n_buffers];
	}

//принять посылку
void Buffer::_recievePackage(Package package) 
{
	this->_findPlaceToInsertPackage();

	if (buffer_packages_[current_]._isActive()) 
	{
		this -> superviser_ -> _droppPackage(&buffer_packages_[current_]);
	}
		
	buffer_packages_[current_] = package;

	_inc();
};


//выбираем по заказу устройства f посылок из буфера
std::list<Package> Buffer::_sendPackages(int f)
{
	int ready_to_give = this -> n_buffers_ - this -> _free();
	int asked_for = f;

	std::list<Package> result;

	if (ready_to_give == 0)
	{
		return result;
	}

	int let_take;

	if (asked_for > ready_to_give)
	{
		let_take = ready_to_give;
	} else if (asked_for <= ready_to_give)
	{
		let_take = asked_for;
	};

	for (int i = 0; i < let_take; i++) 
	{
		int k = this -> _chooseHighestPackagePrior();
		while (!buffer_packages_[current_]._isActive() && (buffer_packages_[current_]._getNofSource() != k))
		{
			_inc();
		}
		result.push_back(buffer_packages_[current_]);
	};
	return result;
};


//поиск и управление через current_
void Buffer::_findPlaceToInsertPackage() 
{
	if (!buffer_packages_[current_]._isActive()) 
	{
		return;
	}
	int origin = current_;
	do{
		_inc();
	} while  ((current_ != origin) && (buffer_packages_[current_]._isActive()));
};

int Buffer::_chooseHighestPackagePrior() 
{
	std::vector<float> temp;

	for (int i = 0; i < n_buffers_; ++i)
	{
		if (buffer_packages_[i]._isActive())
		{
			temp.push_back(buffer_packages_[i]._getNofSource());
		}
	}

	if (temp.size() == 0)
	{
		return -1;
	}

	int index = 0;
	int min = temp.at(0);
	for (int i = 0; i < temp.size(); i++)
	{
		if (temp[i] < min)
		{
			min = temp[i];
			index = i;
		}
	}

	return min;
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
void Buffer::_picture()
{
	this -> superviser_ -> _addBufferPicture(this -> buffer_packages_);
}

int Buffer::_free()
{
	int count = 0;

	for (int i = 0; i < n_buffers_; ++i)
	{
		if (!buffer_packages_[i]._isActive()) 
		{
			count++;
		};
	}
	
	return count;
};

bool Buffer::_done() 
{
	return (this->_free() == n_buffers_)?true:false;
};
