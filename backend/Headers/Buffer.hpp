#ifndef BUFFER_HPP
#define BUFFER_HPP

#include "Superviser.hpp"
#include "Package.hpp"

class Buffer {
public:

	//конструктор
	Buffer(Superviser * superviser, int n_buffers);

	//принять посылку
	void 				_recievePackage(Package package);

	//выбираем по заказу устройства f посылок из буфера
	std::list<Package> 	_sendPackages(int f);

	//поиск и управление через current_
	void 				_findPlaceToInsertPackage();
	int 				_chooseHighestPackagePrior();
	void 				_inc();
	void 				_dec();

	//состояние
	void 				_picture();
	int 				_capacity();
	int					_free();
	bool 				_done();

private:

	Superviser 	* 	superviser_;
	int 			n_buffers_;	
	Package  	*	buffer_packages_;
	int 			current_;
	
};



#endif
