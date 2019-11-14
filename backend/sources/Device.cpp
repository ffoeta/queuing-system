#include "../headers/Device.hpp"

void Device::set(Superviser * superviser, Buffer * buffer, int N) {
	this -> N_ = N; 
	this -> time_ = 0;
	this -> current_ = 0;
	this -> l_ = 1.5;
	this -> superviser_ = superviser;
	this -> buffer_ = buffer;
	debug_ = this->superviser_->debug();
	array_ = new Package[N_];
}

std::string Device::stat() {
	return("DEVICE	| total: " + std::to_string(N_) + " | free: " + std::to_string(capacity()));
};

void Device::inc() {
	if (current_ + 1 == N_) {
		current_ = 0;
	} else {
		current_++;
	}
};

void Device::dec() {
	if (current_ - 1 < 0) {
		current_ = N_-1;
	} else {
		current_--;
	}
}

void Device::find() {
	if (array_[current_].null()) {
		return;
	}
	int temp = current_;
	do{
		inc();
	} while ( (!array_[current_].null()) && (current_ != temp) );
};

void Device::place(std::list<Package> packages) {
	if (packages.empty()) {
		return;
	}

	for (std::list<Package>::iterator package = packages.begin(); package != packages.end(); ++package)
	{
		this->find();
		array_[current_] = *package;
		array_[current_].setDeviceArrived(this->time_);
		array_[current_].setDeviceDone(this->time_ + this->fx());
		this->notify(array_[current_].getDeviceDone());
		inc();
	}

};

void Device::notify(float time){
	this->superviser_->add(time);
}

void Device::work() {
	time_ = this->superviser_->time();
	this->finish();
	this->collect();
};

void Device::collect() {
	int f = this->capacity();
	this->place(buffer_->select(f));
};

void Device::finish() {

	for (int i = 0; i < N_; ++i)
	{
		if (array_[i].getDeviceDone() == time_ ) {
			superviser_->collect(array_[i]);
			this->free(&array_[i]);
		};
	};
	
};

void Device::free(Package * package) {
	package->reboot();
};

float Device::fx(){
	return (-1.0 / this->l_*log(rand()/(double)RAND_MAX));
};

void Device::setConstant(float l) {
	this->l_ = l;
}

int Device::capacity(){
	int count = 0;
	for (int i = 0; i < N_; i++)
	{
		if (array_[i].null()) {
			count++;
		}
	}
	return count;
};

bool Device::done() {
	if (this->capacity() == N_)
		return true;
	return false;
};
