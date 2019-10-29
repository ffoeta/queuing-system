#include "Device.hpp"

Device::Device(Superviser * superviser, Buffer * buffer, int N) : 
	superviser_(superviser), buffer_(buffer), N_(N), time_(0), current_(0) {

	doPrint_ = this->superviser_->debug();
	array_ = new Package[N_];
}

Device::~Device(){
	delete array_;
}

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
		if (doPrint_)
			std::cout << " Nothing taken from buffer. " << std::endl;
		return;
	}

	if (doPrint_)
		std::cout << packages.size() << " requests taken from buffer. " << std::endl;

	for (std::list<Package>::iterator package = packages.begin(); package != packages.end(); ++package)
	{
		this->find();
		array_[current_] = *package;
		array_[current_].setDeviceArrived(this->time_);
		array_[current_].setDeviceDone(this->time_ + this->fx());

		this->superviser_->add(array_[current_].getDeviceDone());

		if (doPrint_)
			std::cout << current_ <<"|  Job added arrived at" <<array_[current_].getDeviceArrived()  << " set to " << array_[current_].getDeviceDone() << std::endl;
		inc();
	}

};

void Device::work() {
	time_ = this->superviser_->time();
	this->finish();
	this->collect();
};

void Device::collect() {
	int f = this->capacity();

	if (doPrint_)
		std::cout << f << " Devices free " << std::endl;

	this->place(buffer_->select(f));
};

void Device::finish() {

	for (int i = 0; i < N_; ++i)
	{
		if (array_[i].getDeviceDone() == time_ ) {
			superviser_->collect(array_[i]);
			if (doPrint_)
				std::cout << "Device : Done with " << array_[i].getN() << std::endl;
			this->free(&array_[i]);
		};
	};
	
};

void Device::free(Package * package) {
	package->reboot();
};

float Device::fx(){
	return (-1.0 / 1.5*log(rand()/(double)RAND_MAX));
};

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
