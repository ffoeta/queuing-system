#ifndef SUPERVISER_HPP
#define SUPERVISER_HPP

#include <list>
#include "Package.hpp"

#include "Picture.hpp"
#include "State.hpp"

class Superviser {
public:

	//конструктор
	Superviser(int n_sources, int n_buffers, int n_devices, int n_requests);

	//текущее время в системе
	float 		_getCurrentTime();

	//добавить событие
	void 		_addEvent(float time);
	
	//обновить кол-во заявок
	void 		_addGenerated();

	//регистрация выбывших пакетов
	void 		_addPackage(Package * p);
	void 		_droppPackage(Package * p);

	//состояние
	void 		_next();
	bool 		_over();

	void 		_addSourcePicture(Package  *  array);
	void 		_addBufferPicture(Package  *  array);
	void 		_addDevicePicture(Package  *  array);

	State 		_sample();
	Picture		_picture();



private:

	//расчеты
	float 		_getAverageFaillure(int i);
	float 		_getAverageWaitTime(int i);
	float 		_getAverageSpendOnDevice(int i);
	float 		_getAverageSpendInSystem(int i);

	int 					n_requests_;
	int 					n_sources_; 
	int 					n_buffers_;
	int 					n_devices_;
	float 					current_;

	int 					total_packages_;
	std::list<float> 		time_;

	int 							* 		generated_request_per_source_;
	int 							* 		dropped_request_per_source_;

    std::vector<float>	 			* 		waited_on_buffer_per_source_;
	std::vector<float>				* 		spend_on_device_;
    std::vector<float>				* 		spend_in_system_;

	std::vector<int>				*		source_picture_;
	std::vector<int>				*		buffer_picture_;
	std::vector<int>				*		device_picture_;


};

#endif
