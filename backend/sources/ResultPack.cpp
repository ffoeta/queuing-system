#include "../headers/ResultPack.hpp"

//конструктор 
ResultPack::ResultPack() :
    N_(0), generated_request_per_source(0), dropped_request_per_source(0),
    waited_on_buffer_per_source(0), spend_on_device(0), spend_in_system(0)
    {}

//сеттер
void ResultPack::set(int N)
{
    if (generated_request_per_source != nullptr) 
    {
        delete generated_request_per_source;
    }
    
    if (dropped_request_per_source != nullptr) 
    {
        delete dropped_request_per_source;
    }
    
	if (waited_on_buffer_per_source != nullptr)
    {
		waited_on_buffer_per_source -> clear();
	}
    
    if (spend_on_device != nullptr)
    {
        spend_on_device -> clear();
    }
    
    if (spend_in_system != nullptr)
    {
        spend_in_system -> clear();
    }

    this -> N_ = N;
    this -> generated_request_per_source = new int[N_];
    this -> dropped_request_per_source = new int[N_];

    this -> waited_on_buffer_per_source = new std::vector<float>[N_];
    this -> spend_on_device = new std::vector<float>[N_];
    this -> spend_in_system = new std::vector<float>[N_];

    for (int i = 0; i < N_; i++) 
    {
        this -> generated_request_per_source[i] = 0;;
        this -> dropped_request_per_source[i] = 0;

        this -> waited_on_buffer_per_source[i].clear();
        this -> spend_on_device[i].clear();
        this -> spend_in_system[i].clear();
    }
}

//зарегистрировать пакеты
void ResultPack::addPackage(Package package) 
{

    int n                   =   package.getNofSource();
    float arrived_buffer    =   package.getArrivedBuffer();
    float arrived_device    =   package.getArrivedDevice();
    float done              =   package.getDone();

    this -> generated_request_per_source[n]++;

    this -> waited_on_buffer_per_source[n].push_back(arrived_device - arrived_buffer);
    this -> spend_on_device[n].push_back(done - arrived_device);
    this -> spend_in_system[n].push_back(done - arrived_buffer);
}

void ResultPack::droppPackage(Package package) 
{
    int n = package.getNofSource();
    this -> dropped_request_per_source[n]++;
}

//расчеты статистики

//процент отказа
float ResultPack::getAverageFaillure(int i) 
{
    if (generated_request_per_source[i] == 0) return 0;
    
    return dropped_request_per_source[i] / generated_request_per_source[i];
}

float ResultPack::getAverageWaitTime(int i)
{   
    if (waited_on_buffer_per_source[i].empty()) return 0;

    float temp = std::accumulate(waited_on_buffer_per_source[i].begin(), waited_on_buffer_per_source[i].end(), 0);

    return  temp / waited_on_buffer_per_source[i].size();
}

float ResultPack::getAverageSpendOnDevice(int i)
{
    if (spend_on_device[i].empty()) return 0;

    auto temp = std::accumulate(spend_on_device[i].begin(), spend_on_device[i].end(), 0);
       
    return temp / spend_on_device[i].size();
}

float ResultPack::getAverageSpendInSystem(int i)
{
    if (spend_in_system[i].empty()) return 0;

    auto temp =  std::accumulate(spend_in_system[i].begin(), spend_in_system[i].end(), 0);

    return  temp / spend_in_system[i].size();
}


//текущаая статистика для каждого источника
State ResultPack::sample() 
{
    std::vector<float> average_probability_of_failure;
    std::vector<float> average_waited_on_buffer_per_source;
    std::vector<float> average_spend_on_device;
    std::vector<float> average_spend_in_system;

    //средние значения и шанс отказа
    for (int i = 0; i < N_; i++)
    {        
        average_probability_of_failure.push_back(this -> getAverageFaillure(i));
        average_waited_on_buffer_per_source.push_back(this -> getAverageWaitTime(i));
        average_spend_on_device.push_back(this -> getAverageSpendOnDevice(i));
        average_spend_in_system.push_back(this -> getAverageSpendInSystem(i));
    }

    return State(average_probability_of_failure, average_waited_on_buffer_per_source,
        average_spend_on_device, average_spend_in_system);
}
