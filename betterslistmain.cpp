#include "slist.h"
#include <iostream>
using namespace std;

int main(void){
	SList<int> list;
	SList<int>::const_iterator i;
	list.insert(5);
	list.insert(6);
	list.insert(1);
	list.insert(2);
//	list.append(10);
//	list.rmFirst();
//	list.rmLast();
	for(i=list.begin();i!=list.end();i++){
		cout << *i << endl;
	}
}