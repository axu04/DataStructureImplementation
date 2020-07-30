/*
 *
 * ArrayList Reimplementation
 * Author: Alec Xu
 * Last Motified: April 17, 2020
 * 
 * ArrayList.cpp
 * Full function implementation
 * 
 */

#include "ArrayList.h"

#include <iostream>
#include <string>

using namespace std;

//default constructor
//Parameters: Nothing
//Returns: Nothing
//Does: Initializes an empty instance of the ArrayList class
template<typename ElemType>
ArrayList<ElemType>::ArrayList() 
{
        num_items = 0;
        max_capacity = 0;
        array = nullptr;

}

//initial capacity constructor 
//Parameters: int initial_capacity, initial array size
//Returns: Nothing
//Does: Initializes an array given an initial capacity 
template<typename ElemType>
ArrayList<ElemType>::ArrayList(int initial_capacity) 
{
        num_items = 0;
        max_capacity = initial_capacity;
        array = new ElemType[max_capacity];
}

//array constructor 
//Parameters: ElemType *temp_array, array containing elements 
//            being inserted to the array
//Returns: Nothing
//Does: Initializes an instance using a passed in array and 
//      the length
template<typename ElemType>
ArrayList<ElemType>::ArrayList(ElemType *temp_array, int size)
{
        array = new ElemType[size];
        num_items = size;
        for (int i = 0; i < size; i++) {
                array[i] = temp_array[i];
        }
        max_capacity = num_items;
}

//copy constructor 
//Parameters: const ArrayList &rhs, second instance of the class
//Returns: Nothing
//Does: Creates new instance of the ArrayList Class and copies
//      the values stored in object passed in
template<typename ElemType>
ArrayList<ElemType>::ArrayList(const ArrayList &rhs)
{
        num_items = rhs.num_items;
        array = new ElemType[num_items];
        max_capacity = num_items;
        for (int i = 0; i < num_items; i++) 
        {
                array[i] = rhs.array[i];
        }
}

//destructor
//Parameters: Nothing
//Returns: Nothing
//Does: Deletes dynamically allocated memory
template<typename ElemType>
ArrayList<ElemType>::~ArrayList()
{
        num_items = max_capacity = -1;
        delete [] array;
        array = NULL;
}

//assignment operator
//Parameters: const ArrayList &rhs, second instance of the class
//Returns: ArrayList<ElemType>
//Does: Copies all values stored in the passed in object into the
//      current object
template<typename ElemType>
ArrayList<ElemType> &ArrayList<ElemType>::operator=(const ArrayList &rhs)
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
//Paramters: Nothing
//Returns: bool
//Does: Checks if the ArrayList is empty
template<typename ElemType>
bool ArrayList<ElemType>::is_empty()
{
        if (num_items == 0)
        {
                return true;
        }
        return false;
}

//clear function
//Parameters: Nothing
//Returns: Nothing
//Does: clears the ArrayList
template<typename ElemType>
void ArrayList<ElemType>::clear()
{
        num_items = 0;
}

//size function
//Parameters: Nothing
//Returns: int, the current size of the ArrayList
//Does: Returns the number of items stored in the ArrayList
template<typename ElemType>
int ArrayList<ElemType>::size()
{
        return num_items;
}

//first function
//Parameters: Nothing
//Returns: ElemType
//Does: Returns the first item stored in the ArrayList
template<typename ElemType>
ElemType ArrayList<ElemType>::first()
{
        if (num_items < 1)
        {
                throw runtime_error("Cannot get first of "
                                        "empty ArrayList");
        }
        return array[0];
}

//last function
//Parameters: Nothing
//Returns: ElemType
//Does: Returns the last item stored in the ArrayList
template<typename ElemType>
ElemType ArrayList<ElemType>::last()
{
        if (num_items < 1)
        {
                throw runtime_error("Cannot get last of " 
                                        "empty ArrayList");
        }
        return array[num_items-1];
}

//element_at function
//Paramters: int index, index being accessed
//Returns: Elemtype
//Does: Returns the item stored at the passed in index value
template<typename ElemType>
ElemType ArrayList<ElemType>::element_at(int index)
{
        ensure_in_range(index,0,num_items-1);
        return array[index];
}

//print function
//Parameters: Nothing
//Returns: Nothing
//Does: Prints the current contents in the ArrayList
template<typename ElemType>
void ArrayList<ElemType>::print()
{
        cout << "[ArrayList of size " << num_items << " <<";
                for (int i = 0; i < num_items; i++)
        {
                cout << array[i];
        }
        cout << ">>]" << endl;
}

//push_at_back function
//Parameters: ElemType element, item being added to the ArrayList
//Returns: Nothing
//Does: Adds a passed in element to the back of the ArrayList
template<typename ElemType>
void ArrayList<ElemType>::push_at_back(ElemType element)
{
        ensure_capacity(num_items+1);
        array[num_items] = element;
        num_items++;
}

//push_at_front function
//Parameters: ElemType element, item being added to the ArrayList
//Returns: Nothing
//Does: Adds a passed in element to the front of the ArrayList
template<typename ElemType>
void ArrayList<ElemType>::push_at_front(ElemType element)
{
        ensure_capacity(num_items+1);
        shift_right(num_items,0);
        array[0] = element;
        num_items++;
}

//insert_at function
//Parameters: ElemType element, element being added to the ArrayList
//            int index, index being accessed
//Returns: Nothing
//Does: Adds the passed in element to the passed in index 
//      of the ArrayList
template<typename ElemType>
void ArrayList<ElemType>::insert_at(ElemType element, int index)
{
        ensure_in_range(index,0,num_items);
        ensure_capacity(num_items+1);
        shift_right(num_items, index);
        array[index] = element;
        num_items++;
}

//insert_in_order function
//Parameters: ElemType element, element being added to the ArrayList
//Returns: Nothing
//Does: Adds the passed in element to the ArrayList in ascending
//      order
template<typename ElemType>
void ArrayList<ElemType>::insert_in_order(ElemType element)
{
        ensure_capacity(num_items+1);
        for (int i = 0; i < num_items; i++)
        {
                if (element < array[i])
                {
                        shift_right(num_items, i);
                        array[i] = element;
                        num_items++;
                        return;
                }
        }
        array[num_items] = element;
        num_items++;
}

//pop_from_front function
//Parameters: Nothing
//Returns: Nothing
//Does: Removes the first element from the ArrayList
template<typename ElemType>
void ArrayList<ElemType>::pop_from_front()
{
        if (num_items < 1)
        {
                throw runtime_error("Cannot pop from " 
                                        "empty ArrayList");
        }
        shift_left(0,num_items-1);
        num_items--;
}

//pop_from_back function
//Parameters: Nothing
//Returns: Nothing
//Does: Removes the last element stored in the ArrayList
template<typename ElemType>
void ArrayList<ElemType>::pop_from_back()
{
        if (num_items < 1)
        {
                throw runtime_error("Cannot pop from " 
                                        "empty ArrayList");                
        }
        num_items--;
}

//remove_at function
//Parameters: int index, index being accessed
//Returns: Nothing
//Does: Removes the element stored at a specific index
template<typename ElemType>
void ArrayList<ElemType>::remove_at(int index)
{
        ensure_in_range(index, 0, num_items-1);
        shift_left(index, num_items-1);
        num_items--;
}

//replace_at function
//Parameters: ElemType element, element being added
//            int index, index being accessed
//Returns: Nothing
//Does: Replaces the element stored at a specific element
//      with the ElemType passed into the function
template<typename ElemType>
void ArrayList<ElemType>::replace_at(ElemType element, int index)
{
        ensure_in_range(index, 0, num_items-1);
        array[index] = element;
}

//ensure_capacity function
//Parameters: int desired_capacity, amount of memory needed
//Returns: Nothing
//Does: Checks if ArrayList has desired memory allocation
template<typename ElemType>
void ArrayList<ElemType>::ensure_capacity(int desired_capacity)
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

//ensure_in_range function
//Parameters: int index, index being accessed
//            int low, lowest index possible
//            int high, highest index possible
//Returns: Nothing
//Does: Checks if a index is within the passed in high and low values
template<typename ElemType>
void ArrayList<ElemType>::ensure_in_range(int index, int low, int high)
{
        if (index < low or index > high)
        {
                throw range_error("Index accessed is not in range");
        }
}

//shift_right function
//Parameters: int being, index of the beginning of the shift
//            int end, index of the end of the shift
//Returns: Nothing
//Does: Shifts elements to the right from the begin index
//      to the end index
template<typename ElemType>
void ArrayList<ElemType>::shift_right(int begin, int end)
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
void ArrayList<ElemType>::shift_left(int begin, int end)
{
        for (int i = begin; i < end; i++)
        {
                array[i] = array[i+1];
        }
}

//copy_array function
//Parameters: ElemType from[], array that is being copied from
//            ElemType to[], array being copied into
//            int length, the length of the array 
//Returns: Nothing
//Does: Copies the contents of an array from one to another
template<typename ElemType>
void ArrayList<ElemType>::copy_array(ElemType from[], 
                                        ElemType to[], int length)
{
        for (int i = 0; i < length; ++i)
                to[i] = from[i];
}


