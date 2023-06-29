/*************************************************************/
/*                                                           */
/*  Starter file for a2                                      */
/*                                                           */
/*  Author1 Name: Wonkeun No                                 */
/*      - class/function list/main author or main checker    */
/*                                                           */
/*************************************************************/

#include <string>
#include <utility>
#include <functional>
#include "mylist.h"
#include <iostream>

template <class TYPE>
class Table
{
public:
    Table() {}
    virtual bool update(const std::string &key, const TYPE &value) = 0;
    virtual bool remove(const std::string &key) = 0;
    virtual bool find(const std::string &key, TYPE &value) = 0;
    virtual int numRecords() const = 0;
    virtual bool isEmpty() const = 0;
    virtual int capacity() const = 0;
    virtual ~Table() {}
};

template <class TYPE>
class SimpleTable : public Table<TYPE>
{
    struct Record
    {
        TYPE data_;
        std::string key_;
        Record(const std::string &key, const TYPE &data)
        {
            key_ = key;
            data_ = data;
        }
    };

    Record **records_; // the table
    int capacity_;     // capacity of the array

public:
    SimpleTable(int capacity);
    SimpleTable(const SimpleTable &rhs);
    SimpleTable(SimpleTable &&rhs);
    virtual bool update(const std::string &key, const TYPE &value);
    virtual bool remove(const std::string &key);
    virtual bool find(const std::string &key, TYPE &value);
    virtual const SimpleTable &operator=(const SimpleTable &rhs);
    virtual const SimpleTable &operator=(SimpleTable &&rhs);
    virtual ~SimpleTable();
    virtual bool isEmpty() const { return numRecords() == 0; }
    virtual int numRecords() const;
    virtual int capacity() const { return capacity_; }
};

template <class TYPE>
int SimpleTable<TYPE>::numRecords() const
{
    int rc = 0;
    for (int i = 0; records_[i] != nullptr; i++)
    {
        rc++;
    }
    return rc;
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int capacity) : Table<TYPE>()
{
    records_ = new Record *[capacity + 1];
    capacity_ = capacity;
    for (int i = 0; i < capacity_ + 1; i++)
    {
        records_[i] = nullptr;
    }
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE> &rhs)
{
    records_ = new Record *[rhs.capacity_ + 1];
    capacity_ = rhs.capacity_;
    for (int i = 0; i < capacity_ + 1; i++)
    {
        records_[i] = nullptr;
    }
    for (int i = 0; i < rhs.numRecords(); i++)
    {
        update(rhs.records_[i]->key_, rhs.records_[i]->data_);
    }
}
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE> &&rhs)
{
    capacity_ = rhs.capacity_;
    records_ = rhs.records_;
    rhs.records_ = nullptr;
    rhs.capacity_ = 0;
}

template <class TYPE>
bool SimpleTable<TYPE>::update(const std::string &key, const TYPE &value)
{
    int idx = -1;
    int sz = numRecords();
    bool rc = true;
    for (int i = 0; i < sz; i++)
    {
        if (records_[i]->key_ == key)
        {
            idx = i;
        }
    }
    if (idx == -1)
    {
        if (sz < capacity_)
        {
            records_[numRecords()] = new Record(key, value);
            for (int i = numRecords() - 1; i > 0 && records_[i]->key_ < records_[i - 1]->key_; i--)
            {
                Record *tmp = records_[i];
                records_[i] = records_[i - 1];
                records_[i - 1] = tmp;
            }
        }
        else
        {
            rc = false;
        }
    }
    else
    {
        records_[idx]->data_ = value;
    }
    return rc;
}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const std::string &key)
{
    int idx = -1;
    for (int i = 0; records_[i] != nullptr; i++)
    {
        if (records_[i]->key_ == key)
        {
            idx = i;
        }
    }
    int size = numRecords();
    if (idx != -1)
    {
        delete records_[idx];

        for (int i = idx; i < numRecords() - 1; i++)
        {
            records_[i] = records_[i + 1];
        }
        records_[size - 1] = nullptr;
        return true;
    }
    else
    {
        return false;
    }
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const std::string &key, TYPE &value)
{
    int idx = -1;
    for (int i = 0; i < numRecords(); i++)
    {
        if (records_[i]->key_ == key)
        {
            idx = i;
        }
    }
    if (idx == -1)
        return false;
    else
    {
        value = records_[idx]->data_;
        return true;
    }
}

template <class TYPE>
const SimpleTable<TYPE> &SimpleTable<TYPE>::operator=(const SimpleTable<TYPE> &rhs)
{
    if (this != &rhs)
    {
        if (records_)
        {
            while (numRecords() != 0)
            {
                remove(records_[0]->key_);
            }
            delete[] records_;
        }
        records_ = new Record *[rhs.capacity_ + 1];
        capacity_ = rhs.capacity_;
        for (int i = 0; i < capacity_; i++)
        {
            records_[i] = nullptr;
        }
        for (int i = 0; i < rhs.numRecords(); i++)
        {
            update(rhs.records_[i]->key_, rhs.records_[i]->data_);
        }
    }
    return *this;
}
template <class TYPE>
const SimpleTable<TYPE> &SimpleTable<TYPE>::operator=(SimpleTable<TYPE> &&rhs)
{
    if (records_)
    {
        while (numRecords() != 0)
        {
            remove(records_[0]->key_);
        }
        delete[] records_;
    }
    records_ = rhs.records_;
    capacity_ = rhs.capacity_;
    rhs.records_ = nullptr;
    rhs.capacity_ = 0;

    return *this;
}
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable()
{
    if (records_)
    {
        int sz = numRecords();
        for (int i = 0; i < sz; i++)
        {
            remove(records_[0]->key_);
        }
        delete[] records_;
    }
}
template <class TYPE>
class ChainingTable : public Table<TYPE>
{
    DList<TYPE> *lists_;
    int capacity_;
    int numRecords_;

public:
    ChainingTable(int maxExpected);
    ChainingTable(const ChainingTable &other);
    ChainingTable(ChainingTable &&other);
    double loadFactor() const;
    virtual bool update(const std::string &key, const TYPE &value);
    virtual bool remove(const std::string &key);
    virtual bool find(const std::string &key, TYPE &value);
    virtual const ChainingTable &operator=(const ChainingTable &other);
    virtual const ChainingTable &operator=(ChainingTable &&other);
    virtual ~ChainingTable();
    virtual bool isEmpty() const;
    virtual int numRecords() const;
    virtual int capacity() const;
};

// Base ChainingTable constructor
// It takes capacity parameter to create an array of DList as many as capacity parameter.
// Each Node in DList will have string key, TYPE value
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(int capacity) : Table<TYPE>()
{
    lists_ = new DList<TYPE>[capacity]; // Create empty resources for the table
    capacity_ = capacity;               // Set capacity of the table
    numRecords_ = 0;                    // Initialize the number of records in the table
}

// ChainingTable copy constructor
// It takes another ChainingTable object to create the same length of array and deep copy the resource
// Each Node in DList will have string key, TYPE value
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(const ChainingTable<TYPE> &other)
{
    capacity_ = other.capacity_;                // Reset capacity of the table
    numRecords_ = other.numRecords_;            // Reset the number of records in the table
    lists_ = new DList<TYPE>[other.capacity()]; // Reset empty resources for the table
    for (int i = 0; i < capacity_; i++)
    {
        lists_[i] = other.lists_[i];
    }
}

// ChainingTable move constructor
// It takes another ChainingTable object to transfer the resources from.
// Each Node in DList will have string key, TYPE value
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(ChainingTable<TYPE> &&other)
{
    lists_ = std::move(other.lists_); // Move resources from moving ChainingTable
    capacity_ = other.capacity_;      // Reset capacity of the table
    numRecords_ = other.numRecords_;  // Reset the number of records in the table
    other.lists_ = nullptr;           // Initialize moving ChainingTable
    other.capacity_ = 0;              // Initialize moving ChainingTable
    other.numRecords_ = 0;            // Initialize moving ChainingTable
}

// update function takes key and value parameters and find if there is a matching key existing in the table.
// key is hashed to find the right DList index to search the matching key.
// If exists, update the value with the passed value in the table.
// If not exists, key-value pair is added to the table.
// If operation is successful, function returns true. Otherwise it returns false.
template <class TYPE>
bool ChainingTable<TYPE>::update(const std::string &key, const TYPE &value)
{
    bool rc = false; // Return boolean value to show operation is successful
    // Hash the key and get the index to search the key
    std::hash<std::string> hashFunction;
    size_t hash = hashFunction(key);
    size_t idx = hash % capacity_;

    // Try is find the matching key. If there is, it updates the passed value and returns the iterator pointing to node.
    typename DList<TYPE>::iterator it = lists_[idx].insert(lists_[idx].end(), key, value);
    // If iterator is not nullptr, operation is successful, increate the number of records and set rc to true. Otherwise set to false.
    if (it != lists_[idx].end())
    {
        rc = true;
        numRecords_++;
    }
    else
    {
        rc = true;
    }
    return rc;
}

// remove function takes key parameter and find if there is a matching key existing in the table.
// key is hashed to find the right DList index to search the matching key.
// If exists, remove the node with matching key return true.
// If not exists, it does nothing and returns false.
template <class TYPE>
bool ChainingTable<TYPE>::remove(const std::string &key)
{
    bool rc = false; // Return boolean value to show operation is successful
    // Hash the key and get the index to search the key
    std::hash<std::string> hashFunction;
    size_t hash = hashFunction(key);
    size_t idx = hash % capacity_;

    // Set the iterator to beginning of the DList
    typename DList<TYPE>::iterator it = lists_[idx].begin();
    // Search the key until the end of array. If found, remove in the DList
    while (it != lists_[idx].end() && !rc)
    {
        if (*it == key)
        {
            rc = true;
            lists_[idx].erase(it);
            numRecords_--;
        }
        else
        {
            ++it;
        }
    }
    return rc;
}

// find function takes key and value parameters and find if there is a matching key existing in the table.
// key is hashed to find the right DList index to search the matching key.
// If exists, update the passed value to value that is matching with passed key inside the table.
// If key exists in the table, function returns true. Otherwise it returns false.
template <class TYPE>
bool ChainingTable<TYPE>::find(const std::string &key, TYPE &value)
{
    bool rc = false; // Return boolean value to show operation is successful
    // Hash the key and get the index to search the key
    std::hash<std::string> hashFunction;
    size_t hash = hashFunction(key);
    size_t idx = hash % capacity_;

    // Search the key and return an iterator pointing to matching key node or last iterator if not found
    typename DList<TYPE>::iterator it = lists_[idx].search(key, value);
    if (it != lists_[idx].end())
    {
        rc = true;
    }
    return rc;
}

// ChainingTable copy assignment
// It removes existing resources, then takes another ChainingTable object to create the same length of array and deep copy the resource
// Each Node in DList will have string key, TYPE value
template <class TYPE>
const ChainingTable<TYPE> &ChainingTable<TYPE>::operator=(const ChainingTable<TYPE> &other)
{
    if (this != &other)
    {
        delete[] lists_;                            // Remove the resources
        capacity_ = other.capacity_;                // Reset the capacity
        numRecords_ = other.numRecords_;            // Reset the number of records in the table
        lists_ = new DList<TYPE>[other.capacity()]; // Create same length array with copying ChainingTable

        for (int i = 0; i < capacity_; i++) // Copy resources from copying ChainingTable
        {
            lists_[i] = other.lists_[i];
        }
    }
    return *this;
}

// ChainingTable move assignment
// It takes another ChainingTable object to transfer the resources from.
// Each Node in DList will have string key, TYPE value
template <class TYPE>
const ChainingTable<TYPE> &ChainingTable<TYPE>::operator=(ChainingTable<TYPE> &&other)
{
    delete[] lists_;                  // Remove the resources
    lists_ = std::move(other.lists_); // Transfer the array of DList from other ChainingTable
    capacity_ = other.capacity_;      // Reset the capacity
    numRecords_ = other.numRecords_;  // Reset the number of records in the table
    other.numRecords_ = 0;            // Initialize the number of records in the table
    other.lists_ = nullptr;           // Initialize other ChainingTable
    other.capacity_ = 0;              // Initialize other ChainingTable
    return *this;
}

// ChainingTable destructor
// It removes the resources assigned to the object.
template <class TYPE>
ChainingTable<TYPE>::~ChainingTable()
{
    delete[] lists_; // Remove resources
}

// isEmpty returns true if numRecords equals zero. Otherwise it returns false.
template <class TYPE>
bool ChainingTable<TYPE>::isEmpty() const
{
    return numRecords() == 0; // Return true if the number of records in the table is zero
}

// numRecords returns the number of total records in the table as an integer.
template <class TYPE>
int ChainingTable<TYPE>::numRecords() const
{
    return numRecords_;
}

// capacity function returns the capacity of the table as an integer.
template <class TYPE>
int ChainingTable<TYPE>::capacity() const
{
    return this->capacity_;
}

// loadFactor function gets the load factor of the table which is the number of total records divided by capacity of the table.
template <class TYPE>
double ChainingTable<TYPE>::loadFactor() const
{
    double loadFactor = numRecords() / capacity(); // Get double value of the number of records divided by capacity
    return loadFactor;
}

// enum declaration to set each array index status
// empty - never assigned any records
// used - record assigned
// deleted - once assigned, but now deleted
enum Status
{
    empty,
    used,
    deleted
};
template <class TYPE>
class LPTable : public Table<TYPE>
{
    struct Record
    {
        TYPE data_;
        std::string key_;
        Status status_;
        Record() // Base constructor
        {
            status_ = empty;
        }
        Record(const std::string &key, const TYPE &data) // Constructor with arguments
        {
            key_ = key;
            data_ = data;
            status_ = empty;
        }
    };
    Record *records_;
    int capacity_;
    int numRecords_;

public:
    LPTable(int maxExpected);
    LPTable(const LPTable &other);
    LPTable(LPTable &&other);
    double loadFactor() const;
    virtual bool update(const std::string &key, const TYPE &value);
    virtual bool remove(const std::string &key);
    virtual bool find(const std::string &key, TYPE &value);
    virtual const LPTable &operator=(const LPTable &other);
    virtual const LPTable &operator=(LPTable &&other);
    virtual ~LPTable();
    virtual bool isEmpty() const;
    virtual int numRecords() const;
    virtual int capacity() const;
};

// LPTable constructor
// It takes capacity parameter as an integer to create an array of records in the table.
// Also capacity is stored in capacity_ member property
template <class TYPE>
LPTable<TYPE>::LPTable(int capacity) : Table<TYPE>()
{
    records_ = new Record[capacity]; // Capacity (number of elements for the array) of the table.
    capacity_ = capacity;            // Set the capacity using parameter
    numRecords_ = 0;                 // Initialize the number of records
}

// LPTable copy constructor
// It takes LPTable object to create the same length of array and deep copy the data from copying object.
template <class TYPE>
LPTable<TYPE>::LPTable(const LPTable<TYPE> &other)
{
    records_ = new Record[other.capacity_]; // Allocate resources same as other LPTable capacity
    capacity_ = other.capacity_;            // Reset capacity
    numRecords_ = other.numRecords_;        // Reset the number of records
    for (int i = 0; i < capacity_; i++)     // Copy records from other LPTable
    {
        records_[i] = other.records_[i];
    }
}

// LPTable move constructor
// It takes LPTable object to transfer resources from.
template <class TYPE>
LPTable<TYPE>::LPTable(LPTable<TYPE> &&other)
{
    records_ = std::move(other.records_); // Move records from other LPTable
    other.records_ = nullptr;             // Initialize moving LPTable records
    capacity_ = other.capacity_;          // Reset capacity
    numRecords_ = other.numRecords_;      // Reset the number of records
    other.numRecords_ = 0;                // Initialize moving LPTable number of records
    other.capacity_ = 0;                  // Initialize moving LPTable capacity
}

// update function takes string key value and generic type value parameters
// It gets hash value from the key and index from hash divided by capacity to find the starting index to traverse.
// If matching is found in the table, value is updated by passed value and it returns true.
// If key is not found, key-value pair is added to the table and it returns true.
// If the current number of records equals to capacity -1, key-value value is not added and returns false.
template <class TYPE>
bool LPTable<TYPE>::update(const std::string &key, const TYPE &value)
{
    bool rc = false; // Initialize returning boolean value
    // Hash the key and get the index from hash divided by capacity
    std::hash<std::string> hashFunction;
    size_t hash = hashFunction(key);
    size_t idx = hash % capacity_;

    // Traverse until it finds an empty index from the table. When matching key is found, update the value.
    while (records_[idx].status_ != empty && !rc)
    {
        if (records_[idx].key_ == key) // When key is found update the value to passed value
        {
            records_[idx].data_ = value;
            rc = true;
        }
        else // Continue to traverse
        {
            if (idx >= capacity_ - 1) // If it is the end of the array, go back to beginning
            {
                idx = 0;
            }
            else
            {
                idx++;
            }
        }
    }
    // Add key-value pair to empty index and mark as used if key is not found
    if (!rc && numRecords() < capacity_ - 1)
    {
        records_[idx].key_ = key;
        records_[idx].data_ = value;
        records_[idx].status_ = used;
        rc = true;
        numRecords_++; // Increase the number of records in the table
    }
    return rc;
}

// remove function takes string key parameter
// It gets hash value from the key and index from hash divided by capacity to find the starting index to traverse.
// If matching is found in the table, matching key-value pair is removed and index is marked as empty. And it returns true.
// If key is not found, it returns false
template <class TYPE>
bool LPTable<TYPE>::remove(const std::string &key)
{
    bool rc = false; // Initialize returning boolean value
    // Hash the key and get the index from hash divided by capacity
    std::hash<std::string> hashFunction;
    size_t hash = hashFunction(key);
    size_t idx = hash % capacity_;

    // Traverse the array until it finds matching key or empty index. When key is found, remove it and mark as empty
    while (records_[idx].status_ != empty)
    {
        if (records_[idx].key_ == key) // When key is found, initialize the all data members
        {
            records_[idx].key_.clear();
            records_[idx].data_ = {};
            records_[idx].status_ = deleted;
            rc = true;
            numRecords_--;
        }
        else // Continue to traverse
        {
            if (idx >= capacity_ - 1) // If it is the end of the array, go back to beginning
            {
                idx = 0;
            }
            else
            {
                idx++;
            }
        }
    }
    return rc;
}

// find function takes string key and generic type value parameters.
// It gets hash value from the key and index from hash divided by capacity to find the starting index to traverse.
// If matching is found in the table, matching key-value pair is removed and index is marked as empty. And it returns true.
// If key is not found, it returns false
template <class TYPE>
bool LPTable<TYPE>::find(const std::string &key, TYPE &value)
{
    bool rc = false; // Initialize returning boolean value
    // Hash the key and get the index from hash divided by capacity
    std::hash<std::string> hashFunction;
    size_t hash = hashFunction(key);
    size_t idx = hash % capacity_;

    // Traverse the array until it finds matching key or empty index. When key is found, copy the found value to passed value
    while (records_[idx].status_ != empty && !rc)
    {
        if (records_[idx].key_ == key) // When key is found, copy the value from data in the table
        {
            value = records_[idx].data_; //Update the returning value 
            rc = true;
        }
        else // Continue to traverse
        {
            if (idx >= capacity_ - 1) // If it is the end of the array, go back to beginning
            {
                idx = 0;
            }
            else
            {
                idx++;
            }
        }
    }
    return rc;
}

// LPTable copy assignment
// Allocate new resources as many as copying object capacity and deep copy all data
template <class TYPE>
const LPTable<TYPE> &LPTable<TYPE>::operator=(const LPTable<TYPE> &other)
{
    records_ = new Record[other.capacity_]; // Create resources as many as copying LPTable
    capacity_ = other.capacity_;            // Reset the capacity
    numRecords_ = other.numRecords_;        // Reset the number of records
    for (int i = 0; i < capacity_; i++)     // Copy records from other LPTable
    {
        records_[i] = other.records_[i];
    }
    return *this;
}

// LPTable move assignment
// Transfer all resources from moving LPTable object.
template <class TYPE>
const LPTable<TYPE> &LPTable<TYPE>::operator=(LPTable<TYPE> &&other)
{
    records_ = std::move(other.records_); // Transfer records from other table
    other.records_ = nullptr;             // Initialize moving LPTable
    capacity_ = other.capacity_;          // Reset the capacity
    numRecords_ = other.numRecords_;      // Reset the number of records
    other.capacity_ = 0;                  // Initialize moving LPTable capacity
    other.numRecords_ = 0;                // Initialize moving LPTable number of records
    return *this;
}

// LPTable destructor
template <class TYPE>
LPTable<TYPE>::~LPTable()
{
    delete[] records_; // Remove resources
}

// isEmpty return true when there is no records in the table. Otherwise it returns false.
template <class TYPE>
bool LPTable<TYPE>::isEmpty() const
{
    return numRecords() == 0; // Return true if the number of records in the table is zero
}

// numRecords traverse all the indexes in the table and count only element set to used
// It returns the total number of records as an integer
template <class TYPE>
int LPTable<TYPE>::numRecords() const
{
    return numRecords_;
}

// capacity returns the capacity of the table as an integer
template <class TYPE>
int LPTable<TYPE>::capacity() const
{
    return this->capacity_;
}

// loadFactor function gets the load factor of the table which is the number of total records divided by capacity of the table.
template <class TYPE>
double LPTable<TYPE>::loadFactor() const
{
    double loadFactor = numRecords() / capacity_; // Get double value of the number of records divided by capacity
    return loadFactor;
}
