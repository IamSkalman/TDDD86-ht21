// Elis Öhman(elioh505) & Daniel Wendin(danwe681)
// Template class MyPriorityQueue which uses template class MyVector<T> 
// to store elements and a comparator C for sorting the queue 

#ifndef MY_PRIORITY_QUEUE_H
#define MY_PRIORITY_QUEUE_H

#include "MyVector.h"
#include "MyException.h"
#include "algorithm"
#import "cmath"


template <typename T, typename C>
class MyPriorityQueue
{
    MyVector<T> vector_array;
    C strictly_larger_operator;

public:

    //default constructor
    MyPriorityQueue() = default;

    //default deconstructor
    ~MyPriorityQueue() = default;

    //inserts t at last pos in vector, then switches t with parent if priority of t > priority of parent
    void push(const T& t);

    //returns element with highest priority (first in array)
    T top()const;

    //removes element with highest priority
    void pop();

    //returns true if array is empty
    bool empty()const;

    //returns number of elements in array
    unsigned size() const;


private:

};

template <typename T, typename C>
void MyPriorityQueue<T,C>::push(const T& t){
    vector_array.push_back(t);
    int curIndex = vector_array.size() - 1;
    if(curIndex > 0){ // root node(index 0) have no parent to compare with
        int parentIndex = (curIndex-1)/2; // index algorithm to find parent in a heap (e.g 0.5 truncates to 0)
	// t gets swapped with the current parent as long as it has higher priority
        while(strictly_larger_operator(vector_array[parentIndex], t)){
            std::swap(vector_array[curIndex],vector_array[parentIndex]);
            curIndex = parentIndex;
            parentIndex = (curIndex-1)/2; // index algorithm to find parent in a heap (e.g 0.5 truncates to 0)
        }
    }
}

template <typename T, typename C>
T MyPriorityQueue<T,C>::top()const{
    return vector_array[0];
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::pop(){
    if(vector_array.size() > 0){
        std::swap(vector_array[vector_array.size()-1], vector_array[0]); // element with highest priority gets swapped with last element
        vector_array.pop_back(); // element with highest priority gets removed
        int currentIndex = 0;
	// last element moves down the heap as long as a child has higher priority
        while(!((currentIndex >= (int)((vector_array.size())/2)) && currentIndex < vector_array.size())){
            int childPos = 2*currentIndex + 1; // index algorithm to find left child in a heap
	    // if both left and right child exists and right child has higher priority --> make childPos the right child
            if(childPos < (vector_array.size()-1) && childPos+1 < vector_array.size()
                    && strictly_larger_operator(vector_array[childPos], vector_array[childPos+1])){
                childPos++;
            }
	    // if child on childPos exists and child has higher priority than its parent swap their positions
	    // else the previous element has found its correct place in the queue
            if(childPos < vector_array.size()){
                if(strictly_larger_operator(vector_array[currentIndex], vector_array[childPos])){
                    std::swap(vector_array[currentIndex], vector_array[childPos]);
                }
                else{
                    break;
                }
            }
	    // previous last element has no children and can't be prioritized lower
            else{
                break;
            }
            currentIndex = childPos;
        }
    }
}

template <typename T, typename C>
bool MyPriorityQueue<T,C>::empty()const{
    if(vector_array.empty()){
        return true;
    }
    return false;

}

template <typename T, typename C>
unsigned MyPriorityQueue<T,C>::size()const{
    return vector_array.size();

}

#endif // MY_PRIORITY_QUEUE_H
