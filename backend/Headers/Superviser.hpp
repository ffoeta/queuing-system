#ifndef SUPERVISER_HPP
#define SUPERVISER_HPP

#include <list>
#include "ResultPack.hpp"

class Superviser {
private:
	int 					N_;

	int 					sources_; 
	int 					buffers_;
	int 					devices_;

	float 					current_;

	int 					source_created_;

	ResultPack 				data_;
	std::list<float> 		time_;
public:

	//конструктор
	Superviser();

	//сеттер
	void 		set(int N, int sources, int buffers, int devices);

	//текущее время в системе
	float 		getCurrentTime();

	//добавить событие
	void 		addEvent(float time);
	
	//обновить кол-во заявок
	void 		addGenerated();

	//регистрация выбывших пакетов
	void 		addPackage(Package p);
	void 		droppPackage(Package p);

	//состояние
	void 		next();
	State   	state();
	bool 		over();
	
};

#endif
