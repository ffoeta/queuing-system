#include "Source.hpp"


Source::Source(Superviser * superviser, int N) : 
	superviser(superviser), N_(N), time_(0) {

	doPrint_ = this->superviser->debug();
	this->array_ = new int[N_];

	for (int i = 0; i < N_; ++i) {
		array_[i] = -1;
	}
}

Source::~Source(){
	delete this->array_;
};

void Source::init(Father * obj) {
	this->buffer = obj;
};

void Source::send(int i) {
	this->buffer->get(i);
};

void Source::get(int i) {};

int Source::ask() {return 0;};

void Source::generate() {
	for (int i = 0; i < N_; i++) {
		if (this->superviser->over()) {
			return;
		}
		if (array_[i] == -1) {
			array_[i] = this->time_ + this->fx();
			if (doPrint_)
				std::cout << "Source : Generated at  " << i << " set to " << this->array_[i] << std::endl;
			this->superviser->created();
			this->set(i);
		}
	}
};


void Source::collect() {
	for (int i = 0; i < N_; i++) {
		if (array_[i] == this->time_) {
			if (doPrint_)
				std::cout << "Source : Time is up. " << i << " send to buffer" << std::endl;
			this->send(i);
			this->free(i);
		};
	};
};

int Source::fx(){
	int a = 0;
	int b = 1;
	return (double)a+(double)(b-a)*(rand()%100)/100;;
}

void Source::set(int i){
	this->superviser->add(array_[i]);
}

void Source::free(int i){
	array_[i] = -1;
}

void Source::work() {
	this->time_ = superviser->get();
	this->collect();
	
	if (!this->superviser->over()) {
		this->generate();
	}
}

int Source::capacity(){
	int count = 0;
	for (int i = 0; i < N_; ++i) {
		if (array_[i]==-1)
			count++;
	};
	return count;
};

bool Source::done() {
	if (this->capacity() == N_)
		return true;
	return false;
};
