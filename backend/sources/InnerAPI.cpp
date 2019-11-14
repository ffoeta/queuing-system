#include "../headers/InnerAPI.hpp"

InnerAPI::InnerAPI() : 
	run_type_(MANUAL), n_sources_(0), n_buffers_(0), n_devices_(0),
	n_requests_(0), a_(0), b_(0), l_(0) 
{ 
	superviser = new Superviser(); 
	buffer = new Buffer();
	source = new Source();
	device	= new Device(); 
}

ResultContainer InnerAPI::run(){

	this -> randomize();

	while (!superviser -> over() || !source -> done() || !buffer -> done() || !device -> done()) {
		source -> work();
		device -> work();
		superviser -> next();
	}
	return superviser -> result();
}

ResultContainer InnerAPI::next(){
		source -> work();
		device -> work();
		superviser -> next();
	return this -> superviser -> result();
}

bool InnerAPI::over() {
	return (superviser -> over() && source -> done() && buffer -> done() && device -> done());
}

void InnerAPI::randomize() {
    std::srand(std::time(nullptr));
}

void InnerAPI::set(Run_Type run_type, int n_sources, int n_buffers, int n_devices, int n_requests, 
			float a, float b, float l){
		this -> run_type_ = run_type;
		this -> n_sources_ = n_sources;
		this -> n_buffers_ = n_buffers;
		this -> n_devices_ = n_devices;
		this -> n_requests_ = n_requests;
		this -> a_ = a;
		this -> b_ = b;
		this -> l_ = l;

		this -> superviser -> set(n_requests_, n_sources_, n_buffers_, n_devices_, run_type_);
		this -> buffer -> set(superviser, n_buffers_);
		this -> source -> set(superviser, buffer, n_sources_);
		this -> device -> set(superviser, buffer, n_devices_);

		this -> source -> setConstants(a_, b_);
		this -> device -> setConstant(l_);
}


void InnerAPI::reboot() {
  delete superviser; 
  delete buffer; 
  delete source;
  delete device;

  superviser = new Superviser();
  buffer = new Buffer();
  source = new Source();
  device = new Device();

  this -> set(run_type_, n_sources_, n_buffers_, n_devices_, n_requests_, a_, b_, l_);
};

