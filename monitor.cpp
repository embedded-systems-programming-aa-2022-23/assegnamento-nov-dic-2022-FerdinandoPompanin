#include "monitor.h"

#include <mutex>
using std::mutex;
using std::unique_lock;

PC::PC(int capacity)
	: capacity_(capacity),  count_(0), buffer_()
	{}

void PC::append(datatype v){
	unique_lock<std::mutex> mlock(mutex_);
	while( count_ == capacity_)
		not_full_.wait(mlock);
		
	buffer_.push_back(v);
	++count_;
	mlock.unlock();
	not_empty_.notify_one();
}

datatype PC::take(Cella pos){
	std::unique_lock<std::mutex> mlock(mutex_);
	while(count_ == 0)
		not_empty_.wait(mlock);

	auto min = buffer_.cbegin();
	//scorro la lista per trovare goal a distanza minima
	for(auto it{buffer_.cbegin()++}; it != buffer_.cend(); it++)
	{
		if(distanza_euclidea(pos, *it, 1) < distanza_euclidea(pos, *min, 1))
			min = it;
	}
	//tiro fuori dalla lista il dato e lo elimino
	datatype w = *min;
	buffer_.erase(min);
	
  	count_--;
  	mlock.unlock();
  	not_full_.notify_one();

    return w;
}
