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
	int 			debug_;
	int				source_created_;
	int 			dropped_;
	int				sources_;
	int				devices_;
	int				buffers_;

	std::list<Package>  packages_;
	std::list<float>  	time_;
public:
	Superviser(int N, int sources, int buffers, int devices, int debug);
	~Superviser();

	bool 	over();
	void 	next(Run_Type run_t);

	float 	time();

	void 	collect(Package packages);
	int 	add(float N);
	void	created();
	
	bool 	debug();
	void 	stats();
	void 	sort();
	
};

#endif
