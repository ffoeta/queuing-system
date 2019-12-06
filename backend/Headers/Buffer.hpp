#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "Superviser.hpp"

class Buffer {
private:

	Superviser 	* 	superviser_;
	int 			N_;
	Package  	*	array_;
	int 			current_;
	
public:

	//конструктор деструктор
	Buffer();
	~Buffer();

	//сеттер
	void 				set(Superviser * superviser, int N);

	//принять посылку
	void 				recievePackage(Package package);

	//выбираем по заказу устройства f посылок из буфера
	std::list<Package> 	select(int f);

	//поиск и управление через current_
	void 				find();
	int 				search();
	void 				inc();
	void 				dec();

	
	//состояние
	int 				capacity();
	bool 				done();
};



#endif
