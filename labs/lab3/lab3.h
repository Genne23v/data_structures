#include <iostream>

template <typename T>
class DList{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data=T{},Node* next=nullptr, Node* prev=nullptr){
			data_=data;
			next_=next;
			prev_=prev;
		}
	};
	Node* front_;
	Node* back_;
public:
	DList(){
		front_=nullptr;
		back_=nullptr;
	}
	void push_front(const T& data);
	void push_back(const T& data);
	void pop_front();
	void pop_back();
	int getData(int data[]) const;
	int getReverseData(int data[]) const;
	~DList();
};


template <typename T>
void DList<T>::push_front(const T& data){
	Node* new_node = new Node(data, nullptr, nullptr);
	
	if (front_){
		new_node->next_ = front_;
		front_->prev_ = new_node;
	} else {
		back_ = new_node;
	}
	front_ = new_node;
}

template <typename T>
void DList<T>::push_back(const T& data){
	Node* new_node = new Node(data, nullptr, nullptr);

	if (back_){
		new_node->prev_ = back_;
		back_->next_ = new_node;
	} else {
		front_ = new_node;
	}
	back_ = new_node;
}

template <typename T>
void DList<T>::pop_front(){
	if (front_){
		Node* rm_node = front_;
		front_ = front_->next_;

		if (front_ == nullptr){
			back_ = nullptr;
		} else {
			front_->prev_ = nullptr;
		}
		delete rm_node;
	}
}

template <typename T>
void DList<T>::pop_back(){
	if (back_){
		Node* rm_node = back_;
		back_ = back_->prev_;

		if (back_ == nullptr){
			front_ = nullptr;
		} else {
			back_->next_ = nullptr;
		}
		delete rm_node;
	}
}
template <typename T>
int DList<T>::getData(int data[]) const{
	Node* curr=front_;
	int numData=0;
	while(curr!=nullptr){
		data[numData++]=curr->data_;
		curr=curr->next_;
	}
	return numData;
}
template <typename T>
int DList<T>::getReverseData(int data[]) const{
	Node* curr=back_;
	int numData=0;
	while(curr!=nullptr){
		data[numData++]=curr->data_;
		curr=curr->prev_;
	}
	return numData;
}
template <typename T>
DList<T>::~DList(){
	Node* rm_node = front_;
	Node* next_node;

	while(rm_node != nullptr){
		next_node = rm_node->next_;
		delete rm_node;
		rm_node = next_node;
	}
	front_ = nullptr;
	back_ = nullptr;
}
template <typename T>
class Sentinel{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data=T{},Node* next=nullptr, Node* prev=nullptr){
			data_=data;
			next_=next;
			prev_=prev;
		}
	};
	Node* front_;
	Node* back_;
public:
	Sentinel(){
		front_=new Node();
		back_=new Node();
		front_->next_=back_;
		back_->prev_=front_;
	}
	void push_front(const T& data);
	void push_back(const T& data);
	void pop_front();
	void pop_back();
	int getData(int data[]) const;
	int getReverseData(int data[]) const;
	~Sentinel();
};


template <typename T>
void Sentinel<T>::push_front(const T& data){
	Node* new_node = new Node(data, front_->next_, front_);

	front_->next_->prev_ = new_node;
	front_->next_ = new_node;
}

template <typename T>
void Sentinel<T>::push_back(const T& data){
	Node* new_node = new Node(data, back_, back_->prev_);

	back_->prev_->next_ = new_node;
	back_->prev_ = new_node;
}

template <typename T>
void Sentinel<T>::pop_front(){
	if (front_->next_ != back_){
		Node* rm_node = front_->next_;
		front_->next_ = rm_node->next_;
		front_->next_->prev_ = front_;
		delete rm_node;
	}
}

template <typename T>
void Sentinel<T>::pop_back(){
	if (front_->next_ != back_){
		Node* rm_node = back_->prev_;
		back_->prev_ = rm_node->prev_;
		back_->prev_->next_ = back_;
		delete rm_node;
	}
}

template <typename T>
int Sentinel<T>::getData(int data[]) const{
	Node* curr=front_->next_;
	int numData=0;
	while(curr!=back_){
		data[numData++]=curr->data_;
		curr=curr->next_;
	}
	return numData;
}

template <typename T>
int Sentinel<T>::getReverseData(int data[]) const{
	Node* curr=back_->prev_;
	int numData=0;
	while(curr!=front_){
		data[numData++]=curr->data_;
		curr=curr->prev_;
	}
	return numData;
}

template <typename T>
Sentinel<T>::~Sentinel(){
	Node* rm_node = front_->next_;
	Node* next_node;

	while(rm_node != nullptr && rm_node != back_){
		next_node = rm_node->next_;
		delete rm_node;
		rm_node = next_node;
	}
	delete front_;
	delete back_;
}
