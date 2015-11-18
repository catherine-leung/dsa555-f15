template <class T>	
struct Node{
	T data_;
	Node* left_;  //pointer to left child
	Node* right_; //pointer to right child
	Node(const T& data=T{}, Node* left=nullptr, Node* right=nullptr){
		data_=data;
		left_=left;
		right_=right;
	}
};
template <class T>
class Tree{

	Node* root_;
public:
	Tree(){root_=nullptr;}
	void insertRecursive(const T& data){
		insert(root_,data);
	}
	void insert(const T& data){
		if(root_==nullptr){
			root_=new Node(data);
		}
		else{
			Node* curr=root_;
			while(curr){
				if(data < curr->data_){
					
					if(curr->left_==nullptr){
						curr->left_=new Node(data);
						curr=nullptr;
					}
					else{
						curr=curr->left_;	
					}
				}
				else{
					if(curr->right_==nullptr){
						curr->right_=new Node(data);
						curr=nullptr;
					}
					else{
						curr=curr->right_;
					}
				}
			}

		}
	}
	Node* search(const T& data){

	}
	void remove(const T& data){

	}
	void print() const{

	}
	void insert(rt,data){

	}
};