#include "Buffer.hpp"

Buffer::Buffer(Superviser * superviser, int N) : 
	superviser_(superviser), N_(N), current_(0) {

	doPrint_ = this->superviser_->debug();
	this->array_ = new Package[N_];
};

Buffer::~Buffer(){
	delete array_;
};

void Buffer::get(Package package) {
	
	this->find();

	if (!array_[current_].null()) {
		dec();

		superviser_->collect(array_[current_]);

		if (doPrint_)
			std::cout << "emplaced " << array_[current_].getN() << " with " << package.getN() << std::endl;

		array_[current_] = package;
	} else {
		
		if (doPrint_)
			std::cout << "Buffer : Recived " << package.getN() << " from Source" << std::endl;
		
		array_[current_] = package;
	}
	inc();
};

int Buffer::search() {
	if (this->done()) {
		return -1;
	}

	int value = RAND_MAX;
	int k = -1;
	int n = -1;

	for (int i = 0; i < N_; ++i)
	{
		if (!array_[i].null()) {
			n = array_[i].getN();
			if (n < value) {
				value = n;
				k = i;
			}
		}

	}

	return k;
};


std::list<Package> Buffer::select(int f){

	std::list<Package> result;
	int r = 0;

	for (int i = 0; i < f; ++i) {
		while(r != -1){
			r = this->search();

			if (r != -1){
				result.push_back(array_[r]);
				free(r);
			};

		};
	};
	return result;
};

int Buffer::capacity(){
	int count = 0;
	for (int i = 0; i < N_; ++i)
	{
		if (array_[i].null()) {
			count++;
		};
	}
	return count;
};

void Buffer::inc() {
	if (current_ + 1 == N_) {
		current_ = 0;
	} else {
		current_++;
	}
};

void Buffer::dec() {
	if (current_ - 1 < 0) {
		current_ = N_-1;
	} else {
		current_--;
	}
}


void Buffer::find() {
	if (array_[current_].null()) {
		return;
	}
	int temp = current_;
	do{
		inc();
	} while ( (!array_[current_].null()) && (current_ != temp) );
};


void Buffer::free(int i) {
	array_[i].reboot();
};

bool Buffer::done() {
	if (this->capacity() == N_)
		return true;
	return false;
};
