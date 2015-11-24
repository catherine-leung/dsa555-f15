#include "threadedtree.h"
#include <iostream>
using namespace std;

int main(void){
	ThreadedTree<int> tree;
	int values [9]={20,30,10,15,5,25,27,18,16};

	for(int i=0;i<2;i++){
		tree.insert(values[i]);
		cout << "***" << endl;
		// next line only prints if you implement the recursive print() function
		// you don't have to, but it might be useful
		tree.print();
	}
	
	for(auto i=tree.begin();i!=tree.end();i++){
		cout << *i << endl;
	}

	return 0;
}