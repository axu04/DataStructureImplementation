/*
 *
 * Stack Reimplementation
 * Author: Alec Xu
 * Last Motified: April 18, 2020
 * 
 * Stack.cpp
 * Full function implementation
 * 
 */

#include "Stack.h"
#include <iostream>

//default constructor
//Parameters: Nothing
//Returns: Nothing
//Does: Initializes an instance of the class
template<typename ElemType>
Stack<ElemType>::Stack()
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
Stack<ElemType>::~Stack()
{
        num_items = max_capacity = -1;
        delete [] array;
        array = nullptr;
}

//copy constructor
//Parameters: const Stack &rhs, second instance of the 
//            Stack class
//Returns: Nothing
//Does: Creates new instance of the Stack Class and copies
//      the values stored in object passed in
template<typename ElemType>
Stack<ElemType>::Stack(const Stack &rhs)
{
        num_items = rhs.num_items;
        array = new ElemType[num_items];
        max_capacity = num_items;
        copy_array(rhs.array, array, num_items);
}

//assignment operator
//Parameters: const Stack &rhs, second instance of the 
//            Stack class
//Returns: Nothing
//Does: Copies all values stored in the passed in object into the
//      current object
template<typename ElemType>
Stack<ElemType> &Stack<ElemType>::operator=(const Stack &rhs)
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
//Does: Checks if the Stack object is empty
template<typename ElemType>
bool Stack<ElemType>::is_empty()
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
//Does: Returns the number of items in the Stack
template<typename ElemType>
int Stack<ElemType>::size()
{
        return num_items;
}

//top function
//Parameters: Nothing
//Returns: ElemType
//Does: Returns the top element on the Stack
template<typename ElemType>
ElemType Stack<ElemType>::top()
{
        return array[0];
}

//push function
//Parameters: ElemType element, item added to the Stack
//Returns: Nothing
//Does: Adds an element to the top of the stack
template<typename ElemType>
void Stack<ElemType>::push(ElemType element)
{
        ensure_capacity(num_items+1);
        shift_right(num_items,0);
        array[0] = element;
        num_items++;
}

//pop function
//Parameters: Nothing
//Returns: Nothing
//Does: Removes the first element from the Stack
template<typename ElemType>
void Stack<ElemType>::pop()
{
        if (num_items < 1)
        {
                throw runtime_error("Cannot pop from " 
                                        "empty Stack");
        }
        shift_left(0,num_items-1);
        num_items--;
}

//ensure_capacity function
//Parameters: int desired_capacity, amount of memory needed
//Returns: Nothing
//Does: Checks if Stack has the desired memory allocation
template<typename ElemType>
void Stack<ElemType>::ensure_capacity(int desired_capacity)
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
void Stack<ElemType>::copy_array(ElemType from[], 
                                        ElemType to[], int length)
{
        for (int i = 0; i < length; ++i)
                to[i] = from[i];
}

//shift_right function
//Parameters: int being, index of the beginning of the shift
//            int end, index of the end of the shift
//Returns: Nothing
//Does: Shifts elements to the right from the begin index
//      to the end index
template<typename ElemType>
void Stack<ElemType>::shift_right(int begin, int end)
{
        for (int i = begin; i > end; i--)
        {
                array[i] = array[i-1];
        }
}

//shift_left function
//Parameters: int begin, index of the beginning of the shift
//            int end, index of the end of the shift
//Returns: Nothing
//Does: Shifts elements to the left within the bounds 
//      passed into the function
template<typename ElemType>
void Stack<ElemType>::shift_left(int begin, int end)
{
        for (int i = begin; i < end; i++)
        {
                array[i] = array[i+1];
        }
}