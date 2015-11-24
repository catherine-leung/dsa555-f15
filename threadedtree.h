#include <iostream>
using namespace std;

template <class T>
class ThreadedTree{
	struct Node{
		T data_;
		Node* left_;
		Node* right_;
		bool leftIsThread_;
		bool rightIsThread_;
		Node(const T& data=T{},Node* left=nullptr, Node* right=nullptr){
			data_=data;
			left_=left;
			right_=right;
			leftIsThread_=true;
			rightIsThread_=true;
		}
	};
	Node* root_;	
	void print(const Node* rt, int lvl)const{
		//I won't test this on the main.  You might find it useful
		//to implement for testing purposes
		//Note, passed in lvl so that you can use indentations based on lvl to 
		//see where a node is within your tree.  if you don't want to use it
		//just alter the prototype.

	}

public:
	class const_iterator{
	protected:
		Node* curr_;
		const_iterator(Node* c){curr_=c;}
	public:
		const_iterator(){
			curr_=nullptr;
		}
		const_iterator operator++(int){
		}
		const_iterator operator--(int){
		}
		const T& operator*(){
			return curr_->data_;
		}
		bool operator==(const const_iterator& rhs) const{
			return curr_ == rhs.curr_;
		}
		bool operator!=(const const_iterator& rhs) const{
			return curr_ != rhs.curr_;
		}
		friend class ThreadedTree;
	};
	class iterator:public const_iterator{
		iterator(Node* c):const_iterator(c){}
	public:
		iterator():const_iterator(){}
		const T& operator*(){
			return this->curr_->data_;
		}
		iterator operator++(int){
		}
		iterator operator--(int){
		}
		friend class ThreadedTree;
	};

	ThreadedTree(){
		root_=nullptr;
	}
	iterator insert(const T& data){

	}
	iterator find(const T& data) const{

	}
	iterator begin(){

	}
	iterator end(){
	}
	const_iterator begin()const{
	}
	const_iterator end() const{
	}
	void print() const{
		print(root_,0);
	}
	~ThreadedTree(){

	}
};