#include "../headers/Superviser.hpp"
#include <iostream>
#include <numeric>

//конструктор
Superviser::Superviser(int n_sources, int n_buffers, int n_devices, int n_requests) :
	n_requests_(n_requests), n_sources_(n_sources), n_buffers_(n_buffers), 
	n_devices_(n_devices), current_(0), total_packages_(0), time_(0)
{
	generated_request_per_source_   = new int[n_sources]; 
    dropped_request_per_source_     = new int[n_sources];

    waited_on_buffer_per_source_    =  new std::vector<float>[n_sources]; 
    spend_on_device_                =  new std::vector<float>[n_sources];
    spend_in_system_                =  new std::vector<float>[n_sources];
}

//текущее время в системе
float Superviser::_getCurrentTime() 
{
	return this -> current_;
}

//добавить событие
void Superviser::_addEvent(float time) 
{
	std::cout << time << " added." << std::endl;
	this->time_.push_back(time);
}


//обновить кол-во заявок
void Superviser::_addGenerated() 
{
	this -> total_packages_++;
}

//состояние
void Superviser::_next() 
{
	this->time_.sort();
	this->current_ = this->time_.front();
	this->time_.pop_front();

    std::cout << "time is " << current_ << " ";
	for (auto it = time_.begin(); it != time_.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << "." << std::endl;
};

bool Superviser::_over()
{
    std::cout << "xxxxxx "<<total_packages_ << std::endl;
	return (total_packages_ < n_requests_)?false:true;
};

//зарегистрировать пакеты
void Superviser::_addPackage(Package * package) 
{
    int   n                 =   package -> _getNofSource();
    float arrived_buffer    =   package -> _getArrivedBuffer();
    float arrived_device    =   package -> _getArrivedDevice();
    float done              =   package -> _getDone();

    this -> generated_request_per_source_[n]++;

    this -> waited_on_buffer_per_source_[n].push_back(arrived_device - arrived_buffer);
    this -> spend_on_device_[n].push_back(done - arrived_device);
    this -> spend_in_system_[n].push_back(done - arrived_buffer);
}

void Superviser::_droppPackage(Package * package) 
{
    int n = package -> _getNofSource();
    this -> dropped_request_per_source_[n]++;
}

//расчеты статистики

float Superviser::_getAverageFaillure(int i) 
{
    if (generated_request_per_source_[i] == 0) return 0;
    
    return dropped_request_per_source_[i] / generated_request_per_source_[i];
}

float Superviser::_getAverageWaitTime(int i)
{   
    if (waited_on_buffer_per_source_[i].empty()) return 0;

    float temp = std::accumulate(waited_on_buffer_per_source_[i].begin(), waited_on_buffer_per_source_[i].end(), 0);

    return  temp / waited_on_buffer_per_source_[i].size();
}

float Superviser::_getAverageSpendOnDevice(int i)
{
    if (spend_on_device_[i].empty()) return 0;

    auto temp = std::accumulate(spend_on_device_[i].begin(), spend_on_device_[i].end(), 0);
       
    return temp / spend_on_device_[i].size();
}

float Superviser::_getAverageSpendInSystem(int i)
{
    if (spend_in_system_[i].empty()) return 0;

    auto temp =  std::accumulate(spend_in_system_[i].begin(), spend_in_system_[i].end(), 0);

    return  temp / spend_in_system_[i].size();
}


//генерация статистики
State Superviser::_sample() 
{
    std::vector<float> average_probability_of_failure;
    std::vector<float> average_waited_on_buffer_per_source;
    std::vector<float> average_spend_on_device;
    std::vector<float> average_spend_in_system;

    //средние значения и шанс отказа
    for (int i = 0; i < n_sources_; i++)
    {        
        average_probability_of_failure.push_back(this -> _getAverageFaillure(i));
        average_waited_on_buffer_per_source.push_back(this -> _getAverageWaitTime(i));
        average_spend_on_device.push_back(this -> _getAverageSpendOnDevice(i));
        average_spend_in_system.push_back(this -> _getAverageSpendInSystem(i));
    }

    return State(average_probability_of_failure, average_waited_on_buffer_per_source,
        average_spend_on_device, average_spend_in_system);
}
