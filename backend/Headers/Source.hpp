#ifndef SOURCE_HPP
#define SOURCE_HPP

#include "../Interface/TimeStackInterface.hpp"
#include "Buffer.hpp"

class Source : public TimeStackInterface {
private:
	int 		N_;
	float 		time_;
	Package  *  array_;
	bool 		doPrint_;

	float		a_;
	float		b_;

	Buffer 		* 	buffer_;
	Superviser 	* 	superviser_;
public:

	void set(Superviser * superviser, Buffer * buffer, int N);

	std::string stat();

	void 	notify(float time);

	void 	create(Package * package);
	void 	send(Package * package);

	void 	generate();
	void 	collect();

	float  	fx();
	void 	setConstants(float a, float b);

	void 	free(Package * package);
	void 	work();
	
	int 	capacity();
	bool 	done();
};



#endif
