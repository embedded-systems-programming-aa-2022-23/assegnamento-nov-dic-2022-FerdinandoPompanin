#include "monitor.h"

#include <mutex>
using std::mutex;
using std::unique_lock;

PC::PC(int capacity)
	: capacity_(capacity),  count_(0), buffer_(), stop_(false)
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
	while(count_ == 0 && !order_to_stop())
		not_empty_.wait(mlock);
		
	//serve per uscire dal take se la thread deve morire
	if(order_to_stop())
	{
		mlock.unlock();
  		not_empty_.notify_one();//risveglio a cascata
  		return pos;
	}
	
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

void PC::finish(){

	while(buffer_.size()!=0)
	{}
	
	stop_ = true;
	
	not_empty_.notify_one();//questo serve a svegliare una thread robot ferma a not_empty.wait(mlock), le altre si rivegliano a cascata
}

bool PC::order_to_stop() const{
	return stop_;
}






