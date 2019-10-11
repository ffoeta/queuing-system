#include "Superviser.hpp"

Superviser::Superviser(int N, int debug) : 
	N_(N), debug_(debug), current_(0), created_(0), sent_(0) {
	this->time_ = std::list<int>();
	this->dropped_ = std::list<int>();
}

Superviser::~Superviser(){};

int Superviser::get() {
	return this->current_;
};

bool Superviser::debug() {
	return (debug_ > 0)?true:false;
};

int Superviser::add(int N) {
	this->time_.push_back(N);
	return 0;
};

void Superviser::sent() {
	this->sent_++;
};

void Superviser::created() {
	this->created_++;
};

void Superviser::next() {
	if (time_.empty()){
		return;
	}
	if (this->debug_) {
		std::cout << "----------" << std::endl;
		std::cout << created_ << std::endl;
		std::cout << sent_ << std::endl;
	}
	this->time_.sort();
	this->current_ = this->time_.front();
	this->time_.pop_front();
	if (this->debug_) {
		std::cout << "TIME : " << this->current_ <<std::endl;
	}
};

bool Superviser::over() {
	return (created_ < N_)?false:true;
};

void Superviser::stats() { //REDO

	int stuck = created_ - sent_ - dropped_.size();

	std::cout << "Time is : " 	<< current_ 		<< std::endl; 
	std::cout << "Created : " 	<< created_ 		<< std::endl;
	std::cout << "Sent : " 		<< sent_ 			<< " | " << (double)sent_/created_ 			 << std::endl;
	std::cout << "Dropped : " 	<< dropped_.size()	<< " | " << (double)dropped_.size()/created_ << std::endl;
	std::cout << "Stuck : "		<< stuck 			<< " | " << (double)stuck/created_			 << std::endl;
};

void Superviser::drop(int i){
	this->dropped_.push_back(i);
};
