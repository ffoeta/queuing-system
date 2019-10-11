#include "Device.hpp"

Device::Device(Superviser * superviser, int N) : 
	superviser(superviser), N_(N), time_(0), current_(0) {

	doPrint_ = this->superviser->debug();
	array_ = new int[N_];
	wait_ = new int[N_];
	
	for (int i = 0; i < N_; ++i) {
		array_[i] = -1;
		wait_[i] = -1;
	}
}


Device::~Device(){
	delete array_;
	delete wait_;
}





void Device::init(Father * buffer) {
	this->buffer = buffer;
};

void Device::get(int i) {};

void Device::send(int i) {};

int Device::ask() {return 0;};







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
	if (array_[current_] < 0) {
		return;
	}
	int temp = current_;
	do{
		inc();
	} while ( (array_[current_] != -1) && (current_ != temp) );
};

void Device::work() {
	time_ = this->superviser->get();
	this->finish();
	this->collect();
};

void Device::collect() {
	int f = this->capacity();

	if (doPrint_)
		std::cout << f << " Devices free " << std::endl;

	for (int i = 0; i < f; ++i) {
		int k = this->buffer->ask();
		if (k >= 0) {
			this->superviser->sent();

			if (doPrint_)
				std::cout << "Device : Recieved " << k << " from Buffer" << std::endl;

			this->find();
			array_[current_] = k;
			wait_[current_] = time_ + fx();
			this->superviser->add(wait_[current_]);
		} else {
			return;
		}
	}
}

void Device::finish() {
	for (int i = 0; i < N_; ++i) {
		if (time_ == wait_[i]) {

			if (doPrint_)
				std::cout << "Device : Done with " << array_[i] << " waited " << wait_[i] << std::endl;

			this->free(i);
		}
	}
};

void Device::free(int i) {
	wait_[i] = -1;
	array_[i] = -1;
};






int Device::fx(){
	return (-1.0 / 1.5*log(rand()/(double)RAND_MAX));
};





int Device::capacity(){
	int count = 0;
	for (int i = 0; i < N_; i++)
	{
		if (array_[i] == -1) {
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









