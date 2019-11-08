#ifndef SUPERVISER_HPP
#define SUPERVISER_HPP

#include <list>
#include <iostream>

#include "Package.hpp"
#include "RunType.hpp"

class Superviser {
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
	Superviser(int N, int sources, int buffers, int devices, Run_Type run_t);
	~Superviser();

	std::string stat();
	Run_Type debug();

	bool 	over();
	void 	next();

	float 	time();

	void 	collect(Package packages);
	int 	add(float N);
	void	created();
	
	void 	stats();
	void 	sort();
	
};

#endif
