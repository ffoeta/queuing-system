#ifndef INNERAPI_HPP
#define INNERAPI_HPP

#include "../Headers/Device.hpp"
#include "../Headers/Source.hpp"

class InnerAPI
{
private:
    Superviser superviser;
	Buffer buffer;
	Source source;
	Device device;

	Run_Type run_type_;
	int n_sources_;
	int n_devices_;
	int n_buffers_;
	int n_requests_;

	float a_;
	float b_;
	float l_;
public:
	InnerAPI();
	void set(Run_Type run_type, int n_sources, int n_buffers, int n_devices, int n_requests, 
			float a, float b, float l);
	ResultContainer run();
	ResultContainer next();
	bool over();
	void build();
	void randomize();
};


#endif