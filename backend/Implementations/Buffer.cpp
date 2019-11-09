#include "../Headers/Buffer.hpp"

void Buffer::set(Superviser * superviser, int N) {
	this -> superviser_ = superviser;
	this -> N_ = N;
	this -> current_ = 0;
	this -> debug_ = this->superviser_->debug();
	this -> array_ = new Package[N_];
}

std::string Buffer::stat() {
	return("BUFFER	| total: " + std::to_string(N_) + " | free: " + std::to_string(capacity()));
};

void Buffer::get(Package package) {
	
	this->find();

	if (!array_[current_].null()) {
		dec();

		superviser_->collect(array_[current_]);

		array_[current_] = package;
	} else {
		
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
