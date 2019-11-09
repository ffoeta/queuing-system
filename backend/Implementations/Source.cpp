#include "../Headers/Source.hpp"

void Source::set(Superviser * superviser, Buffer * buffer, int N) {
	this -> N_ = N;
	this -> time_ = 0;
	this -> a_ = 0;
	this -> b_ = 1;
	this -> superviser_ = superviser; 
	this -> buffer_ = buffer;

	doPrint_ = this->superviser_->debug();
	this->array_ = new Package[N_];

	for (int i = 0; i < N_; ++i) {
		array_[i].init(i);
	}
}

void Source::create(Package * package) {
	package->setSourceInitiated(this->time_);
	package->setSourceCreated(this->time_ + this->fx());
	this->notify(package->getSourceCreated());
}

std::string Source::stat() {
	return("SOURCE	| total: " + std::to_string(N_) + " | free: " + std::to_string(capacity()));
};


void Source::send(Package * package) {
	buffer_->get(*package);
	this->free(package);
};

void Source::generate() {
	for (int i = 0; i < N_; i++) {
		if (array_[i].null()) {
			this->create(&array_[i]);
		}
	}
};


void Source::collect() {
	for (int i = 0; i < N_; i++) {
		if (array_[i].getSourceCreated() == this->time_) {
			this->send(&array_[i]);
		};
	};
};

float Source::fx(){
	return a_+(b_-a_)*(rand()%100)/100;;
}

void Source::setConstants(float a, float b) {
	this->a_ = a;
	this->b_ = b;
}

void Source::notify(float time){
	this->superviser_->add(time);
	this->superviser_->created();
}

void Source::free(Package * package){
	int n = package->getN();
	package->reboot();
	package->init(n);
}

void Source::work() {
	this->time_ = superviser_->time();
	this->collect();
	
	if (!this->superviser_->over()) {
		this->generate();
	}
}

int Source::capacity(){
	int count = 0;
	for (int i = 0; i < N_; ++i) {
		if (array_[i].getSourceInitiated() == -1)
			count++;
	};
	return count;
};

bool Source::done() {
	if (this->capacity() == N_)
		return true;
	return false;
};
