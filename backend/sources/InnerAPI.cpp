#include "../headers/InnerAPI.hpp"

//коснтруктор деструктор
InnerAPI::InnerAPI() : 
	run_type_(NONE), n_sources_(0), n_buffers_(0), n_devices_(0),
	n_requests_(0), a_(0), b_(0), l_(0), 
	superviser_(nullptr), buffer_(nullptr), source_(nullptr), device_(nullptr)
{}

InnerAPI::~InnerAPI()
{
	if (superviser_ != nullptr)
	{
		delete superviser_;
	}
	if (buffer_ != nullptr)
	{
		delete buffer_;
	}
	if (source_ != nullptr)
	{
		delete source_;
	}
	if (device_ != nullptr)
	{
		delete device_;
	}
}

//ребут
void InnerAPI::reboot() 
{
	delete buffer_;
	delete source_;
	delete device_;

  	this -> set(n_sources_, n_buffers_, n_devices_, n_requests_, a_, b_, l_);
};

//сеттеры
void InnerAPI::set(int n_sources, int n_buffers, int n_devices, int n_requests, 
			float a, float b, float l){
		this -> n_sources_ = n_sources;
		this -> n_buffers_ = n_buffers;
		this -> n_devices_ = n_devices;
		this -> n_requests_ = n_requests;
		this -> a_ = a;
		this -> b_ = b;
		this -> l_ = l;

		this -> superviser_ = new Superviser();
		this -> buffer_ = new Buffer();
		this -> source_ = new Source();
		this -> device_ = new Device();

		this -> superviser_ -> set(n_requests_, n_sources_, n_buffers_, n_devices_);
		this -> buffer_ -> set(superviser_, n_buffers_);
		this -> source_ -> set(superviser_, buffer_, n_sources_);
		this -> device_ -> set(superviser_, buffer_, n_devices_);

		this -> source_ -> setConstants(a_, b_);
		this -> device_ -> setConstant(l_);
}

void InnerAPI::setRunType(Run_Type run_type){
	this -> run_type_ = run_type;
}

//гетеры
int InnerAPI::getNSources() {
	return this -> n_sources_;
}

int InnerAPI::getNBuffers() {
	return this -> n_buffers_;
}

int InnerAPI::getNDevices() {
	return this -> n_devices_;
}

//исполнение программы
State InnerAPI::run()
{
	while (!superviser_ -> over() || !source_ -> done() || !buffer_ -> done() || !device_ -> done()) 
	{
		source_ -> work();
		device_ -> work();
		superviser_ -> next();
	}
	return superviser_ -> state();
}

State InnerAPI::next()
{
	source_ 			-> work();
	device_ 			-> work();
	superviser_ 		-> next();
	return	superviser_ -> state();
}
