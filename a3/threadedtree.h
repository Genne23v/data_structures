#include <iostream>
using namespace std;

template <class T>
class ThreadedTree
{
    struct Node
    {
        T data_;
        Node *left_;
        Node *right_;
        bool leftThreaded_;
        bool rightThreaded_;
        Node(const T &data = T{}, Node *left = nullptr, Node *right = nullptr)
        {
            data_ = data;
            left_ = left;
            right_ = right;
            leftThreaded_ = false;
            rightThreaded_ = false;
        }
    };
    int size_; // number of nodes in the table
    Node *root_;

public:
    class const_iterator
    {
    protected:
        const ThreadedTree *threadedTree_;
        Node *curr_; // Current node that the const_iterator is pointing
        // const_iterator constructor
        const_iterator(Node *node, const ThreadedTree *threadedTree)
        {
            curr_ = node;
            threadedTree_ = threadedTree;
        }

    public:
        // const_iterator base constructor
        const_iterator()
        {
            curr_ = nullptr;
            threadedTree_ = nullptr;
        }

        // const_iterator operator++(int) moves the iterator to the one greater position but return old iterator.
        const_iterator operator++(int)
        {
            const_iterator old = *this; // Store current position of iterator
            if (curr_)
            {
                if (curr_->rightThreaded_)
                { // If right node is threaded, move to right node
                    curr_ = curr_->right_;
                }
                else
                { // If right node is not threaded, move to right and keep moving to left to find the smallest underneath
                    curr_ = curr_->right_;
                    if (curr_ && curr_->left_)
                    {
                        while (!curr_->leftThreaded_)
                        {
                            curr_ = curr_->left_;
                        }
                    }
                }
            }
            return old; // Return old iterator as previous position of iterator
        }

        // const_iterator operator--(int) moves the iterator to the one smaller position but return old iterator.
        const_iterator operator--(int)
        {
            const_iterator old = *this; // Store current position of iterator
            if (curr_)
            {
                if (curr_->leftThreaded_)
                { // If left node is threaded, move to left node
                    curr_ = curr_->left_;
                    if (curr_ != threadedTree_->root_)
                    { // If current node is not root, move to right most node
                        while (curr_ && curr_->right_ && curr_->rightThreaded_)
                        {
                            curr_ = curr_->right_;
                        }
                    }
                }
                else
                { // If left node is not threaded, move to left and keep moving to right to find the greatest underneath
                    curr_ = curr_->left_;
                    if (curr_ && curr_->right_)
                    {
                        while (!curr_->rightThreaded_)
                        { // Stop moving if right node is threaded
                            curr_ = curr_->right_;
                        }
                    }
                }
            }
            else
            {                                 // This is for the case when iterator is not pointing any node in the tree
                curr_ = threadedTree_->root_; // Store root node in current node
                while (curr_->right_ != nullptr & !curr_->rightThreaded_)
                { // Keep moving to right most node as the last node in the tree
                    curr_ = curr_->right_;
                }
            }
            return old; // Return old iterator as previous position of iterator
        }

        // const_iterator operator++ moves the iterator to the one greater position and return current iterator.
        const_iterator operator++()
        {
            if (curr_)
            {
                if (curr_->rightThreaded_)
                { // If right node is threaded, move to right node
                    curr_ = curr_->right_;
                }
                else
                { // If right node is not threaded, move to right and keep moving to left to find the smallest underneath
                    curr_ = curr_->right_;
                    if (curr_ && curr_->left_)
                    {
                        while (!curr_->leftThreaded_)
                        {
                            curr_ = curr_->left_;
                        }
                    }
                }
            }
            return *this; // Return current iterator
        }

        // const_iterator operator++ moves the iterator to the one smaller position and return current iterator.
        const_iterator operator--()
        {
            if (curr_)
            {
                if (curr_->leftThreaded_)
                { // If left node is threaded, move to left node
                    curr_ = curr_->left_;
                    if (curr_ != threadedTree_->root_)
                    { // If current node is not root, move to right most node
                        while (curr_ && curr_->right_ && curr_->rightThreaded_)
                        {
                            curr_ = curr_->right_;
                        }
                    }
                }
                else
                { // If left node is not threaded, move to left and keep moving to right to find the greatest underneath
                    curr_ = curr_->left_;
                    if (curr_ && curr_->right_)
                    {
                        while (!curr_->rightThreaded_)
                        { // Stop moving if right node is threaded
                            curr_ = curr_->right_;
                        }
                    }
                }
            }
            else
            {                                 // This is for the case when iterator is not pointing any node in the tree
                curr_ = threadedTree_->root_; // Store root node in current node
                while (curr_->right_ != nullptr & !curr_->rightThreaded_)
                { // Keep moving to right most node as the last node in the tree
                    curr_ = curr_->right_;
                }
            }
            return *this; // Return current iterator
        }

        // operator* dereference the current node of data
        const T &operator*() const
        {
            return curr_->data_;
        }

        // operator== compares the current const_iterator with rhs const_iterator
        bool operator==(const const_iterator &rhs) const
        {
            return (threadedTree_ == rhs.threadedTree_ && curr_ == rhs.curr_); // If the current const_iterator is pointing to the same ThreadedTree and node with rhs, return true. Otherwise false
        }

        // operator!= compares current const_iterator with rhs const_iterator are same. If so, it returns true, otherwise false.
        bool operator!=(const const_iterator &rhs) const
        {
            return !(*this == rhs); // If current const_iterator is same as rhs const_iterator, return true. Otherwise false.
        }
        friend class ThreadedTree;
    };
    class iterator : public const_iterator
    {
        friend class ThreadedTree;
        iterator(Node *curr, ThreadedTree *threadedTree) : const_iterator(curr, threadedTree) {}

    public:
        iterator() : const_iterator()
        {
        }

        // operator* return const generic type data
        const T &operator*() const
        {
            const T data = this->curr_->data_; // Store current data in const type
            return data;
        }

        // operator* return generic type data
        T &operator*()
        {
            return this->curr_->data_;
        }

        // iterator operator++(int) moves the iterator to the one greater position but return old iterator.
        iterator operator++(int)
        {
            iterator old = *this; // Store current position of iterator
            if (this->curr_)
            {
                if (this->curr_->rightThreaded_)
                { // If right node is threaded, move to right node
                    this->curr_ = this->curr_->right_;
                }
                else
                { // If right node is not threaded, move to right and keep moving to left to find the smallest underneath
                    this->curr_ = this->curr_->right_;
                    if (this->curr_ && this->curr_->left_)
                    {
                        while (!this->curr_->leftThreaded_)
                        {
                            this->curr_ = this->curr_->left_;
                        }
                    }
                }
            }
            return old; // Return old iterator as previous position of iterator
        }

        // iterator operator--(int) moves the iterator to the one smaller position but return old iterator.
        iterator operator--(int)
        {
            iterator old = *this; // Store current position of iterator
            if (this->curr_)
            {
                if (this->curr_->leftThreaded_)
                { // If left node is threaded, move to left node
                    this->curr_ = this->curr_->left_;
                }
                else
                { // If left node is not threaded, move to left and keep moving to right to find the greatest underneath
                    this->curr_ = this->curr_->left_;
                    if (this->curr_ && this->curr_->right_)
                    {
                        while (!this->curr_->rightThreaded_)
                        { // Stop moving if right node is threaded
                            this->curr_ = this->curr_->right_;
                        }
                    }
                }
            }
            else
            {                                             // This is for the case when iterator is not pointing any node in the tree
                this->curr_ = this->threadedTree_->root_; // Store root node in current node
                while (this->curr_->right_ != nullptr & !this->curr_->rightThreaded_)
                { // Keep moving to right most node as the last node in the tree
                    this->curr_ = this->curr_->right_;
                }
            }
            return old; // Return old iterator as previous position of iterator
        }

        // iterator operator++ moves the iterator to the one greater position and return current iterator.
        iterator operator++()
        {
            if (this->curr_)
            {
                if (this->curr_->rightThreaded_)
                { // If right node is threaded, move to right node
                    this->curr_ = this->curr_->right_;
                }
                else
                { // If right node is not threaded, move to right and keep moving to left to find the smallest underneath
                    this->curr_ = this->curr_->right_;
                    if (this->curr_ && this->curr_->left_)
                    {
                        while (!this->curr_->leftThreaded_)
                        {
                            this->curr_ = this->curr_->left_;
                        }
                    }
                }
            }
            return *this; // Return current iterator
        }

        // iterator operator++ moves the iterator to the one smaller position and return current iterator.
        iterator operator--()
        {
            if (this->curr_)
            {
                if (this->curr_->leftThreaded_)
                { // If left node is threaded, move to left node
                    this->curr_ = this->curr_->left_;
                }
                else
                { // If left node is not threaded, move to left and keep moving to right to find the greatest underneath
                    this->curr_ = this->curr_->left_;
                    if (this->curr_ && this->curr_->right_)
                    {
                        while (!this->curr_->rightThreaded_)
                        { // Stop moving if right node is threaded
                            this->curr_ = this->curr_->right_;
                        }
                    }
                }
            }
            else
            {                                             // This is for the case when iterator is not pointing any node in the tree
                this->curr_ = this->threadedTree_->root_; // Store root node in current node
                while (this->curr_->right_ != nullptr & !this->curr_->rightThreaded_)
                { // Keep moving to right most node as the last node in the tree
                    this->curr_ = this->curr_->right_;
                }
            }
            return *this; // Return current iterator
        }

        friend class ThreadedTree;
    };

    // ThreadedTree default constructor.
    ThreadedTree()
    {
        size_ = 0;       // Initialize size
        root_ = nullptr; // Initialize root pointer
    }

    // insert() takes constant generic type data. It compares the each node data to find the right position to add.
    // It creates new node and increase the size of the table.
    // It does not return anything
    void insert(const T &data)
    {
        if (root_) // If root exists already
        {
            Node *curr = root_;     // Starting from root of the tree
            Node *parent = nullptr; // To store parent node to link

            while (curr != nullptr)
            {                           // Loop until it finds a empty node
                if (data < curr->data_) // If data is less than the current data, check left
                {
                    if (!curr->leftThreaded_ && curr->left_) // Move to left if node exists to left and it is not threaded
                    {
                        curr = curr->left_;
                    }
                    else if (!curr->left_ || curr->leftThreaded_) // If it is empty or a threated node, create a node with the data
                    {
                        parent = curr;                // Store parent node
                        Node *temp = curr->left_;     // Store current left to connect after creation
                        curr->left_ = nullptr;        // Disconnect left node for creation
                        curr->left_ = new Node(data); // Create new node on left
                        if (parent->leftThreaded_)    // If parent node is threaded which is the smallest in right tree
                        {
                            curr->left_->left_ = temp;          // Point left to parent left threaded node
                            curr->left_->right_ = parent;       // Point right to parent
                            curr->left_->rightThreaded_ = true; // Set current right threaded
                            curr->left_->leftThreaded_ = true;  // Set current left-threaded
                            parent->leftThreaded_ = false;      // Reset parent to not left-threaded
                        }
                        else // If parent node is not threaded, point right to parent
                        {
                            curr->left_->right_ = parent;
                            curr->left_->rightThreaded_ = true;
                        }
                        curr = nullptr;
                        size_++;
                    }
                }
                else // If data is greater than the current data, check right
                {
                    if (!curr->rightThreaded_ && curr->right_) // Move to right if node exists to right and it is not threaded
                    {
                        curr = curr->right_;
                    }
                    else if (!curr->right_ || curr->rightThreaded_) // If it is empty or a threated node, create a node with the data
                    {
                        parent = curr;                 // Store curr node as parent
                        Node *temp = curr->right_;     // Store current left to connect after creation
                        curr->right_ = nullptr;        // Disconnect left node for creation
                        curr->right_ = new Node(data); // Create new node on right
                        if (parent->rightThreaded_)    // If parent node is threaded which is the largest in left tree
                        {
                            curr->right_->right_ = temp;         // Point right to parent right threaded node
                            curr->right_->left_ = parent;        // Point left to parent
                            curr->right_->leftThreaded_ = true;  // Set current left threaded
                            curr->right_->rightThreaded_ = true; // Set current right-threaded
                            parent->rightThreaded_ = false;      // Reset parent not right-threaded
                        }
                        else // If parent node is not threaded, point left to parent
                        {
                            curr->right_->left_ = parent;
                            curr->right_->leftThreaded_ = true;
                        }
                        curr = nullptr;
                        size_++;
                    }
                }
            }
        }
        else // If root does not exist, create new node on root
        {
            root_ = new Node(data, nullptr, nullptr);
            size_++;
        }
    }

    // find() takes constant generic type key to find the node matching with passed key.
    // It loops the table to search the key.
    // It returns iterator pointing to matching node. If not found, it returns the end of tree.
    iterator find(const T &key)
    {
        iterator it = this->begin(); // Start with beginning of the tree
        bool found = false;

        while (it != this->end() && !found) // Loop until the end of the tree or matching is found
        {
            if (*it == key)
            {
                found = true;
            }
            else
            {
                ++it;
            }
        }
        return it;
    }

    // find() takes constant generic type key to find the node matching with passed key.
    // It loops the table to search the key.
    // It returns const_iterator pointing to matching node. If not found, it returns the end of tree.
    const_iterator find(const T &key) const
    {
        const_iterator cit = this->cbegin(); // Start with beginning of the tree
        bool found = false;

        while (cit != this->cend() && !found) // Loop until the end of the tree or matching is found
        {
            if (*cit == key)
            {
                found = true;
            }
            else
            {
                ++cit;
            }
        }
        return cit;
    }

    // begin() finds the start of the tree and return the iterator pointing to start
    iterator begin()
    {
        Node *curr = root_;
        Node *prev = nullptr;
        if (root_)
        {
            while (curr != nullptr && !curr->leftThreaded_) // Move left while there is a node on left and it is not threaded
            {
                prev = curr;
                curr = curr->left_;
            }
        }
        return iterator(prev, this); // Create an iterator with the left most node and return it
    }

    // end() finds the end of the tree and return the iterator pointing to end
    iterator end()
    {
        Node *curr = root_;
        if (root_)
        {
            while (curr != nullptr && !curr->rightThreaded_) // Move right while there is a node on right and it is not threaded
            {
                curr = curr->right_;
            }
        }
        return iterator(curr, this); // Create an iterator with the right most node and return it
    }

    // cbegin() finds the start of the tree and return const_iterator pointing to start
    const_iterator cbegin() const
    {
        Node *curr = root_;
        Node *prev = nullptr;
        if (root_)
        {
            while (curr != nullptr && !curr->leftThreaded_) // Move left while there is a node on left and it is not threaded
            {
                prev = curr;
                curr = curr->left_;
            }
        }
        return const_iterator(prev, this); // Create an iterator with the left most node and return it
    }

    // cend() finds the end of the tree and return const_iterator pointing to end
    const_iterator cend() const
    {
        Node *curr = root_;
        if (root_)
        {
            while (curr != nullptr && !curr->rightThreaded_) // Move right while there is a node on right and it is not threaded
            {
                curr = curr->right_;
            }
        }
        return const_iterator(curr, this); // Create an iterator with the right most node and return it
    }

    // size() returns the number of nodes in the tree as an integer
    int size() const
    {
        return size_;
    }

    // empty() returns true if tree does not have any node. If does, it returns false.
    bool empty() const
    {
        return size_ == 0;
    }

    // destroy() calls recursively passing each node left and right node and delete root in each call
    void destroy(Node *root)
    {
        if (root)
        { // If root node exists
            if (!root->leftThreaded_)
            {
                destroy(root->left_); // Recursive call with left node
            }
            if (!root->rightThreaded_)
            {
                destroy(root->right_); // Recursive call with right node
            }
            delete root; // Delete root node
        }
    }

    // ThreadedTree destructor
    ~ThreadedTree()
    {
        destroy(root_);
    }
};
