#include "slist.h"
template<class T>
class Stack{
	SList<T> theStack_;
public:
	Stack():theStack_(){
	}
	void push(const T& data){
		theStack_.insert(data);
	}
	void pop(){
		theStack_.rmFirst();
	}
	const T& top(){
		return theStack_.first()->data();
	}
	bool isEmpty() const{
		return theStack_->first();
	}
};
