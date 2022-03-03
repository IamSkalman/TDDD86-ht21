// Elis Öhman(elioh505) & Daniel Wendin(danwe681)
// Template class MyVector creates an array "storage" which can change in size
// "capacity" keeps track of array size and "numberOfElements" keeps track of
// actual amount of elements in the array

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"

template <typename T>
class MyVector
{

public:

    //Constructor, initializes the private variables with default values.
    MyVector();

    //Deconstructor, deletes the array of pointers (not the pointers themselves)
    ~MyVector();

    //Copyconstructor, initializes the private variables with other's values.
    MyVector(const MyVector& other);

    //Assignment operator, delete[] storage and sets private variables to other's values.
    MyVector& operator =(const MyVector& other);

    //inserts element after last element in array (if the array is full, it creates more space)
    void push_back(const T&);

    //decreases the number of elements by one
    void pop_back();

    //Index operator, return element from the array with index i
    T& operator[](unsigned i);

    //Const index operator, return const element from the array with index i
    const T& operator[](unsigned i)const;

    //return true if array is empty
    bool empty()const;

    //return pointer of start of array (the "space" not the element itself)
    T* begin();

    //return pointer of end of array (the "space" after last element in array)
    T* end();

    //delete the array and recreates a new (same as Deconstructor and then Constructor)
    void clear();

    //return number of elements
    unsigned size()const;

private:
    T* storage = nullptr;
    unsigned capacity;
    unsigned numberOfElements;
};

template<typename T>
MyVector<T>::MyVector(){
    capacity = 1;
    numberOfElements = 0;
    storage = new T[capacity];
}

template<typename T>
MyVector<T>::~MyVector(){
    delete[] storage; // each elements destructor in the array is called
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other){
    capacity = other.capacity;
    storage = new T[capacity];
    for(int i = 0; i < capacity; i++){
        storage[i] = other.storage[i];
    }
    numberOfElements = other.numberOfElements;
}

template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){
    if(!(&other == this)){
        delete[] storage; // each elements destructor in the array is called
        capacity = other.capacity;
        storage = new T[capacity];
        for(int i = 0; i < capacity; i++){
            storage[i] = other.storage[i];
        }
        numberOfElements = other.numberOfElements;
    }
    return *this;
}

template<typename T>
void MyVector<T>::push_back(const T& e){
    if(capacity == numberOfElements){
        T* newStorage = new T[capacity * 2]; // double the capacity of the array
        for (int i = 0; i < capacity; i++){
            newStorage[i] = storage[i];
        }
        delete[] storage; // each elements destructor in the array is called
        storage = newStorage;
        capacity *= 2;
    }
    storage[numberOfElements] = e;
    numberOfElements++;
}

template<typename T>
void MyVector<T>::pop_back(){
    if(numberOfElements > 0){
        numberOfElements--;
    }
}

template<typename T>
T& MyVector<T>::operator[](unsigned i){
    return storage[i];
}

template<typename T>
const T& MyVector<T>::operator[](unsigned i)const{
    return storage[i];
}

template<typename T>
bool MyVector<T>::empty()const{
    if(numberOfElements == 0){
        return true;
    }
    return false;
}

template<typename T>
void MyVector<T>::clear(){
    delete[] storage; // each elements destructor in the array is called
    capacity = 1;
    numberOfElements = 0;
    storage = new T[capacity];
}

template<typename T>
unsigned MyVector<T>::size()const{
    return numberOfElements;
}

template<typename T>
T* MyVector<T>::begin(){
    return storage;
}

template<typename T>
T* MyVector<T>::end(){
    return storage + numberOfElements;
}

#endif // MY_VECTOR_H
