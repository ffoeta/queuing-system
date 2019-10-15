#include "Buffer.hpp"

Buffer::Buffer(Superviser * superviser, int N) : 
	superviser(superviser), N_(N), current_(0) {
	
	doPrint_ = this->superviser->debug();
	this->array_ = new int[N];

	for (int i = 0; i < N_; ++i) {
		array_[i] = -1;
	};
}

Buffer::~Buffer(){
	delete array_;
}

void Buffer::init(Father * obj) {};

void Buffer::send(int i) {};

void Buffer::get(int i) {
	
	this->find();

	if (array_[current_] >= 0) {
		dec();
		this->superviser->drop(array_[current_]);

		if (doPrint_)
			std::cout << "emplace " << array_[current_] << " with " << i << std::endl;

		array_[current_] = i;
	} else {
		
		if (doPrint_)
			std::cout << "Buffer : Recived " << i << " from Source" << std::endl;
		
		array_[current_] = i;
	}
	inc();
};

int Buffer::ask() {
	return this->select();
};

int Buffer::capacity(){
	int count = 0;
	for (int i = 0; i < N_; ++i)
	{
		if (array_[i] == -1) {
			count++;
		}
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
	if (array_[current_] < 0) {
		return;
	}
	int temp = current_;
	do{
		inc();
	} while ( (array_[current_] != -1) && (current_ != temp) );
};

int Buffer::select(){
	int k = 0;

	std::list<int> temp;

	for (int i = 0; i < N_; ++i) {
		temp.push_back(array_[i]);
	};

	temp.sort();

	while (temp.front() == -1) {
		temp.pop_front();
	};

	if (temp.empty()) {
		return -1;
	};


	for (int i = 0; i < N_; ++i) {
		if (array_[i] == temp.front()){
			k = i;
			break;
		};
	};

	this->free(k);

	if (doPrint_)
		std::cout << "Buffer : Sent " << temp.front() << " to Device" << std::endl;

	return temp.front();
}

void Buffer::free(int i) {
	array_[i] = -1;
}

bool Buffer::done() {
	if (this->capacity() == N_)
		return true;
	return false;
};
