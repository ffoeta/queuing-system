#include "../headers/Superviser.hpp"
#include <iostream>
#include <numeric>
#include <algorithm>

//конструктор
Superviser::Superviser(int n_sources, int n_buffers, int n_devices, int n_requests) :
	n_requests_(n_requests), n_sources_(n_sources), n_buffers_(n_buffers), 
	n_devices_(n_devices), current_(0), total_packages_(0), time_(0)
{
	generated_request_per_source_   =   new int[n_sources]; 
    dropped_request_per_source_     =   new int[n_sources];

    waited_on_buffer_per_source_    =   new std::vector<float>[n_sources]; 
    spend_on_device_                =   new std::vector<float>[n_sources];
    spend_in_system_                =   new std::vector<float>[n_sources];

    source_picture_    				=   new std::vector<int>[n_sources];
	buffer_picture_				    =   new std::vector<int>[n_buffers];
	device_picture_				    =   new std::vector<int>[n_devices];

    for (int i = 0; i < n_sources; i ++)
    {
        generated_request_per_source_[i] = 0;
        dropped_request_per_source_[i] = 0;

        waited_on_buffer_per_source_[i].clear();
        spend_on_device_[i].clear();
        spend_in_system_[i].clear();
    }

    test = 0;
    test_c = 0;
}

//текущее время в системе
float Superviser::_getCurrentTime() 
{
	return this -> current_;
}

//добавить событие
void Superviser::_addEvent(float time) 
{
	this->time_.push_back(time);
}


//обновить кол-во заявок
void Superviser::_addGenerated() 
{
	this -> total_packages_++;
}

void Superviser::__ADD__() 
{
	test_c++;
}

void Superviser::__TEST__() 
{
    std:: cout << total_packages_ << std::endl; 
    std:: cout << generated_request_per_source_[0] << std::endl;
    std:: cout << generated_request_per_source_[1] << std::endl;
    std:: cout << generated_request_per_source_[2] << std::endl;

    std:: cout << dropped_request_per_source_[0] << std::endl;
    std:: cout << dropped_request_per_source_[1] << std::endl;
    std:: cout << dropped_request_per_source_[2] << std::endl;

    std::cout << test_c << std::endl;
    // std:: cout << generated_request_per_source_[1] << std::endl;
    // std:: cout << generated_request_per_source_[2] << std::endl;
}

//состояние
void Superviser::_next() 
{
	this->time_.sort();
	this->current_ = this->time_.front();
	this->time_.pop_front();
};

bool Superviser::_over()
{   
	return (total_packages_ < n_requests_)?false:true;
};

//зарегистрировать пакеты
void Superviser::_addPackage(Package * package) 
{
    int   n                 =   package -> _getNofSource() - 1;
    float arrived_buffer    =   package -> _getArrivedBuffer();
    float arrived_device    =   package -> _getArrivedDevice();
    float done              =   package -> _getDone();

    if (n == 0)
    {
        __ADD__();
    } else 

    this -> generated_request_per_source_[n]++;
    this -> waited_on_buffer_per_source_[n].push_back(arrived_device - arrived_buffer);
    this -> spend_on_device_[n].push_back(done - arrived_device);
    this -> spend_in_system_[n].push_back(done - arrived_buffer);
}

void Superviser::_droppPackage(Package * package) 
{
    int n = package -> _getNofSource() - 1;
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


void 	Superviser::_addSourcePicture(Package  *  array)
{
    std::vector<int> temp;
    for (int i = 0; i < n_sources_; i++)
    {
        if (array[i]._isActive())
        {
            temp.push_back(array[i]._getNofSource());
        } else 
        {
            temp.push_back(-1);
        }
    }
    source_picture_ -> swap(temp);
}

void 	Superviser::_addBufferPicture(Package  *  array)
{
    std::vector<int> temp;
    for (int i = 0; i < n_buffers_; i++)
    {
        if (array[i]._isActive())
        {
            temp.push_back(array[i]._getNofSource());
        } else 
        {
            temp.push_back(-1);
        }
    }
    buffer_picture_ -> swap(temp);
}

void 	Superviser::_addDevicePicture(Package  *  array)
{
    std::vector<int> temp;
    for (int i = 0; i < n_sources_; i++)
    {
        if (array[i]._isActive())
        {
            temp.push_back(array[i]._getNofSource());
        } else 
        {
            temp.push_back(-1);
        }
    }
    device_picture_ -> swap(temp);
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



Picture	Superviser::_picture()
{
    return Picture(source_picture_, buffer_picture_, device_picture_);
}
