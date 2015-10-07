#include "sortedlist.h"
#include <cstring>
#include <iostream>
using namespace std;
struct Record{
	char word_[100];
	int count_;

};
ostream& operator<<(ostream& os, const Record rec){
	os << rec.word_;
	return os;
}
bool operator<(const Record& a,const Record& b){
	bool rc=false;
	if(strcmp(a.word_,b.word_)<0)
		rc=true;
	return rc;
}
bool operator==(const Record& a,const Record& b){
	bool rc=false;
	if(strcmp(a.word_,b.word_)==0)
		rc=true;
	return rc;
}

int main(void){
	Record data[5]={
		{"dog",5},
		{"cat",4},
		{"mouse",3},
		{"hamster",2},
		{"rat",1}
	};
	Record check[5];
	SortedList<Record> list;
	for(int i=0;i<5;i++){
	 	list.insert(data[i]);
	}
	int i=0;
	for(SortedList<Record>::const_iterator ptr=list.begin();ptr != list.end(); ptr++){
	 	cout << *ptr << " ";
	}
	cout << endl;

}