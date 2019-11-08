#include "../Headers/Superviser.hpp"

Superviser::Superviser(int N, int sources, int buffers, int devices, Run_Type debug) : 
	N_(N), sources_(sources), buffers_(buffers), devices_(devices), debug_(debug), current_(0), dropped_(0), source_created_(0) {
	this->time_ = std::list<float>();
	this->packages_ = std::list<Package>();
}

Superviser::~Superviser(){};

float Superviser::time() {
	return this->current_;
};

int Superviser::add(float N) {
	this->time_.push_back(N);
	return 0;
};

void Superviser::created() {
	this->source_created_++;
};

void Superviser::collect(Package package) {
	if (package.getDeviceDone() == -1) {
		package.setDropped(current_);
		dropped_++;
	}

	this->packages_.push_back(package);
}

Run_Type Superviser::debug() {
	return debug_;
};

void Superviser::next() {
	if (time_.empty()){
		return;
	}
	this->time_.sort();
	this->current_ = this->time_.front();
	this->time_.pop_front();
	if (this->debug_ == MANUAL) {
		std::cout << "NEXT TIME : " << this->current_ <<std::endl;
		std::cin.get();
	}
};

bool Superviser::over() {
	return (source_created_ < N_)?false:true;
};

void Superviser::sort() {

};

std::string Superviser::stat() {
	return("TIME IS "+ std::to_string(current_));
};

void Superviser::stats() { //REDO

	this->sort();

	std::cout << "STATS:  " << std::endl;	
	std::cout << std::endl;	

	std::cout << "  GENERATED:  " << std::endl;	
	std::cout << source_created_ << "  |  " << (float)source_created_/source_created_ << std::endl;	
	std::cout << std::endl;

	std::cout << "  DROPPED:  " << std::endl;	
	std::cout << dropped_ << "  |  " << (float)dropped_/source_created_<< std::endl;	
	std::cout << std::endl;


	for (std::list<Package>::iterator package = packages_.begin(); package != packages_.end(); ++package){};
};


