#include <iostream>
using namespace std;


template <class T>
class SList{
	struct Node{
		T data_;
		Node* next_;
		Node(const T& data=T{},Node* next=nullptr){
			data_=data;
			next_=next;
		}
	};
	Node* first_;
	Node* last_;
	void rrwork(Node* curr);

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
	protected:
		friend SList<T>;

		iterator(Node* p):const_iterator(p){}
	public:
		iterator():const_iterator(){
		}
		iterator operator++(){
			//++p
			this->curr_=this->curr_->next_;
			return *this;
		}
		iterator operator++(int){
			//p++
			iterator old=*this;
			this->curr_=this->curr_->next_;
			return old;
		}
		bool operator==(iterator rhs){
			return this->curr_==rhs.curr_;
		}
		bool operator!=(iterator rhs){
			return this->curr_!=rhs.curr_;
		}
		T& operator*(){
			return this->curr_->data_;
		}

	};
	SList(){
		first_=new Node;
		last_=new Node;
		first_->next_=last_;
	}
	const_iterator begin() const {return const_iterator(first_->next_);}
	const_iterator end() const {return const_iterator(last_);}
	iterator begin(){return iterator(first_->next_);}
	iterator end(){return iterator(last_);}
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
void SList<T>::insert(const T& data){
	Node* nn=new Node(data,first_->next_);
	first_->next_=nn;
}
//remove first node from list
template<class T>
void SList<T>::rmFirst(){
	if(first_->next != last_){
		Node* rm=first_->next_;
		first_->next_=rm->next_;

		delete rm;
	}
}

//remove last node from list
template<class T>
void SList<T>::rmLast(){
	if(first_->next_ != last_){
		Node* rm;
		Node* prev=first_;
		Node* curr=first_->next_;
		while(curr->next_!=last_){
			prev=curr;
			curr=curr->next_;
		}
		prev->next_=last;
		delete curr;
	}

}

//
template<class T>
void SList<T>::append(const T& data){
	Node* nn=new Node(data);
	if(first_->next_==last_){
		insert(data);		
	}
	else{
		Node* prev=first_->next_;
		while(prev->)	
}


template<class T>
void SList<T>::reverse(){
	Node* prev;
	Node* curr;
	Node* next;
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
void SList<T>::rrwork(Node* curr){
	if(curr && curr->next_){
		Node* tmp=curr->next_;
		//at least two nodes in list
		rrwork(curr->next_);
		tmp->next_=curr;
	}
}

template<class T>
void SList<T>::recursiveReverse(){
	if(first_){
		Node* tmp=first_;
		rrwork(first_);
		first_=last_;
		last_=tmp;
		last_->next_=nullptr;
	}
}


template<class T>
void SList<T>::print() const{
	Node* curr=first_;
	while(curr){
		cout << curr->data_ << endl;
		curr=curr->next_;
	}
}
