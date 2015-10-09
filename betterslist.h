#include <iostream>
using namespace std;


template <class T>
class SList{
	Node<T>* first_;
	Node<T>* last_;
	void rrwork(Node<T>* curr);
	struct Node{
		T data_;
		Node<T>* next_;
		Node(const T& data=T{},Node<T>* next=nullptr){
			data_=data;
			next_=next;
		}
	};
public:
	class const_iterator{
	friend SList<T>;
	protected:
		Node* curr_;
		const_iterator(Node* p){
			curr_ = p;
		}
	public:
		const_iterator(){
			curr_=nullptr;
		}
		const_iterator operator++(){
			//++p
			curr_=curr_->next_;
			return *this;
		}
		const_iterator operator++(int){
			//p++
			const_iterator old=*this;
			curr_=curr_->next_;
			return old;

		}
		bool operator==(const_iterator rhs){
			return curr_==rhs.curr_;
		}
		bool operator!=(const_iterator rhs){
			return curr_!=rhs.curr_;
		}
		const T& operator*() const{
			return curr_->data_;
		}
	};
	class iterator : const_iterator{

	};
	SList(){first_=last_=nullptr;}
	const_iterator begin() const {return }
	const_iterator end() const {return}
	iterator begin(){}
	iterator end(){}
	void insert(const T& data);
	void print() const;
	void append(const T& data);
	void rmFirst();
	void rmLast();
	void reverse();
	void recursiveReverse();

};
//this function inserts data into the front
//of the linked list
template<class T>
void SList<T>::insert(T data){
	Node<T>* nn=new Node<T>(data,first_);
	first_=nn;
	if(!last_){
		last_=nn;
	}
}
//remove first node from list
template<class T>
void SList<T>::rmFirst(){
	if(first_){
		Node<T>* rm=first_;
		first_=first_->next_;
		if(!first_){
			last_=nullptr;
		}
		delete rm;
	}
}

//remove last node from list
template<class T>
void SList<T>::rmLast(){
	if(first_){
		Node<T>* rm=last_;
		Node<T>* curr=first_;
		if(rm !=curr){
			while(curr->next_!=rm){
				curr=curr->next_;
			}
			last_=curr;
			last_->next_=nullptr;
		}
		else{
			first_=last_=nullptr;
		}
		delete rm;
	}

}

//
template<class T>
void SList<T>::append(T data){
	Node<T>* nn=new Node<T>(data);
	if(first_){
		last_->next_ = nn;
	}
	else{
		first_=nn;
	}
	last_=nn;
}


template<class T>
void SList<T>::reverse(){
	Node<T>* prev;
	Node<T>* curr;
	Node<T>* next;
	//if statement is true, list has at 
	//least 2 nodes
	if(first_!=last_){
		prev=first_;
		curr=first_->next_;
		next=curr->next_;
		while(curr){
			curr->next_=prev;
			prev=curr;
			curr=next;
			if(curr)
				next=curr->next_;

		}
		first_->next_=nullptr;
		last_=first_;
		first_=prev;
	}
}

//this function reverses a list starting
//at node pointed to by curr
template<class T>
void SList<T>::rrwork(Node<T>* curr){
	if(curr && curr->next_){
		Node<T>* tmp=curr->next_;
		//at least two nodes in list
		rrwork(curr->next_);
		tmp->next_=curr;
	}
}

template<class T>
void SList<T>::recursiveReverse(){
	if(first_){
		Node<T>* tmp=first_;
		rrwork(first_);
		first_=last_;
		last_=tmp;
		last_->next_=nullptr;
	}
}


template<class T>
void SList<T>::print() const{
	Node<T>* curr=first_;
	while(curr){
		cout << curr->data_ << endl;
		curr=curr->next_;
	}
}
