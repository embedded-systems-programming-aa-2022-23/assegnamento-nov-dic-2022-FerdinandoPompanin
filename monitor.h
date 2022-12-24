#ifndef monitor_h
#define monitor_h

#include <vector>
#include <mutex>
#include <condition_variable> 

#include "griglia.h"

typedef Cella datatype;

class PC{

public:
	PC(int capacity);
	void append(datatype v);
	datatype take();

private:
	int capacity_;
	
	int front_;
	int rear_;
	int count_;
	
	std::vector<datatype> buffer_;
	
	std::mutex mutex_;
	std::condition_variable not_empty_;
	std::condition_variable not_full_;

};
#endif
