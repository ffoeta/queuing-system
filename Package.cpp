#include "Package.hpp"

Package::Package() :
n_(-1),
source_initiated_(-1),
source_created_(-1),
device_arrived_(-1),
device_done_(-1),
dropped_(-1)
{};

	void Package::init(int n) {
		this->setN(n);
	};



	void Package::reboot() {
		this->init(-1);
		this->setSourceInitiated(-1);
		this->setSourceCreated(-1);
		this->setDeviceArrived(-1);
		this->setDeviceDone(-1);
		this->setDropped(-1);
	};



	bool Package::null() {
		return (this->source_initiated_ == -1);
	}

	float Package::getSourceInitiated() {
		return this->source_initiated_;
	};

	float Package::getSourceCreated() {
		return this->source_created_;
	};

	float Package::getDeviceArrived() {
		return this->device_arrived_;

	};

	float Package::getDeviceDone() {
		return this->device_done_;
	};

	float Package::getDropped(){
		return this->dropped_;
	};

	int Package::getN() {
		return this->n_;
	};






	void Package::setSourceInitiated(float time) {
		this->source_initiated_ = time;
	};

	void Package::setSourceCreated(float time) {
		this->source_created_ = time;
	};

	void Package::setDeviceArrived(float time) {
		this->device_arrived_ = time;

	};

	void Package::setDeviceDone(float time) {
		this->device_done_ = time;
	};

	void Package::setDropped(float time){
		this->dropped_ = time;
	};

	void Package::setN(int n) {
		this->n_ = n;
	};

