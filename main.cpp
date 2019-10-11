#include "Device.hpp"
#include "Buffer.hpp"
#include "Source.hpp"


int main(int argc, char* argv[]) {

	std::srand(std::time(nullptr));

	int N1 = std::stoi(argv[1]);
	int N2 = std::stoi(argv[2]);
	int N3 = std::stoi(argv[3]);
	int L = std::stoi(argv[4]);
	int INFO = std::stoi(argv[5]);

	Superviser superviser(L, INFO);
	Source source(&superviser, N1);
	Buffer buffer(&superviser, N2);
	Device device(&superviser, N3);

	source.init(&buffer);
	buffer.init(&device);
	device.init(&buffer);

	while (!superviser.over()) {
		source.get(0);
		device.work();
		superviser.next();
	}

	// source.stats();

	// buffer.stats();

	// device.stats();

	superviser.stats();

};