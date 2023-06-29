/********************************************************************/
/*                                                                  */
/*  A1 Part 2: DList starter file                                   */
/*                                                                  */
/*  Author1 Name: Wonkeun No                                        */
/*      - class/function list/main author or main checker           */
/*                                                                  */
/********************************************************************/
#include <utility>
#include <iostream>
template <typename T>

class DList{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data=T{}, Node* next=nullptr, Node* prev=nullptr){
			data_ = data;
			next_ = next;
			prev_ = prev;
		}
	};
	Node* front_;
	Node* back_;

public:
	class const_iterator{
		friend class DList;
	protected: 
		const DList* dList_;
		Node* curr_;
		const_iterator(Node* n, const DList* list){
			curr_ = n;
			dList_ = list;
		}
	public:
		const_iterator(){
			curr_ = nullptr;
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
		iterator():const_iterator(){}
		iterator& operator++(){
			this->curr_ = this->curr_->next_;	//invalid read of size 8
			return *this;
		}
		iterator operator++(int){
			iterator old = *this;
			if (this->curr_ != nullptr){
				this->curr_ = this->curr_->next_;
			}
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
			const T data = this->curr_->data_;
			return data;
		}
	};
	DList();
	~DList();
	DList(const DList& rhs);
	DList& operator=(const DList& rhs);
	DList(DList&& rhs) noexcept;
	DList& operator=(DList&& rhs) noexcept;
	iterator insert(iterator it, const T& data);
	iterator search(const T& data);
	iterator erase(iterator it);
	void sort(iterator first, iterator last);
	bool empty() const;
	int size() const;

	iterator begin(){
		return iterator(front_, this);
	}
	iterator end(){
		return iterator(nullptr, this);
	}
	const_iterator cbegin() const{
		return const_iterator(front_, this);
	}
	const_iterator cend() const{
		return const_iterator(nullptr, this);
	}
};

template <typename T>
DList<T>::DList(){
	front_ = nullptr;
	back_ = nullptr;
}
template <typename T>
DList<T>::~DList(){
	Node* rm_node = front_;
	Node* next_node = nullptr;

	while(rm_node != nullptr){
		next_node = rm_node->next_;
        
		if (next_node != nullptr){
			front_ = next_node;
			next_node->prev_ = nullptr;
			rm_node->next_ = nullptr;
		}
		delete rm_node;
		rm_node = next_node;
	}
	front_ = nullptr;
	back_ = nullptr;
}
template <typename T>
DList<T>::DList(const DList& rhs){
	const_iterator it;
    Node* prev_node;
    
    for(it=rhs.cbegin(); it!=rhs.cend(); it++){
        Node* new_node = new Node(it.curr_->data_, nullptr, nullptr);
        if (it.curr_ == rhs.front_){
            this->front_ = new_node;
            prev_node = new_node;
        } else if (it.curr_ == rhs.back_){
            this->back_ = new_node;
            new_node->prev_ = prev_node;
            prev_node->next_ = new_node;
        } else {
            new_node->prev_ = prev_node;;
            prev_node->next_ = new_node;
            prev_node = new_node;
        }
    }
}
template <typename T>
DList<T>& DList<T>::operator=(const DList& rhs){
	if (this != &rhs){
		iterator it; 
		Node* rm_node = front_;
		Node* next_node;

		while(rm_node != nullptr){
            next_node = rm_node->next_;
            front_ = next_node;
            
            if (next_node != nullptr){
                next_node->prev_ = nullptr;
            }
            
            delete rm_node;
            rm_node = next_node;
        }
        back_ = nullptr;

		const_iterator cit = rhs.cbegin();
		while(cit!=rhs.cend()){
			this->insert(this->end(), cit.curr_->data_);
			++cit;
		}
	}
	return *this;
}
template <typename T>
DList<T>::DList(DList&& rhs) noexcept {
	if (this != &rhs){
		front_ = std::move(rhs.front_);
		back_ = std::move(rhs.back_);
		rhs.front_ = nullptr;
		rhs.back_ = nullptr;
	}
}

template <typename T>
DList<T>& DList<T>::operator=(DList&& rhs) noexcept {
	if (this != &rhs){
		Node* rm_node = front_;
		Node* next_node = nullptr;

		while(rm_node != nullptr){
			next_node = rm_node->next_;
			
			if (next_node != nullptr){
				front_ = next_node;
				next_node->prev_ = nullptr;
				rm_node->next_ = nullptr;
			}

			delete rm_node;
			rm_node = next_node;
		}
		front_ = std::move(rhs.front_);
		back_ = std::move(rhs.back_);
		rhs.front_ = nullptr;
		rhs.back_ = nullptr;
	}
	return *this;
}


template <typename T>
typename DList<T>::iterator DList<T>::insert(iterator it, const T& data){
	Node* new_node = new Node(data, nullptr, nullptr);

	if (this->empty()){
		front_ = new_node;
		back_ = new_node;
	} else {
		Node* prev_node;
		Node* temp_node;
		temp_node = front_;
		iterator temp = this->begin();
		
		while (temp != it){
			++temp;
			prev_node = temp_node;
			temp_node = temp_node->next_;
		}

		if (temp_node == nullptr){
			back_ = new_node;
			new_node->prev_ = prev_node;
			prev_node->next_ = new_node;
		} else if (temp_node == front_){
			new_node->next_ = temp_node;
			temp_node->prev_ = new_node;
			front_ = new_node;
		} else {
			temp_node->prev_ = new_node;
			new_node->next_ = temp_node;
			prev_node->next_ = new_node;
			new_node->prev_ = prev_node;
		}
	}
	return --it;
}
//search function takes any types of data that is comparable. 
//It will iterate through linked list to see whether same data exists in the list. 
//It will return an iterator after the node matching with the data. If not found, it will return nullptr.
template <typename T>
typename DList<T>::iterator DList<T>::search(const T& data){
	iterator it = this->begin();

	while(it != this->end() && *it != data){
		++it;
	}
	return it;
}

//erase function will take an iterator to find a node right before the passed iterator is pointing to. 
//It will remove the node and return an iterator that is pointing to next node of removed node. 
template <typename T>
typename DList<T>::iterator DList<T>::erase(iterator it){
	iterator temp;
    if (!this->empty()){
        Node* rm_node;
        Node* prev_node;
        temp = this->begin();
        rm_node = front_;

        while(temp != it){
            ++temp;
            prev_node = rm_node;
            rm_node = rm_node->next_;
        }

        if (rm_node == front_){
            front_ = rm_node->next_;
            ++it;
            if (rm_node->next_ != nullptr){
                rm_node->next_->prev_ = nullptr;
                rm_node->next_ = nullptr;
            }
        } else if (rm_node->next_ == nullptr){
            back_ = prev_node;
            ++it;
            rm_node->prev_ = nullptr;
            prev_node->next_ = nullptr;
        } else {
            prev_node->next_ = rm_node->next_;
            prev_node->next_->prev_ = prev_node;
            ++it;
            rm_node->prev_ = nullptr;
            rm_node->next_ = nullptr;
        }
        delete rm_node;
    }
    return it;
}

//sort function receives two iterators which is a range that will be sorted. 
//This function uses selection sort algorithm. 
//It does not return anything.
template <typename T>
void DList<T>::sort(iterator first, iterator last){
	Node* min_node;
    iterator it1, it2;
    int offset = 0;
    
    it1 = this->begin();
    while(it1 != first){
        offset++;
        ++it1;
    }
    int loop = offset;
    
    for (it1=first; it1!=last; ++it1){
        min_node = it1.curr_;
        loop++;
        for (it2=it1; it2!=last; ++it2){
            if (it2.curr_->data_.count_ < min_node->data_.count_){
                min_node = it2.curr_;
            }
        }
        
        Node* left = it1.curr_;
        
        if (min_node != it1.curr_){
            if (left == front_){
                front_ = min_node;
            }
            if (min_node == back_){
                back_ = left;
            }
            
            Node* tmp = left->next_;
            left->next_ = min_node->next_;
            min_node->next_ = tmp;
            
            if (left->next_ != nullptr){
                left->next_->prev_ = left;
            }
            if (min_node->next_ != nullptr){
                min_node->next_->prev_ = min_node;
            }
            
            tmp = left->prev_;
            left->prev_ = min_node->prev_;
            min_node->prev_ = tmp;
            
            if (left->prev_ != nullptr){
                left->prev_->next_ = left;
            }
            if (min_node->prev_ != nullptr){
                min_node->prev_->next_ = min_node;
            }
        }
        
        it1 = this->begin();
        for (int i=0; i<loop-1; i++){
            ++it1;
        }
    }
}

//empty function has no parameter. 
//It returns true if the linked list does not have any node. 
//Otherwise it returns false.
template <typename T>
bool DList<T>::empty() const{
	return (front_ == nullptr && back_ == nullptr);
}

//size function has no parameter. 
//It traverses all nodes in the linked list and returns the number of nodes inside as an integer value. 
template <typename T>
int DList<T>::size() const{
	int size = 0;
	const_iterator it = this->cbegin();
	while(it != this->cend()){
		++it;
		++size;
	}
	return size;
}
