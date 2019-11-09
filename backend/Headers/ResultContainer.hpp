#ifndef RESULTCONTAINER_HPP
#define RESULTCONTAINER_HPP

#include "Package.hpp"
#include "RunType.hpp"
#include <iostream>
#include <list>

class ResultContainer {
private:
    int 			N_;
	float 			current_;
	Run_Type 		debug_;
	int				source_created_;
	int 			dropped_;
	int				sources_;
	int				devices_;
	int				buffers_;

    std::list<Package>  packages_;
	std::list<float>  	time_;
public:
    ResultContainer(int N, float current, Run_Type debug, int source_created, int dropped, 
    int sources, int devices, int buffers, std::list<Package> packages, std::list<float> time);

	int 				getSources();
	int 				getBuffers();
	int 				getDevices();
	int 				getCreated();
	int					getDropped();
	int					getN();
	float 				getCurrent();
	Run_Type			getDebug();

	std::list<Package>	getPackages();
	std::list<float>	getTime();
};


#endif
