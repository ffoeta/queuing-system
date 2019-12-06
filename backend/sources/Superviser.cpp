#include "../headers/Superviser.hpp"

//конструктор
Superviser::Superviser() :
	N_(0), sources_(0), buffers_(0), devices_(0), current_(0), source_created_(0),data_()
{
	time_.clear();
}

//сеттер
void Superviser::set(int N, int sources, int buffers, int devices) 
{
	this -> N_ = N; 

	this -> sources_ = sources; 
	this -> buffers_ = buffers;
	this -> devices_ = devices;

	this -> current_ = 0;
	this -> source_created_ = 0;

	this -> data_.set(sources_);
}

//текущее время в системе
float Superviser::getCurrentTime() 
{
	return this -> current_;
}

//добавить событие
void Superviser::addEvent(float time) 
{
	this->time_.push_back(time);
}


//обновить кол-во заявок
void Superviser::addGenerated() 
{
	this -> source_created_++;
}


//регистрирация выбывших пакетов
void Superviser::addPackage(Package p)
{
	this -> data_.addPackage(p);
}

void Superviser::droppPackage(Package p)
{
	this -> data_.droppPackage(p);
}

//состояние
void Superviser::next() 
{
	this->time_.sort();
	this->current_ = this->time_.front();
	this->time_.pop_front();
};

State Superviser::state()
{
	return this -> data_.sample();
}

bool Superviser::over()
{
	return (source_created_ < N_)?false:true;
};