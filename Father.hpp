#ifndef FATHER_HPP

class Father
{
public:
	virtual void init(Father * obj) = 0;
	virtual void send(int i) = 0;
	virtual void get(int i) = 0;
	virtual int ask() = 0;
};

#define FATHER_HPP 
#endif