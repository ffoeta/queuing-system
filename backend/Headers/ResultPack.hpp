#ifndef RESULTPACK_HPP
#define RESULTPACK_HPP

#include <vector>
#include <numeric>
#include "Package.hpp"
#include "State.hpp"

class ResultPack {
public:
	//конструктор
	ResultPack();

	//сеттер
	void 		set(int N);

	//зарегистрировать пакеты
	void 		addPackage(Package p);
	void 		droppPackage(Package p);

	//расчеты статистики
	float getAverageFaillure(int i);
	float getAverageWaitTime(int i);
	float getAverageSpendOnDevice(int i);
	float getAverageSpendInSystem(int i);

	//текущая статистика для каждого источника
	State 		sample();

private:

	int 									N_;
	int 							* 		generated_request_per_source;
	int 							* 		dropped_request_per_source;

    std::vector<float>	 			* 		waited_on_buffer_per_source;
	std::vector<float>				* 		spend_on_device;
    std::vector<float>				* 		spend_in_system;
};


#endif
