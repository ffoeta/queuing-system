#ifndef BLOGIC_HPP
#define BLOGIC_HPP

#include "Headers/Device.hpp"
#include "Headers/Source.hpp"

void run(Run_Type run_t, int N1, int N2, int N3,int L) {

	std::srand(std::time(nullptr));

	Superviser superviser(L, N1, N2, N3, run_t);
	Buffer buffer(&superviser, N2);
	Source source(&superviser, &buffer, N1);
	Device device(&superviser, &buffer, N3);

	while (!superviser.over() || !source.done() || !buffer.done() || !device.done()) {
		source.work();
		device.work();
		if (run_t == MANUAL) {
			std::cout << superviser.stat() << std::endl;
			std::cout << source.stat() << std::endl;
			std::cout << buffer.stat() << std::endl;
			std::cout << device.stat() << std::endl;
			std::cout << "-------------------" << std::endl;
		}
		superviser.next();
	}
	superviser.stats();
};

#endif
