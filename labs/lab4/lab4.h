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
	~DList();

	class const_iterator{
		friend class DList;
	protected:
		const DList* dList_;
		Node* curr_;
		const_iterator(Node* n, const DList* list){
			curr_=n;
			dList_ = list;
		}
	public:
		const_iterator(){
			curr_=nullptr;
			dList_ = nullptr;
		}

		const_iterator& operator++(){
			curr_ = curr_->next_;
			return *this;
		}

		const_iterator operator++(int){
			const_iterator old = *this;
			curr_ = curr_->next_;
			return old;
		}

		const_iterator& operator--(){
			if (curr_){
				curr_ = curr_->prev_;
			} else {
				if (dList_){
					curr_ = dList_->back_;
				}
			}
			return *this;
		}

		const_iterator operator--(int){
			const_iterator old = *this;
			if (curr_){
				curr_ = curr_->prev_;
			} else {
				if (dList_){
					curr_ = dList_->back_;
				}
			}
			return old;
		}

		bool operator==(const_iterator rhs){
			return (dList_ == rhs.dList_ && curr_ == rhs.curr_);
		}

		bool operator!=(const_iterator rhs){
			return !(*this == rhs);
		}

		const T& operator*()const{
			return curr_->data_;
		}
	};

	class iterator:public const_iterator{
		friend class DList;
		iterator(Node* curr, DList* list):const_iterator(curr, list){}
	public:
		iterator():const_iterator(){};
		iterator& operator++(){
			this->curr_ = this->curr_->next_;
			return *this;
		}
		
		iterator operator++(int){
			iterator old = *this;
			this->curr_ = this->curr_->next_;
			return old;
		}

		iterator& operator--(){
			if (this->curr_){
				this->curr_ = this->curr_->prev_;
			} else {
				if (this->dList_){
					this->curr_ = this->dList_->back_;
				}
			}
			return *this;
		}

		iterator operator--(int){
			iterator old = *this;

			if (this->curr_){
				this->curr_ = this->curr_->prev_;
			} else {
				if (this->dList_){
					this->curr_ = this->dList_->back_;
				}
			}
			return old;
		}
		
		T& operator*(){
			return this->curr_->data_;
		}

		const T& operator*()const{
			return this->curr_->data_;	//TO BE MODIFIED
		}

	};

	const_iterator cbegin() const{	
		return const_iterator(front_, this);
	}

	iterator begin(){
		return iterator(front_, this);
	}

	const_iterator cend() const{
		return const_iterator(nullptr, this);
	}

	iterator end(){
		return iterator(nullptr, this);
	}
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
	~Sentinel();

	class const_iterator{
		friend class Sentinel;
	protected:
		const Sentinel* sList_;
		Node* curr_;
		const_iterator(Node* n, const Sentinel* list){
			curr_ = n;
			sList_ = list;
		}
	public:
		const_iterator(){
			curr_ = nullptr;
			sList_ = nullptr;
		}

		const_iterator& operator++(){
			curr_ = curr_->next_;
			return *this;
		}
		
		const_iterator operator++(int){
			const_iterator old = *this;
			curr_ = curr_->next_;
			return old;
		}

		const_iterator& operator--(){
			if (curr_){
				curr_ = curr_->prev_;
				// std::cout << "Prefix --" << curr_->data_ << std::endl;
			} else {
				if (sList_){
					curr_ = sList_->back_->prev_;
				}
			}
			return *this;
		}

		const_iterator operator--(int){
			const_iterator old = *this;

			if (curr_){
				curr_ = curr_->prev_;
			} else {
				if (sList_){
					curr_ = sList_->back_->prev_;
				}
			}
			return old;
		}

		bool operator==(const_iterator rhs){
			return sList_ == rhs.sList_ && curr_ == rhs.curr_;
		}

		bool operator!=(const_iterator rhs){
			return !(*this == rhs);
		}

		const T& operator*()const{
			// std::cout << "Dereferencing data" << curr_->data_ << std::endl;
			return curr_->data_;
		}
	};
	class iterator:public const_iterator{
		friend class Sentinel;
		iterator(Node* curr, Sentinel* list):const_iterator(curr, list){}
	public:
		iterator():const_iterator(){};
		iterator& operator++(){
			this->curr_ = this->curr_->next_;
			return *this;
		}

		iterator operator++(int){
			iterator old = *this;
			this->curr_ = this->curr_->next_;
			return old;
		}

		iterator& operator--(){
			this->curr_ = this->curr_->prev_;
			return *this;
		}

		iterator operator--(int){
			iterator old = *this;
			
			if (this->curr_){
				this->curr_ = this->curr_->prev_;
			} else {
				if (this->sList_){
					this->curr_ = this->sList_->back_->prev_;
				}
			}
			return old;
		}

		T& operator*(){
			// std::cout << "this->curr_->data_: " << this->curr_->data_ << std::endl;
			return this->curr_->data_;
		}

		const T& operator*()const{
			
		}
	};

	const_iterator cbegin() const{
		return const_iterator(front_->next_, this);
	}

	iterator begin(){
		return iterator(front_->next_, this);
	}

	const_iterator cend() const{
		return const_iterator(back_, this);
	}

	iterator end(){
		return iterator(back_, this);
	}
};


template <typename T>
void Sentinel<T>::push_front(const T& data){
	Node* new_node = new Node(data, front_->next_, front_);

	front_->next_->prev_ = new_node;
	front_->next_ = new_node;
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