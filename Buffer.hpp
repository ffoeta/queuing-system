#ifndef BUFFER_HPP

#include "Father.hpp"
#include "Superviser.hpp"
#include <iostream>

class Buffer : public Father {
private:
	int 	N_;
	int  * 	array_;
	int 	current_;
	bool 	doPrint_;

	Superviser * 	superviser;
public:
	Buffer(Superviser * superviser, int N);
	~Buffer();

	void 	init(Father * obj) 	override;
	void 	send(int i) 		override;
	void 	get(int i) 			override;
	int 	ask() 				override;



	void 	inc();
	void 	dec();
	void 	find();
	int 	select();
	void	free(int i);

	int 	capacity();
	bool 	done();
};


#define BUFFER_HPP
#endif