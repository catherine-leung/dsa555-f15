/*********************************************************/
/*                                                       */
/*   Written by: Catherine Leung                         */
/*   Version 1.0                                         */
/*                                                       */
/*   This program uses a text file with a list of        */
/*   words and creates the tables using the words as     */
/*   keys.                                               */
/*   You will need the file: dictionary.txt (in repo)    */
/*                                                       */
/*   When testing SimpleTable, expect that it will take  */
/*   some time.  The HashTable should be much much       */
/*   faster.  If your hashTable is as slow as            */
/*   SimpleTable,  you probably have a bug in your code. */
/*                                                       */
/*                                                       */
/*   DSA555 - Fall 2015                                */
/*                                                       */
/*   A reminder that all template code must be placed in */
/*   header file. You will have trouble compiling and    */
/*   linking otherwise.                                  */
/*                                                       */
/*   NOTE:  If you find an error, please let me know     */
/*          asap.  I will use this main when I test      */
/*          test so do not make any changes  yourself.   */
/*          Let me know and I'll fix the bug             */
/*                                                       */
/*   To compile this program:                            */
/*          g++ a2main.cpp                               */
/*                                                       */
/*********************************************************/

#include "table.h"
#include <cstring>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
const int NUMTESTS=24;
const int MAX=150000;
const int  NUMOVP= 50000;   //number of words to overpopulate tables with


const char* filename="dictionary.txt";

//A struct to simplify error recording process.
struct Error{
  char msg_[150];
  int passed_;
  Error(const char* msg, int p){
    strcpy(msg_,msg);
    passed_=p;
  }
  void set(const char* msg, int p){
    strcpy(msg_,msg);
    passed_=p;
  }
};


void cleanWordList(char* wordlist[]);
void setData(int data[],int sz);

int main(void){

  FILE* fp=fopen(filename,"r");

  int testnumber=0;
  if(!fp){
    cout << "could not open file" << filename << ".  Make sure it is in the" << endl;
    cout << "same directory as this program and try again" << endl;
    return 0;
  }
  char curr[50];          //used to read in words from text file
  char** wordlist;        //list of test cases. 

  bool oprc;              //return value from an operation

  int reccount;     //the count value in the record.  the ones that were removed and added should 
                    //be 1 the ones that were never removed should be 2
  
  int numremoved=0;   //number of words removed from the table;

  int* data;
  int currValue;

  try{
    data=new int[MAX+NUMOVP];
    wordlist= new char*[MAX+NUMOVP];
    for(int i=0;i<MAX+NUMOVP;i++){
      fscanf(fp,"%s\n",curr);                 //read in a word from data file
      wordlist[i]=new char[strlen(curr)+1];   //record it
      strcpy(wordlist[i],curr);
    }/*end for:  populate table*/
    setData(data,MAX+NUMOVP);
    cout << "* * * * * * * * * * * * Testing Simple Table* * * * * * * * * * * * * * * *"<< endl;
    cout << "Checking table was properly initialized..." << endl;
    int simpleMax=MAX/3;
    SimpleTable<int> simple(simpleMax);
    cout << endl;
    cout << "Populating simple table.  Checking update() functions." << endl;
    for(int i=0;i<simpleMax;i++){

      oprc=simple.update(wordlist[i],data[i]);             
      if(!oprc){                              //check return code (should be true)
        throw Error("simpletable::update is returning false when table is not full",testnumber);
      }
    }/*end for:  populate table*/
    testnumber++;
 


    cout << "Add some more records" << endl;
    for(int i=0;i<NUMOVP;i++){
    
      oprc=simple.update(wordlist[simpleMax+i],data[simpleMax+i]);              
      if(!oprc){                              //check return code (should be false)
        throw Error("SimpleTable::update is returning false.  table should expand with data",testnumber);
      }
    }/*end*/
    testnumber++;
    cout << endl;
    cout << "Checking SimpleTable::find() and that records were properly recorded..." << endl;
    for(int i=0;i<simpleMax+NUMOVP;i++){
      int currValue;
      oprc=simple.find(wordlist[i],currValue);                
      if(!oprc){                                          //check return code (should be true)
        throw Error("simple::find is returning false for a word that should be in the table",testnumber);
      }
      if(currValue!=data[i]){
        cout << "search key:" << wordlist[i] << endl;
        cout << "correct value: "<< data[i] << endl;
        cout << "your record's value: " << currValue << endl;
        throw Error("Simple::find is not passing back the correct data",testnumber);
      }
    }
    testnumber++;
    
    cout << endl;
    cout << "Change some records in Simple table and see if it still works" << endl;
    for(int i=0;i<simpleMax+NUMOVP;i++){
      data[i]+=1;                                              //modify the data (but key is same)
      oprc=simple.update(wordlist[i],data[i]);                          //put it back in the table
      if(!oprc){
        throw Error("Simple::update is returning false for updating an existing record",testnumber);
      }
    }
    testnumber++;
    cout << endl;
    cout << "Checking simple::find() and whether or not records were properly updated..." << endl;
    for(int i=0;i<simpleMax+NUMOVP;i++){
      oprc=simple.find(wordlist[i],currValue);                //search the linear probing table
      if(!oprc){                                          //check return code (should be true)
        throw Error("simple::find is returning false for a word that should be in the table",testnumber);
      }
      if(data[i]!=currValue){
        cout << "search key:" << wordlist[i] << endl;
        cout << "correct value: "<< data[i] << endl;
        cout << "your record's value: " << currValue << endl;
        throw Error("Simple::find is not passing back the correct data",testnumber);
      }
    }
    testnumber++;
    cout << endl;
    cout << "Create a table using copy constructor" << endl;
    SimpleTable<int> simpleCopy=simple;
    cout << "Checking simpleCopy to see whether or not copy was properly made..." << endl;
    for(int i=0;i<simpleMax+NUMOVP;i++){
      oprc=simpleCopy.find(wordlist[i],currValue);                //search the linear probing table
      if(!oprc){                                          //check return code (should be true)
        throw Error("simpleCopy.find is returning false for a word that should be in the table",testnumber);
      }
      if(data[i]!=currValue){
        cout << "search key:" << wordlist[i] << endl;
        cout << "correct value: "<< data[i] << endl;
        cout << "your record's value: " << currValue << endl;
        throw Error("SimpleCopy.find is not passing back the correct data",testnumber);
      }
    }
    testnumber++;
    cout << endl;

    cout << "Remove some records that exist from simple table..." << endl;
    numremoved=0;
    for(int i=0;i<simpleMax+NUMOVP;i+=10){
      oprc=simple.remove(wordlist[i]);                          //put it back in the table
      numremoved++;
      if(!oprc){
        throw Error("simple::remove is returning false for removing an existing record",testnumber);
      }
    }
    testnumber++;
    cout << endl;
    cout << "Check that removed records are gone and other are unaffected in simple table..." << endl;
    for(int i=0;i<simpleMax;i++){
      oprc=simple.find(wordlist[i],currValue);                          //put it back in the table
      if(i%10){
        if(!oprc){
          throw Error("simple::find() could not find record that was not removed",testnumber);
        }
        if(data[i]!=currValue){
        cout << "search key:" << wordlist[i] << endl;
        cout << "correct value: "<< data[i] << endl;
        cout << "your record's value: " << currValue << endl;
        throw Error("Simple::find is not passing back the correct data",testnumber);
        } 
      }
      else{
        if(oprc){
          throw Error("simple::find() found a record that was removed",testnumber);
        }
      }
    }
    testnumber++;
    cout << endl;

    cout << "Checking simpleCopy to see that it was unaffected by removing from simple" << endl;
    for(int i=0;i<simpleMax+NUMOVP;i++){
      oprc=simpleCopy.find(wordlist[i],currValue);                //search the linear probing table
      if(!oprc){                                          //check return code (should be true)
        throw Error("simpleCopy.find is returning false for a word that should be in the table",testnumber);
      }
      if(data[i]!=currValue){
        cout << "search key:" << wordlist[i] << endl;
        cout << "correct value: "<< data[i] << endl;
        cout << "your record's value: " << currValue << endl;
        throw Error("SimpleCopy.find is not passing back the correct data",testnumber);
      }
    }
    testnumber++;
    cout << endl;

    cout << "Use assignment operator to copy simple back into simpleCopy" << endl;
    simpleCopy = simple;


    cout << "Check that assignment operator made proper copy" << endl;
    for(int i=0;i<simpleMax;i++){
      oprc=simpleCopy.find(wordlist[i],currValue);                          //put it back in the table
      if(i%10){
        if(!oprc){
          throw Error("table made with = operator did not find word that should have been in table",testnumber);
        }
        if(data[i]!=currValue){
        cout << "search key:" << wordlist[i] << endl;
        cout << "correct value: "<< data[i] << endl;
        cout << "your record's value: " << currValue << endl;
        throw Error("SimpleCopy.find() is not passing back the correct data",testnumber);
        } 
      }
      else{
        if(oprc){
          throw Error("simplecopy.find() found a record that should not be in table",testnumber);
        }
      }
    }
    testnumber++;
    cout << endl;

    cout << "Add the removed items back to simple table..." << endl;
    for(int i=0;i<simpleMax+NUMOVP;i+=10){
      data[i]-=1;
      oprc=simple.update(wordlist[i],data[i]);          //put it in the chaining table
      if(!oprc){                             //check return code (should be true)
        throw Error("simple::update is returning false when table is not full",testnumber);
      }
    }/*end for*/
    testnumber++;
    cout << endl;


    cout << "Checking that everything in simple was properly updated adding adding removed records back" << endl;
    for(int i=0;i<simpleMax+NUMOVP;i++){
      oprc=simple.find(wordlist[i],currValue);                        
      if(!oprc){
        throw Error("simple::find() could not find record that should be there",testnumber);
      }
      if(data[i]!=currValue){
        cout << "search key:" << wordlist[i] << endl;
        cout << "correct value: "<< data[i] << endl;
        cout << "your record's value: " << currValue << endl;
        throw Error("Simple::find is not passing back the correct data",testnumber);
      } 
    }
    testnumber++;
    cout << endl;
    cout << "* * * * * * * * * * * * Testing HashTable Table* * * * * * * * * * * * * * * *"<< endl;

    cout << "Checking table was properly initialized..." << endl;
    int hashtableMax=MAX;
    bool expandHash=true;
    HashTable<int> hashtable(hashtableMax);
    cout << endl;
    cout << "Populating hashtable table.  Checking update() functions." << endl;
    for(int i=0;i<hashtableMax;i++){

      oprc=hashtable.update(wordlist[i],data[i]);             
      if(!oprc){                              //check return code (should be true)
        throw Error("hashtabletable::update is returning false when table is not full",testnumber);
      }
    }/*end for:  populate table*/
    testnumber++;
    cout << endl;

    cout << "Add some more records (more than expected)" << endl;
    for(int i=0;i<NUMOVP;i++){
    
      oprc=hashtable.update(wordlist[hashtableMax+i],data[hashtableMax+i]);              
      if(!oprc){                              //check return code (should be false)
        expandHash = false;
      }
    }/*end*/
    testnumber++;
    if(expandHash){
      cout << "**HashTable can hold more than maxexpect.** "<< endl;
    }
    int total=expandHash?hashtableMax+NUMOVP:hashtableMax;
    cout << "Checking hashtableTable::find() and that records were properly recorded..." << endl;
    for(int i=0;i<total;i++){
      int currValue;
      oprc=hashtable.find(wordlist[i],currValue);                
      if(!oprc){                                          //check return code (should be true)
        throw Error("hashtable::find is returning false for a word that should be in the table",testnumber);
      }
      if(currValue!=data[i]){
        cout << "search key:" << wordlist[i] << endl;
        cout << "correct value: "<< data[i] << endl;
        cout << "your record's value: " << currValue << endl;
        throw Error("hashtable::find is not passing back the correct data",testnumber);
      }
    }
    testnumber++;
    
    cout << endl;

    cout << "Change some records in hashtable table and see if it still works" << endl;
    for(int i=0;i<total;i++){
      data[i]+=1;                                              //modify the data (but key is same)
      oprc=hashtable.update(wordlist[i],data[i]);                          //put it back in the table
      if(!oprc){
        throw Error("hashtable::update is returning false for updating an existing record",testnumber);
      }
    }
    testnumber++;
    cout << endl;

    cout << "Checking hashtable::find() and whether or not records were properly updated..." << endl;
    for(int i=0;i<total;i++){
      oprc=hashtable.find(wordlist[i],currValue);                //search the linear probing table
      if(!oprc){                                          //check return code (should be true)
        throw Error("hashtable::find is returning false for a word that should be in the table",testnumber);
      }
      if(data[i]!=currValue){
        cout << "search key:" << wordlist[i] << endl;
        cout << "correct value: "<< data[i] << endl;
        cout << "your record's value: " << currValue << endl;
        throw Error("hashtable::find is not passing back the correct data",testnumber);
      }
    }
    testnumber++;
    cout << endl;

    cout << "Create a table using copy constructor" << endl;
    HashTable<int> hashtableCopy=hashtable;
    cout << "Checking hashtableCopy to see whether or not copy was properly made..." << endl;
    for(int i=0;i<total;i++){
      oprc=hashtableCopy.find(wordlist[i],currValue);                //search the linear probing table
      if(!oprc){                                          //check return code (should be true)
        throw Error("hashtableCopy.find is returning false for a word that should be in the table",testnumber);
      }
      if(data[i]!=currValue){
        cout << "search key:" << wordlist[i] << endl;
        cout << "correct value: "<< data[i] << endl;
        cout << "your record's value: " << currValue << endl;
        throw Error("hashtableCopy.find is not passing back the correct data",testnumber);
      }
    }
    testnumber++;
    cout << endl;

    cout << "Remove some records that exist from hashtable table..." << endl;
    numremoved=0;
    for(int i=0;i<total;i+=10){
      oprc=hashtable.remove(wordlist[i]);                          //put it back in the table
      numremoved++;
      if(!oprc){
        throw Error("hashtable::remove is returning false for removing an existing record",testnumber);
      }
    }
    testnumber++;
    cout << endl;
    cout << "Check that removed records are gone and other are unaffected in hashtable table..." << endl;
    for(int i=0;i<hashtableMax;i++){
      oprc=hashtable.find(wordlist[i],currValue);                          //put it back in the table
      if(i%10){
        if(!oprc){
          throw Error("hashtable::find() could not find record that was not removed",testnumber);
        }
        if(data[i]!=currValue){
        cout << "search key:" << wordlist[i] << endl;
        cout << "correct value: "<< data[i] << endl;
        cout << "your record's value: " << currValue << endl;
        throw Error("hashtable::find is not passing back the correct data",testnumber);
        } 
      }
      else{
        if(oprc){
          throw Error("hashtable::find() found a record that was removed",testnumber);
        }
      }
    }
    testnumber++;
    cout << endl;

    cout << "Checking hashtableCopy to see that it was unaffected by removing from hashtable" << endl;
    for(int i=0;i<total;i++){
      oprc=hashtableCopy.find(wordlist[i],currValue);                //search the linear probing table
      if(!oprc){                                          //check return code (should be true)
        throw Error("hashtableCopy.find is returning false for a word that should be in the table",testnumber);
      }
      if(data[i]!=currValue){
        cout << "search key:" << wordlist[i] << endl;
        cout << "correct value: "<< data[i] << endl;
        cout << "your record's value: " << currValue << endl;
        throw Error("hashtableCopy.find is not passing back the correct data",testnumber);
      }
    }
    testnumber++;
    cout << endl;

    cout << "Use assignment operator to copy hashtable back into hashtableCopy" << endl;
    hashtableCopy = hashtable;


    cout << "Check that assignment operator made proper copy" << endl;
    for(int i=0;i<total;i++){
      oprc=hashtableCopy.find(wordlist[i],currValue);                          //put it back in the table
      if(i%10){
        if(!oprc){
          throw Error("table made with = operator did not find word that should have been in table",testnumber);
        }
        if(data[i]!=currValue){
        cout << "search key:" << wordlist[i] << endl;
        cout << "correct value: "<< data[i] << endl;
        cout << "your record's value: " << currValue << endl;
        throw Error("hashtableCopy.find() is not passing back the correct data",testnumber);
        } 
      }
      else{
        if(oprc){
          throw Error("hashtablecopy.find() found a record that should not be in table",testnumber);
        }
      }
    }
    testnumber++;
    cout << endl;

    cout << "Add the removed items back to hashtable table..." << endl;
    for(int i=0;i<total;i+=10){
      data[i]-=1;
      oprc=hashtable.update(wordlist[i],data[i]);          //put it in the chaining table
      if(!oprc){                             //check return code (should be true)
        throw Error("hashtable::update is returning false when table is not full",testnumber);
      }
    }/*end for*/
    testnumber++;
    cout << endl;


    cout << "Checking that everything in hashtable was properly updated adding adding removed records back" << endl;
    for(int i=0;i<total;i++){
      oprc=hashtable.find(wordlist[i],currValue);                        
      if(!oprc){
        throw Error("hashtable::find() could not find record that should be there",testnumber);
      }
      if(data[i]!=currValue){
        cout << "search key:" << wordlist[i] << endl;
        cout << "correct value: "<< data[i] << endl;
        cout << "your record's value: " << currValue << endl;
        throw Error("hashtable::find is not passing back the correct data",testnumber);
      } 
    }
    testnumber++;
 
 
    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"<< endl;

    
    cleanWordList(wordlist);
    cout << endl;
    cout << testnumber << " out of " << NUMTESTS << " tests passed." << endl;
    fclose(fp);
  }
  catch(Error e){
    cout << e.msg_ << endl;
    cout << e.passed_ << " tests of "<< NUMTESTS <<" passed" << endl;
  }
}

void cleanWordList(char* wordlist[]){
  for(int i=0;i<MAX+NUMOVP;i++){
    delete wordlist[i];
  }
}


void setData(int data[],int sz){
  for(int i=0;i<sz;i++){
    data[i]=rand()%10;
  }
}

