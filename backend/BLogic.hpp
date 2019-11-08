#ifndef BLOGIC_HPP
#define BLOGIC_HPP

#include "Headers/Device.hpp"
#include "Headers/Source.hpp"

void run(Run_Type run_t, int N1, int N2, int N3,int L, int INFO) {

	std::srand(std::time(nullptr));

	Superviser superviser(L, N1, N2, N3, INFO);
	Buffer buffer(&superviser, N2);
	Source source(&superviser, &buffer, N1);
	Device device(&superviser, &buffer, N3);

	while (!superviser.over() || !source.done() || !buffer.done() || !device.done()) {
		source.work();
		device.work();
		superviser.next(run_t);
	}

	superviser.stats();

};

#endif
