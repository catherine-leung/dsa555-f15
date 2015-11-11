
template <class TYPE>
class Table{
public:
	Table(){}
	Table(const Table& other){}
	virtual bool update(const char* key, const TYPE& value)=0;
	virtual bool remove(const char* key)=0;
	virtual bool find(const char* key, TYPE& value)=0;
	virtual const Table& operator=(const Table<TYPE>& other){return *this;}
	virtual ~Table(){}
};

template <class TYPE>
class SimpleTable:public Table<TYPE>{

public:
	SimpleTable(int maxExpected);
	SimpleTable(const SimpleTable& other);
	virtual bool update(const char* key, const TYPE& value);
	virtual bool remove(const char* key);
	virtual bool find(const char* key, TYPE& value);
	virtual const SimpleTable& operator=(const SimpleTable& other);
	virtual ~SimpleTable();
};
/* none of the code in the function definitions below are correct.  You can replace what you need
*/
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int maxExpected): Table<TYPE>(){

}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& other){

}

template <class TYPE>
bool SimpleTable<TYPE>::update(const char* key, const TYPE& value){
	return true;
}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const char* key){
	return true;
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const char* key, TYPE& value){
	return true;
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& other){
	return *this;

}
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable(){

}

template <class TYPE>
class HashTable:public Table<TYPE>{

public:
	HashTable(int maxExpected);
	HashTable(const HashTable& other);
	virtual bool update(const char* key, const TYPE& value);
	virtual bool remove(const char* key);
	virtual bool find(const char* key, TYPE& value);
	virtual const HashTable& operator=(const HashTable& other);
	virtual ~HashTable();
};
/* none of the code in the function definitions below are correct.  You can replace what you need
*/
template <class TYPE>
HashTable<TYPE>::HashTable(int maxExpected): Table<TYPE>(){

}

template <class TYPE>
HashTable<TYPE>::HashTable(const HashTable<TYPE>& other){

}

template <class TYPE>
bool HashTable<TYPE>::update(const char* key, const TYPE& value){
	return true;
}

template <class TYPE>
bool HashTable<TYPE>::remove(const char* key){
	return true;
}

template <class TYPE>
bool HashTable<TYPE>::find(const char* key, TYPE& value){
	return true;
}

template <class TYPE>
const HashTable<TYPE>& HashTable<TYPE>::operator=(const HashTable<TYPE>& other){
	return *this;

}
template <class TYPE>
HashTable<TYPE>::~HashTable(){

}

