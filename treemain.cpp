#include "tree.h"
#include <iostream>
using namespace std;
int main(void){
	Tree<int> myTree;
	myTree.insert(5);
	myTree.insert(3);
	myTree.insert(10);
	myTree.insert(1);
	myTree.insert(2);
	myTree.insert(4);
	myTree.insert(7);
	myTree.insert(6);
	myTree.insert(9);
	myTree.insert(20);
	myTree.inorderPrint();
	cout << endl;
	myTree.breadthFirstPrint();
	cout << endl;
	myTree.remove(5);
	cout  << " remove 5"  << endl;
	myTree.inorderPrint();
	cout << endl;
	myTree.breadthFirstPrint();
	cout << endl;
	cout  << " remove 3"  << endl;
	myTree.remove(3);
	myTree.inorderPrint();
	cout << endl;
	myTree.breadthFirstPrint();
	cout << endl;
}