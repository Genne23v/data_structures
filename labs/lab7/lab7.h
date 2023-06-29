#include <iostream>
#include <iomanip>

/*forward declaration*/
template <class T>
class Queue;

template <class T>
class BST
{
    struct Node
    {
        T data_;
        Node *left_;
        Node *right_;
        Node(const T &data, Node *lt = nullptr, Node *rt = nullptr)
        {
            data_ = data;
            left_ = lt;
            right_ = rt;
        }
    };
    Node *root_;

    void printPreOrder(Node *subroot) const
    {
        if (subroot)
        {
            std::cout << subroot->data_ << " ";
            printPreOrder(subroot->left_);
            printPreOrder(subroot->right_);
        }
    }
    void printInOrder(Node *subroot) const
    {
        if (subroot)
        {
            printInOrder(subroot->left_);
            std::cout << subroot->data_ << " ";
            printInOrder(subroot->right_);
        }
    }

    void printBetween(int min, int max){
        printBetween(root_, min, max);
    }
    void printBetween(Node* root, int min, int max){
        if (root_->left_.data_ >= min){
            printBetween(root_->left_);
        }
        if (root_->data_ >= min && root_->data_ <= max){
            std::cout << root_->data_ << std::endl;
        }
        if (root_->right_->data_ <= max){
            printBetween(root_->right_);
        }
    };

    bool removeSmallest(int v){
        bool rc = false;

        if (!root_) {
            return rc;
        } else {
            bool vFound = false;
            Node* curr = root_;
            //Loop until it finds the node that has matching data with v or it gets to leaf node
            while (!vFound && curr){
                if (curr->data_ == v){
                    vFound = true;
                } else if (curr->data_ > v){
                    curr = curr->left_;
                } else {
                    curr = curr->right_;
                }
            }
            //If node is found that has the same data as v 
            if(vFound){
                if (curr->left_){
                    //Find the smallest node from current node
                    //Keep moving to left node
                    Node* parent = nullptr;
                    while (curr->left_){
                        parent = curr;
                        curr = curr->left_;
                    }
                    parent->left_ = nullptr;
                    delete curr;
                    rc = true;  //rc is true only when matching node is found and smallest node in subtree is removed
                } else {
                    //There is no left child from the node found. Does nothing
                }
            } else {
                //Node that has v value not found. Does nothing
            }
        }
        return rc;
    }

    int nodeDifference() const {
        if(!root_){ //If root does not exist, return 0
            return 0;
        } else {    //Get the number of nodes for each left and right subtree by calling countNodes function
            int numLeftNodes = countNodes(root_->left_);
            int numRightNodes = countNodes(root_->right_);
            return numRightNodes - numLeftNodes;    //Return the difference (the number of right tree nodes - the number of left tree nodes)
        }
    }

    int countNodes(Node* subroot) {
        if (!subroot){  //If subroot is nullptr, return 0 immediately 
            return 0;
        } else {    //Count the current node and recursively call countNodes for both side nodes
            return 1 + countNodes(subroot->left_) + countNodes(subroot->right_);
        }
    }

    void destroy(Node *subroot)
    {
        if (subroot)
        {
            destroy(subroot->left_);
            destroy(subroot->right_);
            delete subroot;
        }
    }

    bool isSame(const Node *left, const Node *right) const;

    /*used by print() to print all nodes at same level*/
    void printLine(Node *data[], int numNodes, int width) const
    {
        int half = width / 2;
        int firsthalf = width % 2 ? half + 1 : half;

        if (numNodes > 1)
        {
            for (int i = 0; i < numNodes; i++)
            {
                if (i % 2 == 0)
                {
                    if (data[i])
                    {
                        std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << "-";
                        std::cout << std::left << std::setfill('-') << std::setw(half) << "-";
                    }
                    else
                    {
                        std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << " ";
                        std::cout << std::left << std::setfill(' ') << std::setw(half) << " ";
                    }
                }
                else
                {
                    if (data[i])
                    {
                        std::cout << std::right << std::setfill('-') << std::setw(firsthalf) << "-";
                        std::cout << std::left << std::setfill(' ') << std::setw(half) << "-";
                    }
                    else
                    {
                        std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << " ";
                        std::cout << std::left << std::setfill(' ') << std::setw(half) << " ";
                    }
                }
            }
            std::cout << std::endl;
        }
        for (int i = 0; i < numNodes; i++)
        {
            if (data[i])
            {
                if (i % 2 == 0)
                {
                    std::cout << std::right << std::setw(firsthalf) << "|";
                    std::cout << std::left << std::setfill(' ') << std::setw(half) << " ";
                }
                else
                {
                    std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << " ";
                    std::cout << std::left << std::setfill(' ') << std::setw(half) << "|";
                }
            }
            else
            {
                std::cout << std::left << std::setfill(' ') << std::setw(width) << " ";
            }
        }
        std::cout << std::endl;
        for (int i = 0; i < numNodes; i++)
        {
            if (data[i])
            {
                if (i % 2 == 0)
                {
                    std::cout << std::right << std::setw(firsthalf) << data[i]->data_;
                    std::cout << std::left << std::setfill(' ') << std::setw(half) << " ";
                }
                else
                {
                    std::cout << std::right << std::setfill(' ') << std::setw(firsthalf) << " ";
                    std::cout << std::left << std::setfill(' ') << std::setw(half) << data[i]->data_;
                }
            }
            else
            {
                std::cout << std::left << std::setfill(' ') << std::setw(width) << " ";
            }
        }
        std::cout << std::endl;
    }

public:
    BST()
    {
        root_ = nullptr;
    }

    /* Lab 7: Implement these 3 functions. */
    BST(const BST &rhs)
    {
        Queue<Node*> nodes;
        
        if (rhs.root_){
            nodes.enqueue(rhs.root_);
        }
        
        while(!nodes.isEmpty()){
            Node* curr = nodes.front();
            this->insert(curr->data_);
            nodes.dequeue();
            if (curr->left_){
                nodes.enqueue(curr->left_);
            }
            if (curr->right_){
                nodes.enqueue(curr->right_);
            }
        }
    }
    
    void remove(const T &data)
    {
        root_ = removeNode(root_, data);
    }
    
    Node* removeNode(Node* root, T data){
        Node* temp = nullptr;
        if (root){
            if (root->data_ == data){
                if (root->left_ == nullptr && root->right_ == nullptr){
                    delete root;
                    return nullptr;
                }else {
                    if (root->left_ == nullptr){
                        temp = root->right_;
                        temp->data_ = root->right_->data_;
                        delete root;
                        return temp;
                    }
                    if (root->right_ == nullptr){
                        temp = root->left_;
                        temp->data_ = root->left_->data_;
                        delete root;
                        return temp;
                    }
                    temp = root->right_;
                    while(temp->left_ != nullptr){
                        temp = temp->left_;
                    }
                    root->data_ = temp->data_;
                    root->right_ = removeNode(root->right_, temp->data_);
                }
            } else {
                if (root->data_ > data){
                    root->left_ = removeNode(root->left_, data);
                } else {
                    root->right_ = removeNode(root->right_, data);
                }
            }
        }
        return root;
    }

    int depth(const T &data)
    {
        int depth = -1;
        Node *curr = root_;
        bool found = false;
        while (curr != nullptr && !found)
        {
            if (data < curr->data_)
            {
                 if (curr->left_)
                 {
                     curr = curr->left_;
                 }
                 else
                 {
                     curr = nullptr;
                 }
            }
            else if (data > curr->data_)
            {
                 if (curr->right_)
                 {
                     curr = curr->right_;
                 }
                 else
                 {
                     curr = nullptr;
                 }
            } else {
                found = true;
            }
            depth++;
        }
        
        if (!found){
            depth = -1;
        }
        return depth;
    }

    void printPreOrder() const
    {
        printPreOrder(root_);
        std::cout << std::endl;
    }
    void printInOrder() const
    {
        printInOrder(root_);
        std::cout << std::endl;
    }
    

    void insert(const T &data)
    {
        if (root_ == nullptr)
        {
            root_ = new Node(data);
        }
        else
        {

            Node *curr = root_;
            while (curr != nullptr)
            {
                if (data < curr->data_)
                {
                    // go left
                    if (curr->left_)
                    {
                        curr = curr->left_;
                    }
                    else
                    {
                        curr->left_ = new Node(data);
                        curr = nullptr;
                    }
                }
                else
                {
                    // go right
                    if (curr->right_)
                    {
                        curr = curr->right_;
                    }
                    else
                    {
                        curr->right_ = new Node(data);
                        curr = nullptr;
                    }
                }
            }
        }
    }

    bool operator==(const BST &rhs) const;
    void print() const
    {
        struct Output
        {
            Node *node_;
            int lvl_;
            int position_;
            Output(Node *n = nullptr, int l = 0, int p = 0)
            {
                node_ = n;
                lvl_ = l;
                position_ = p;
            }
            void set(Node *n = nullptr, int l = 0, int p = 0)
            {
                node_ = n;
                lvl_ = l;
                position_ = p;
            }
        };
        Queue<Output> theNodes;
        Node *line[16];
        if (root_)
        {
            for (int i = 0; i < 16; i++)
            {
                line[i] = nullptr;
            }
            theNodes.enqueue(Output(root_, 0, 0));
            int currline = 0;
            int width = 80;
            int numInLine = 1;
            while (theNodes.isEmpty() == false)
            {
                Output curr = theNodes.front();
                if (curr.node_->left_)
                    theNodes.enqueue(Output(curr.node_->left_, curr.lvl_ + 1, curr.position_ * 2));
                if (curr.node_->right_)
                    theNodes.enqueue(Output(curr.node_->right_, curr.lvl_ + 1, curr.position_ * 2 + 1));
                theNodes.dequeue();

                if (curr.lvl_ > currline)
                {
                    printLine(line, numInLine, width);
                    width = width / 2;
                    numInLine = numInLine * 2;
                    for (int i = 0; i < 16; i++)
                    {
                        line[i] = nullptr;
                    }
                    currline++;
                }
                line[curr.position_] = curr.node_;
            }
            printLine(line, numInLine, width);
            std::cout << std::endl;
        }
        else
        {
            std::cout << "tree is empty" << std::endl;
        }
    }
    ~BST()
    {
        destroy(root_);
    }
};

template <class T>
class Queue
{
    T *theQueue_;
    int capacity_;
    int used_;
    int front_;
    int back_;
    void grow()
    {
        T *tmp = new T[capacity_ * 2];
        int j;
        for (int i = 0, j = front_; i < used_; i++, j = (j + 1) % capacity_)
        {
            tmp[i] = theQueue_[j];
        }
        delete[] theQueue_;
        theQueue_ = tmp;
        capacity_ = capacity_ * 2;
        front_ = 0;
        back_ = used_;
    }

public:
    Queue()
    {
        theQueue_ = new T[50];
        capacity_ = 50;
        used_ = 0;
        front_ = 0;
        back_ = 0;
    }
    void enqueue(const T &data)
    {
        if (used_ == capacity_)
        {
            grow();
        }
        theQueue_[back_] = data;
        back_ = (back_ + 1) % capacity_;
        used_++;
    }
    void dequeue()
    {
        if (!isEmpty())
        {
            used_--;
            front_ = (front_ + 1) % capacity_;
        }
    }
    T front() const
    {
        if (!isEmpty())
        {
            return theQueue_[front_];
        }
        return T{};
    }
    bool isEmpty() const
    {
        return used_ == 0;
    }
    ~Queue()
    {
        delete[] theQueue_;
    }
};


