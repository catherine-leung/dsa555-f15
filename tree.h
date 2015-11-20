#include <iostream>
#include "arrayqueue.h"
using namespace std;
template <class T>	
struct Node{
	T data_;
	Node<T>* left_;  //pointer to left child
	Node<T>* right_; //pointer to right child
	Node(const T& data=T{}, Node<T>* left=nullptr, Node<T>* right=nullptr){
		data_=data;
		left_=left;
		right_=right;
	}
};
template <class T>
class Tree{
	void inorderPrint(const Node<T>* rt) const{
		if(rt!=nullptr){
			inorderPrint(rt->left_);
			cout << rt->data_;
			inorderPrint(rt->right_);
		}
	}
	void preorderPrint(const Node<T>* rt) const{
		if(rt!=nullptr){
			cout << rt->data_;
			preorderPrint(rt->left_);
			preorderPrint(rt->right_);
		}
	}
	void reversePrint(const Node<T>* rt) const{
		if(rt!=nullptr){
			reversePrint(rt->right_);
			cout << rt->data_;
			reversePrint(rt->left_);
		}
	}

	void insert(Node<T>*& rt,const T & data){
		if(rt == nullptr){
			rt = new Node<T>(data);
		}
		else{
			 if(data < rt->data_){
				insert(rt->left_,data);
			}
			else{
				insert(rt->right_,data);
			}
		}
	}
	Node<T>* search(Node<T>* rt,const T& data){
		Node<T>* rc=nullptr;
		if(rt != nullptr){
			if(rt->data_ == data){
				rc=rt;
			}
			else if(data < rt->data_){
				rc=search(rt->left_,data);
			}
			else{
				rc=search(rt->right_,data);
			}
		}
		return rc;
	}
	Node<T>* root_;
public:
	Tree(){root_=nullptr;}
	void insertRecursive(const T& data){
		insert(root_,data);
	}

	void insert(const T& data){
		if(root_==nullptr){
			root_=new Node<T>(data);
		}
		else{
			Node<T>* curr=root_;
			while(curr){
				if(data < curr->data_){
					if(curr->left_==nullptr){
						curr->left_=new Node<T>(data);
						curr=nullptr;
					}
					else{
						curr=curr->left_;	
					}
				}
				else{
					if(curr->right_==nullptr){
						curr->right_=new Node<T>(data);
						curr=nullptr;
					}
					else{
						curr=curr->right_;
					}
				}
			}

		}
	}

	Node<T>* searchRecursive(const T& data){
		return search(root_,data);
	}

	Node<T>* search(const T& data){
		Node<T>* curr=root_;
		while(curr && curr->data_ != data){
			if(data < curr->data_){
				curr=curr->left_;
			}
			else{
				curr=curr->right_;
			}
		}
		return curr;
	}
	void remove(const T& data){

	}

	void inorderPrint() const{
		inorderPrint(root_);
	}
	void breadthFirstPrint() const{
		Queue<Node<T>*> q;
		Node<T>* curr;
		if(root_){
			q.enqueue(root_);
			while(!q.isEmpty()){
				curr=q.front();
				q.dequeue();
				if(curr->left_)	
					q.enqueue(curr->left_);
				if(curr->right_)
					q.enqueue(curr->right_);
				cout << curr->data_ << " ";
			}
		}
	}
	void remove(const T& data){
		
	}
};