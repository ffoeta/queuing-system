#include "Source.hpp"


Source::Source(Superviser * superviser, Buffer * buffer, int N) : 
	superviser_(superviser), buffer_(buffer), N_(N), time_(0) {

	doPrint_ = this->superviser_->debug();
	this->array_ = new Package[N_];

	for (int i = 0; i < N_; ++i) {
		array_[i].init(i);
	}
}

Source::~Source(){
	delete this->array_;
};

void Source::create(Package * package) {
	package->setSourceInitiated(this->time_);
	package->setSourceCreated(this->time_ + this->fx());
	this->notify(package->getSourceCreated());
}


void Source::send(Package * package) {
	buffer_->get(*package);
	this->free(package);
};

void Source::generate() {
	for (int i = 0; i < N_; i++) {
		if (array_[i].null()) {
			this->create(&array_[i]);
				if (doPrint_)
					std::cout << "Source: set to " << this->array_[i].getSourceCreated() << std::endl;
		}
	}
};


void Source::collect() {
	for (int i = 0; i < N_; i++) {
		if (array_[i].getSourceCreated() == this->time_) {
			if (doPrint_)
				std::cout << "Source : Time is up. " << i << " send to buffer" << std::endl;
			this->send(&array_[i]);
		};
	};
};

float Source::fx(){
	int a = 0;
	int b = 1;
	return (double)a+(double)(b-a)*(rand()%100)/100;;
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
