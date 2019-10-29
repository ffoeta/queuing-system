#ifndef TIMESTACKINTERFACE_HPP
#define TIMESTACKINTERFACE_HPP

#include "Superviser.hpp"

class TimeStackInterface
{
public:
	virtual void notify(float time) = 0;
};


#endif