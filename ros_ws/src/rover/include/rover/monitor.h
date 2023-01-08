#ifndef monitor_h
#define monitor_h

#include <list>
#include <mutex>
#include <condition_variable> 

#include "griglia.h"

typedef Cella datatype;

class PC{

public:
	PC(int capacity);
	void append(datatype v);
	datatype take(Cella pos);
	void finish(); //serve nel main a cambiare il valore di stop_ e a risvegliare i robot in attesa
	bool order_to_stop() const; //serve a vedere il valore di stop_

private:
	int capacity_;
	
	int count_;
	
	std::list<datatype> buffer_;
	
	bool stop_;//serve a notificare che sono stati raggiunti tutti i goal disponibili
	
	std::mutex mutex_;
	std::condition_variable not_empty_;
	std::condition_variable not_full_;

};
#endif
