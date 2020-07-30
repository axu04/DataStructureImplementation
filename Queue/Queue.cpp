/*
 *
 * Queue Reimplementation
 * Author: Alec Xu
 * Last Motified: April 18, 2020
 * 
 * Queue.cpp
 * Full function implementation
 * 
 */

#include "Queue.h"
#include <iostream>

using namespace std;

//default constructor
//Parameters: Nothing
//Returns: Nothing
//Does: Initializes an instance of the class
template<typename ElemType>
Queue<ElemType>::Queue()
{
        array = nullptr;
        num_items = 0;
        max_capacity = 0;
}

//destructor
//Parameters: Nothing
//Returns: Nothing
//Does: Deletes all dynamically allocated memory
template<typename ElemType>
Queue<ElemType>::~Queue()
{
        num_items = max_capacity = -1;
        delete [] array;
        array = nullptr;
}

//copy constructor
//Parameters: const Queue &rhs, second instance of the class
//Returns: Nothing
//Does: Creates new instance of the Queue Class and copies
//      the values stored in object passed in
template<typename ElemType>
Queue<ElemType>::Queue(const Queue &rhs)
{
        num_items = rhs.num_items;
        array = new ElemType[num_items];
        max_capacity = num_items;
        copy_array(rhs.array, array, num_items);
}

//assignment operator
//Parameters: const Queue &rhs, second instance of the class
//Returns: Queue<ElemType>
//Does: Copies all values stored in the passed in object into the
//      current object
template<typename ElemType>
Queue<ElemType> &Queue<ElemType>::operator=(const Queue &rhs)
{
        if (this == &rhs)
        {
                return *this;
        }
        num_items = rhs.num_items;
        max_capacity = rhs.max_capacity;

        delete [] array;
        array = new ElemType[max_capacity];
        copy_array(rhs.array, array, num_items);
        return *this;
}

//is_empty function
//Parameters: Nothing
//Returns: bool
//Does: Checks if a queue is empty
template<typename ElemType>
bool Queue<ElemType>::is_empty()
{
        if (num_items == 0)
        {
                return true;
        }
        return false;
}

//size function
//Parameters: Nothing
//Returns: int
//Does: Returns the number of items stored 
//      within the Queue
template<typename ElemType>
int Queue<ElemType>::size()
{
        return num_items;
}

//front function
//Parameters: Nothing
//Returns: ElemType
//Does: Returns the first item stored in the Queue
template<typename ElemType>
ElemType Queue<ElemType>::front()
{
        if (num_items < 1)
        {
                throw runtime_error("Cannot get first of "
                                        "empty Queue");
        }
        return array[0];
}

//back function
//Parameters: Nothing
//Returns: ElemType
//Does: Returns the last item stored in the Queue
template<typename ElemType>
ElemType Queue<ElemType>::back()
{
        if (num_items < 1)
        {
                throw runtime_error("Cannot get last of " 
                                        "empty Queue");
        }
        return array[num_items-1];
}

//push function
//Parameters: ElemType element, item being added to the Queue
//Returns: Nothing
//Does: Adds an element to the back of the Queue
template<typename ElemType>
void Queue<ElemType>::push(ElemType element)
{
        ensure_capacity(num_items+1);
        array[num_items] = element;
        num_items++;
}

//pop function
//Parameters: Nothing
//Returns: Nothing
//Does: Removes the first item in the Queue
template<typename ElemType>
void Queue<ElemType>::pop()
{
        if (num_items < 1)
        {
                throw runtime_error("Cannot pop from " 
                                        "empty Queue");
        }
        shift_left(0,num_items-1);
        num_items--;
}

//ensure_capacity function
//Parameters: int desired_capacity, amount of memory needed
//Returns: Nothing
//Does: Checks if Queue has the desired memory allocation
template<typename ElemType>
void Queue<ElemType>::ensure_capacity(int desired_capacity)
{
        if (num_items > desired_capacity)
        {
                return;
        }
        ElemType *new_array = NULL;
        new_array = new ElemType[desired_capacity];
        max_capacity = desired_capacity;
        for (int i = 0; i < num_items; i++)
        {
                new_array[i] = array[i];
        }
        delete [] array;
        array = new_array;
}

//copy_array function
//Parameters: ElemType from[], array that is being copied from
//            ElemType to[], array being copied into
//            int length, the length of the array 
//Returns: Nothing
//Does: Copies the contents of an array from one to another
template<typename ElemType>
void Queue<ElemType>::copy_array(ElemType from[], 
                                        ElemType to[], int length)
{
        for (int i = 0; i < length; ++i)
                to[i] = from[i];
}

//shift_left function
//Parameters: int begin, index of the beginning of the shift
//            int end, index of the end of the shift
//Returns: Nothing
//Does: Shifts elements to the left within the bounds 
//      passed into the function
template<typename ElemType>
void Queue<ElemType>::shift_left(int begin, int end)
{
        for (int i = begin; i < end; i++)
        {
                array[i] = array[i+1];
        }
}