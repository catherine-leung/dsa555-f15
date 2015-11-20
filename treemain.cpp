#include "tree.h"
#include <iostream>
using namespace std;
int main(void){
	Tree<int> myTree;
	myTree.insert(5);
	myTree.insert(3);
	myTree.insert(6);
	myTree.insert(1);
	myTree.insert(2);
	myTree.insert(4);
	myTree.insert(10);
	myTree.inorderPrint();
	cout << endl;
	myTree.breadthFirstPrint();
	cout << endl;
}