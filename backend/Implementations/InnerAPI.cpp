#include "../Interface/InnerAPI.hpp"

InnerAPI::InnerAPI() : 
	run_type_(MANUAL), n_sources_(0), n_buffers_(0), n_devices_(0),
	n_requests_(0), a_(0), b_(0), l_(0), superviser(), buffer(), source(), device()
{};

ResultContainer InnerAPI::run(){

	this->randomize();

	while (!superviser.over() || !source.done() || !buffer.done() || !device.done()) {
		source.work();
		device.work();
		superviser.next();
	}
	return superviser.result();
}

ResultContainer InnerAPI::next(){
		source.work();
		device.work();
		superviser.next();
	return this -> superviser.result();
}

bool InnerAPI::over() {
	return (superviser.over() && source.done() && buffer.done() && device.done());
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

		superviser.set(n_requests_, n_sources_, n_buffers_, n_devices_, run_type_);
		buffer.set(&superviser, n_buffers_);
		source.set(&superviser, &buffer, n_sources_);
		device.set(&superviser, &buffer, n_devices_);

		source.setConstants(a_, b_);
		device.setConstant(l_);
}

void InnerAPI::build() {

};

