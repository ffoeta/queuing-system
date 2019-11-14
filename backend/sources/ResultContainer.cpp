#include "../headers/ResultContainer.hpp"

ResultContainer::ResultContainer(
    int N, 
    float current, 
    Run_Type debug, 
    int source_created, 
    int dropped, 
    int sources, 
    int devices, 
    int buffers, 
    std::list<Package> packages,
    std::list<float> time) :
    N_(N), 
    current_(current), 
    debug_(debug), 
    source_created_(source_created), 
    dropped_(dropped),
    sources_(sources), 
    packages_(packages), 
    time_(time) {};



    int ResultContainer::getSources() {
        return this -> sources_;
    }

	int ResultContainer::getBuffers() {
        return this -> buffers_;
    }

	int ResultContainer::getDevices() {
        return this -> devices_;
    }

	int ResultContainer::getCreated() {
        return this -> source_created_;
    }

	int	ResultContainer::getDropped() {
        return this -> dropped_;
    }

	int	ResultContainer::getN() {
        return this -> N_;
    }

	float ResultContainer::getCurrent() {
        return this -> current_;
    }

	Run_Type  ResultContainer::getDebug() {
        return this -> debug_;
    }

	std::list<Package>	ResultContainer::getPackages() {
        return this -> packages_;
    }
	std::list<float>	ResultContainer::getTime() {
        return this -> time_;
    }
    