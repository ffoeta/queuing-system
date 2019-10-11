#ifndef SUPERVISER_HPP
#include <list>
#include <iostream>

class Superviser {
private:
	int 			N_;
	int 			created_;
	int 			sent_;
	int 			current_;
	int 			debug_;

	std::list<int>  dropped_;
	std::list<int>  time_;
public:
	Superviser(int N, int debug);
	~Superviser();

	bool 	over();
	void 	next();

	int 	get();
	int 	add(int N);
	void 	drop(int i);
	void 	created();
	void 	sent();
	
	bool 	debug();
	void 	stats();
	
};

#define SUPERVISER_HPP
#endif