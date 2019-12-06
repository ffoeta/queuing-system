#include "../headers/Buffer.hpp"

//конструктор деструктор
Buffer::Buffer() : 
	N_(0), array_(nullptr), current_(0), superviser_(nullptr) 
	{}

Buffer::~Buffer()
{
	if (array_ != nullptr)
	{
		delete array_;
	}
}

//сеттер
void Buffer::set(Superviser * superviser, int N) 
{
	this -> superviser_ = superviser;

	this -> N_ = N;

	this -> array_ = new Package[N_];
}

//принять посылку
void Buffer::recievePackage(Package package) 
{
	this->find();

	if (array_[current_].isActive()) 
	{
		//вернулись на последнюю позицию
		dec();

		//приготовили к отмене и выкинули
		// array_[current_] . setDropped(current_);
		// superviser_ -> droppPackage(array_[current_]);

		
		// std::cout <<"--------------------"<<std::endl;
		// std::cout <<"--------------------"<<std::endl;
		// std::cout << package.getNofSource() << std::endl;
		// std::cout << package.getArrivedBuffer() << std::endl;

		// //заменили
		// array_[current_] = package;

		// std::cout <<"--------------------"<<std::endl;
		// std::cout << array_[current_].getNofSource() << std::endl;
		// std::cout << array_[current_].getArrivedBuffer() << std::endl;
		// std::cout <<"--------------------"<<std::endl;
		// std::cout <<"--------------------"<<std::endl;
		
	} else 
	{
		array_[current_] = package;
	}

	inc();
};


//выбираем по заказу устройства f посылок из буфера
std::list<Package> Buffer::select(int f)
{
	std::list<Package> result(0);

	int r = 0;

	for (int i = 0; i < f; ++i) 
	{
		while(r != -1)
		{
			r = this->search();

			if (r != -1)
			{
				result.push_back(array_[r]);
				array_[r].reboot();
			};

		};
	};
	return result;
};


//поиск и управление через current_
void Buffer::find() 
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


int Buffer::search() 
{
	if (this->done()) 
	{
		return -1;
	}

	int value = RAND_MAX;
	int k = -1;
	int n = -1;

	for (int i = 0; i < N_; ++i)
	{
		if (array_[i].isActive()) 
		{
			n = array_[i].getNofSource();
			
			if (n < value) 
			{
				value = n;
				k = i;
			}
		}

	}

	return k;
};


void Buffer::inc() 
{
	if (current_ + 1 == N_) 
	{
		current_ = 0;
	} else 
	{
		current_++;
	}
};

void Buffer::dec() 
{
	if (current_ - 1 < 0) 
	{
		current_ = N_-1;
	} else 
	{
		current_--;
	}
}


//состояние
int Buffer::capacity()
{
	int count = 0;

	for (int i = 0; i < N_; ++i)
	{
		if (!array_[i].isActive()) 
		{
			count++;
		};
	}
	
	return count;
};

bool Buffer::done() 
{
	return (this->capacity() == N_)?true:false;
};
