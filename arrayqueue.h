
template<class T>
class Queue{
	T* data_;
	int maxSize_;
	int currSize_;
	int front_;
	int back_;
	void grow(){
		T* tmp=new T[maxSize_*2];
		for(int i=0;i<currSize_;i++){
			tmp[i]=front();
			dequeue();
		}
		delete data_;
		data_=tmp;
		maxSize_=maxSize_*2;
		front_=0;
		back_=currSize_;
	}
public:
	Queue(int max=100){
		data_=new T[max];
		maxSize_=max;
		currSize_=0;
		front_=0;
		back_=0;
	}
	void enqueue(const T& dat){
		if(currSize_ == maxSize_){
			grow();
		}
		data_[back_]=dat;		
		currSize_++;
		back_=(back_+1)%maxSize_;
	}
	void dequeue(){
		if(currSize_){
			front_=(front_+1)%maxSize_;
			currSize_--;
		}
	}
	const T& front(){
		return data_[front_];
	}
	bool isEmpty() const{
		return currSize_==0;
	}
};