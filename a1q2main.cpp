/****************************************/
/*                                      */
/*   This is the official tester for    */
/*   assignment 1 question 2 of         */
/*   DSA555-f15                         */
/*                                      */
/*   Your code must pass all tests      */
/*   on matrix as I will use that for   */
/*   testing                            */
/*                                      */
/*   To compile on matrix:              */
/*   g++ a1q2main.cpp -std=c++0x        */
/*                                      */
/****************************************/
#include "sortedlist.h"
#include <cstring>
#include <iostream>
#include <cstdlib>
using namespace std;
#define VERBOSE 1
const int numSearches=500;

struct Record{
	char word_[30];
	int count_;

};
ostream& operator<<(ostream& os, const Record rec){
	os << rec.word_;
	return os;
}
bool operator<(const Record& lhs, const Record& rhs){
	bool rc=false;
	if(strcmp(lhs.word_,rhs.word_) < 0){
		rc=true;
	}
	return rc;
}
bool operator==(const Record& lhs, const Record& rhs){
	bool rc=false;
	if(strcmp(lhs.word_,rhs.word_)==0){
		rc=true;
	}
	return rc;
}
bool operator!=(const Record& lhs, const Record& rhs){
	bool rc=false;
	if(strcmp(lhs.word_,rhs.word_)!=0){
		rc=true;
	}
	return rc;
}
template <class T>
void mergeArray(T arr[],T tmp[],int startA,int startB,int endB);
template <class T>
void mergeSort(T arr[],T tmp[],int start,int end);
template <class T>
void mergeSort(T arr[],int size);

template <class T>
void removeItem(T arr[],int idx,int sz);
template <class T>
void removeRange(T arr[],int start,int end,int sz);

template <class T>
void printDebug(SortedList<T>& list,T array[],int sz);

template<class T>
bool checkList(SortedList<T>& list, T mirror[],int sz);

template<class T>
bool cmpSortedLists(const SortedList<T>& list1,const SortedList<T>& list2);

int main(void){
	bool passtest=true;
	int numPassed=0;
	int cap = 500;

	SortedList<Record> recList;
	SortedList<int> intList;

	/* Test constructors, begin and end functions*/
	cout << "test 1: create list empty list, check begin() and end()" << endl;
	if((recList.begin() != recList.end()) || 
		(intList.begin() != intList.end())){
		cout << "error 1: check your constructor, begin() and end() functions" << endl;
		passtest=false;
	}

	Record data[20]={
		{"the",1},
		{"quick",2},
		{"brown ",3},
		{"fox",4},
		{"jumped",5},
		{"over",6},
		{"lazy",7},
		{"dog",8},
		{"Calvin",9},
		{"and",10},
		{"Hobbes",11},
		{"night",12},
		{"watch",13},
		{"captain",14},
		{"carrot",15},
		{"lilac",16},
		{"lavender",17},
		{"lily",18},
		{"coffee",19},
		{"tea",20}
	};

	//this array will mirror what happens to LL
	Record mirror[20];

	int intData[cap];
	int intMirror[cap];
	int recCap=20;
	SortedList<Record>::iterator recFrom;
	SortedList<Record>::iterator recTo;
	for(int i=0;i<recCap;i++){
		recList.insert(data[i]);
		mirror[i]=data[i];
	}
	mergeSort(mirror,recCap);

	for(int i=0;i<cap;i++){
		intMirror[i]=intData[i]=rand();
		intList.insert(intData[i]);
	}
	mergeSort(intMirror,cap);

	if(passtest){
		numPassed++;
		cout << "Test 2: Put data into list, check using iterator.  " << endl;
		if(!checkList(recList,mirror,recCap)){
			passtest=false;
			cout << "Error 2a: Bug in either constructor or insert()"<< endl;
			cout << "Bug may also be in const_iterator, operator++(int) or operator*" << endl;
			#if VERBOSE == 1
			printDebug(recList,mirror,recCap);
			#endif
		}
		if(!checkList(intList,intMirror,cap)){
			passtest=false;
			cout << "Error 2b: Bug in either constructor or insert()"<< endl;
			cout << "Bug may also be in const_iterator, operator++(int) or operator*" << endl;
			#if VERBOSE == 1
			printDebug(intList,intMirror,cap);
			#endif
		}
	}
	SortedList<Record> copy=recList;
	SortedList<int> intCopy=intList;

	if(passtest){
		numPassed++;
		cout << "test 3: create a duplicate of the lists, ensure they match" << endl;

		if(!cmpSortedLists(recList,copy)){
			passtest=false;
			cout << "Error 3a: Bug in copy constructor"  << endl;  		
			#if VERBOSE == 1
			printDebug(recList,mirror,recCap);
			#endif
		}
		if(!cmpSortedLists(intList,intCopy)){
			passtest=false;
			cout << "Error 3b: Bug in copy constructor" << endl;
			#if VERBOSE > 1
			printDebug(intList,intMirror,cap);
			#endif
		}
	}
	if(passtest){
		numPassed++;
		cout << "test 4: check that duplicates are deep copies by using iterators" << endl;
		if((copy.begin() == recList.begin()) || (intCopy.begin() == intList.begin())){
			passtest=false;
			cout << "Error 4: list and copy returning identical iterators" << endl;
		}
	}
	if(passtest){
		numPassed++;
		cout << "test 5: remove first item in the list using erase()" << endl;
		recList.erase(recList.begin());
		intList.erase(intList.begin());
		removeItem(mirror,0,recCap);
		removeItem(intMirror,0,cap);
		recCap--;
		cap--;
		if(!checkList(recList,mirror,recCap)){
			passtest=false;
			cout << "Error 5a: Bug in erase()"  << endl;  		
			#if VERBOSE == 1
			printDebug(recList,mirror,recCap);
			#endif
		}
		if(!checkList(intList,intMirror,cap)){
			passtest=false;
			cout << "Error 5b: Bug in erase()" << endl;
			#if VERBOSE > 1
			printDebug(intList,intMirror,cap);
			#endif		
		}
	}
	if(passtest){
		numPassed++;
		cout << "test 6: check that copy was unaffected by erase()" << endl;
		if(checkList(copy,mirror,recCap)){
			passtest=false;
			cout << "Error 6a: copy constructor error"  << endl;  		
			#if VERBOSE == 1
			printDebug(recList,mirror,recCap);
			cout << "note, above should not match as one should have less in array" << endl;
			#endif
		}
		if(checkList(intCopy,intMirror,cap)){
			passtest=false;
			cout << "Error 6b: copy constructor error" << endl;
			#if VERBOSE > 1
			printDebug(intList,intMirror,cap);
			cout << "note, above should not match as one should have less" << endl;
			#endif
		}
	}
	if(passtest){
		numPassed++;
		cout << "test 7: test postfix and prefix ++ Iterators" << endl;
		recFrom = recList.begin();

		//assign original value of recFrom to recTo.  recTo should now point
		//at first node, recFrom to second node.
		recTo=recFrom++;  
		if(recFrom == recTo || (recTo!= recList.begin()) || (recFrom == recList.begin())){
			passtest=false;
			cout << "Error 7a: check your postfix ++ operator"  << endl;
		}
		if(passtest){
			//recFrom points to third node, so does recTo
			recTo = ++recFrom;
			if(recFrom != recTo){
				passtest=false;
				cout << "Error 7a: check your prefix ++ operator"  << endl;
			}
			else{
				//point recTo to fourth node
				recTo++;
				//point recTo to fifth node
				++recTo;
				//point recTo to sixth node
				++recTo;

			}
		}
	}
	if(passtest){
		numPassed++;
		cout << "test 8: test assignment operator" << endl;
		copy = recList;
		intCopy = intList;

		if(!cmpSortedLists(recList,copy)){
			passtest=false;
			cout << "Error 8a: Bug in assignment operator, copy is not the same"  << endl;  		
			#if VERBOSE == 1
			printDebug(recList,mirror,recCap);
			#endif
		}
		if(!cmpSortedLists(intList,intCopy)){
			passtest=false;
			cout << "Error 8b: Bug in assignment operator, copy is not the same" << endl;
			#if VERBOSE > 1
			printDebug(intList,intMirror,cap);
			#endif
		}
	
	}
	if(passtest){
		numPassed++;
		cout << "test 9: to ensure that the lists are deep copies using iterators" << endl;
		if((copy.begin() == recList.begin()) || (intCopy.begin() == intList.begin())){
			passtest=false;
			cout << "Error 9: list and copy returning identical iterators" << endl;
		}
	}
	if(passtest){
		numPassed++;
		cout << "test 10: test erase(from,to) function" << endl;

		recList.erase(recFrom, recTo);
		removeRange(mirror,2,5,recCap);
		recCap-=3;
		if(!checkList(recList,mirror,recCap)){
			passtest=false;
			cout << "Error 10a: values were not erased properly"  << endl;  		
			#if VERBOSE == 1
			printDebug(recList,mirror,recCap);
			#endif			
		}
	}
	if(passtest){
		numPassed++;
		cout << "test 11: test that copy was unaffected" << endl;
		if(checkList(copy,mirror,recCap)){
			passtest=false;
			cout << "Error 11a: assignment operator error"  << endl;  		
			#if VERBOSE == 1
			printDebug(copy,mirror,recCap);
			cout << "note, above should not match" << endl;
			#endif
		}

	}

	if(passtest){
	 	numPassed++;
	 	cout << "test 12: test remove function"  << endl;
		int pickIdx;
		bool rc;
	 	for(int i=0;i<5;i++){
	 		pickIdx=rand()%recCap;
			rc=recList.remove(mirror[pickIdx]);
		 	removeItem(mirror,pickIdx,recCap);
		 	recCap--;
		 	if(!checkList(recList,mirror,recCap)){
		 		passtest=false;
	 			cout << "Error 12a: Bug in remove." << endl;
				#if VERBOSE == 1
				printDebug(recList,mirror,recCap);
				#endif
	 		}
	 	}	
	 	while(passtest && cap){
	 		pickIdx=rand()%cap;
	 		rc=intList.remove(intMirror[pickIdx]);
	 		removeItem(intMirror,pickIdx,cap);
	 		cap--;
	 		if(!checkList(intList,intMirror,cap)){
	 			passtest=false;
	 			cout << "Error 12b: Bug in remove."  << endl;
				#if VERBOSE > 1
				printDebug(intList,intMirror,cap);
				#endif
	 		}
	 	}
	 	if(passtest){
	 		if(intList.begin() != intList.end()){
	 			cout << "Error 12c: Bug in remove, list should be empty but it is not" << endl;
	 		}
	 	}
	}
	if(passtest){
		numPassed++;
	}




 	if(numPassed == 12){
	 	cout << "Testing for Assignment 1 completed successfully" << endl;
	}
	else{
		cout << numPassed << " / 12 tests passed.  Looks like you still" << endl;
		cout << "have some work to do" << endl;
	}
	return 0;
}


template <class T>
void removeItem(T arr[],int idx,int sz){
	for(int i=idx;i<sz-1;i++){
		arr[i]=arr[i+1];
	}
}
template <class T>
void removeRange(T arr[],int start,int end,int sz){
	int range=sz-end;
	for(int i=0;i<range;i++){
		arr[start+i]=arr[end+i];
	}
}

template<class T>
bool checkList(SortedList<T>& list, T mirror[],int sz){
	bool  rc=true;	
	int i=0;
	
	for(auto p=list.begin();rc && p!=list.end();p++){
		if((i == sz) || (*p != mirror[i])){
			rc=false;
		}
		i++;
	}
	if(rc && i!=sz ){
		rc=false;
	}

	return rc;
}

template <class T>
void printDebug(SortedList<T>& list,T array[],int sz){
	int j=0;
	cout << "Your Linked List" << endl;
	for(auto p=list.begin(); p!=list.end();p++){
		cout << *p << endl;
		j++;
	}
	cout << endl;
	cout << "What it should be" << endl;
	for(int i=0;i<sz;i++){
		cout << array[i] << endl;
	}
	cout << endl;
	cout << "Your list has "<< j << " nodes" << endl;
	cout << "It should "<< sz << " nodes" << endl;

}


template <class T>
void mergeSort(T arr[],T tmp[],int start,int end){
  //if the array is more than one element big
	if(start<end){
		int mid=(start+end)/2;
		mergeSort(arr,tmp,start,mid);
		mergeSort(arr,tmp,mid+1,end);
		mergeArray(arr,tmp,start,mid+1,end);
	}
}
/*function merges the two halfs of a sorted array together.
  The arrays are defined from arr[startA]to arr[startB-1] and arr[startB]
to arr[endB]*/

template <class T>
void mergeArray(T arr[],T tmp[],int startA,int startB,int endB){
	int aptr=startA;
	int bptr=startB;
	int idx=startA;
	while(aptr < startB && bptr < endB+1){
		if(arr[aptr] < arr[bptr]){
			tmp[idx++]=arr[aptr];
			aptr++;
		}
		else{
			tmp[idx++]=arr[bptr];
			bptr++;
		}
	}
//merge function only does one of the two following loops
	while(aptr<startB){
		tmp[idx]=arr[aptr];
		idx++;
		aptr++;    
	}
	while(bptr < endB+1){
		tmp[idx++]=arr[bptr];
		bptr++;
	}

//copy back into arr
	for(int i=startA;i<=endB;i++){
		arr[i]=tmp[i];
	}
}

/*this is the wrapper function that "main" uses.  The world see's this and
  use this. The actual work is done by the other MergeSort() function*/
template <class T>
void mergeSort(T arr[],int size){
	T* tmp=new T[size];
	mergeSort(arr,tmp,0,size-1);
	delete [] tmp;
}

template<class T>
bool cmpSortedLists(const SortedList<T>& list1,const SortedList<T>& list2){
	auto p1=list1.begin();
	auto p2=list2.begin();
	bool rc=true;
	while(rc && p1!=list1.end() && p2!=list2.end()){
		if(*p1 != *p2){
			rc=false;
		}
		p1++;
		++p2;
	}
	if(p1!=list1.end() || p2!=list2.end()){
		rc=false;
	}
	return rc;
}


