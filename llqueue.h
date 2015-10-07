#include "slist.h"
template<class T>
class Queue{
	SList<T> theQueue_;
public:
	Queue():theQueue_(){
	}
	void enqueue(const T& dat){
		theQueue_.append(dat);
		
	}
	void dequeue(){
		theQueue_.rmFront();
	}
	const T& front(){
		return theQueue_.first();
	}
	bool isEmpty() const{return theQueue_.first();}
};