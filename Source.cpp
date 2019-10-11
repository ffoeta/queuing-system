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
	this->superviser->created();
	this->buffer->get(i);
};

void Source::get(int i) {
	this->time_ = superviser->get();
	this->collect();
	this->generate();
};

int Source::ask() {return 0;};

void Source::generate() {
	for (int i = 0; i < N_; i++) {
		if (array_[i] == -1) {
			array_[i] = this->time_ + this->fx();
			if (doPrint_)
				std::cout << "Source : Generated at  " << i << " set to " << this->array_[i] << std::endl;
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
	int x = rand() % 10 + 1;
	return x + 10;
}

void Source::set(int i){
	this->superviser->add(array_[i]);
}

void Source::free(int i){
	array_[i] = -1;
}
















