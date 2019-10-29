#include "Device.hpp"
#include "Buffer.hpp"
#include "Source.hpp"


int main(int argc, char* argv[]) {

	int N1;
	int N2;
	int N3;
	int L;
	int INFO;

	std::srand(std::time(nullptr));
	try {

		N1 	 = 	std::stoi(argv[1]);
		N2 	 = 	std::stoi(argv[2]);
		N3 	 = 	std::stoi(argv[3]);
		L 	 = 	std::stoi(argv[4]);
		INFO = 	std::stoi(argv[5]);

	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	} 

	Superviser superviser(L, N1, N2, N3, INFO);
	Buffer buffer(&superviser, N2);
	Source source(&superviser, &buffer, N1);
	Device device(&superviser, &buffer, N3);

	while (!superviser.over() || !source.done() || !buffer.done() || !device.done()) {
		source.work();
		device.work();
		superviser.next();
	}

	superviser.stats();

};
