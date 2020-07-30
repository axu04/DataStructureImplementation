/*
 *
 * LinkedList Reimplementation
 * Author: Alec Xu
 * Last Motified: April 18, 2020
 * 
 * LinkedList.cpp
 * Full function implementation
 * 
 */

#include "LinkedList.h"

#include <iostream>

using namespace std;

//default constructor
//Parameters: Nothing
//Returns: Nothing
//Does: Initializes an instance of the LinkedList class
template<typename ElemType>
LinkedList<ElemType>::LinkedList()
{
        front = nullptr;
        length = 0;
}

//element constructor
//Parmaters: ElemType element, item being initially added to
//           the LinkedList
//Returns: Nothing
//Does: Initializes an instance of the class with one item 
//      stored initially
template<typename ElemType>
LinkedList<ElemType>::LinkedList(ElemType element)
{
        Node *temp = new Node(element, nullptr, nullptr);
        front = temp;
        length = 1;
}

//array constructor
//Parameters: ElemType *array, array being added to the LinkedList
//            int size, length of the array
//Returns: Nothing
//Does: Initializes the LinkedList with the values stored in
//      the passed in array
template<typename ElemType>
LinkedList<ElemType>::LinkedList(ElemType *array, int size)
{
        length = 0;
        if (size == 0)
        {
                front = nullptr;
                return;
        }
        Node *first = new Node(array[0], nullptr, nullptr);
        front = first;
        for (int i = 1; i < size; i++)
        {
                Node *next_one = new Node(array[i], nullptr, first);
                first->next = next_one;
                first = first->next;
        }
        length = size;
}

//copy constructor
//Parameters: const LinkedList &rhs, second instance of 
//            the LinkedList class
//Returns: Nothing
//Does: Creates a second object using a passed in instance
template<typename ElemType>
LinkedList<ElemType>::LinkedList(const LinkedList &rhs)
{
        copy_linked_list(rhs);
}

//destructor
//Parameters: Nothing
//Returns: Nothing
//Does: Deallocates dynamically allocated memory
template<typename ElemType>
LinkedList<ElemType>::~LinkedList()
{
        Node *curr = front;
        if (front == nullptr)
        {
                delete curr;
                return;
        }
        while (curr != nullptr)
        {
                Node *temp = curr->next;
                curr->next = curr->prev = nullptr;
                delete curr;
                curr = temp;
        }
}

//assignment operator
//Parameters: const LinkedList &rhs, second instance of 
//            the LinkedList class
//Returns: LinkedList<ElemType>
//Does: Copies all values stored in the passed in object into the
//      current object
template<typename ElemType>
LinkedList<ElemType> &LinkedList<ElemType>::operator=(const LinkedList &rhs)
{
        if (this == &rhs)
        {
                return *this;
        }
        clear();
        copy_linked_list(rhs);
        return *this;
}

//is_empty function
//Parameters: Nothing
//Returns: bool
//Does: Checks if a linkedlist is empty
template<typename ElemType>
bool LinkedList<ElemType>::is_empty()
{
        if (front == nullptr)
        {
                return true;
        }
        return false;
}

//clear function
//Paramters: Nothing
//Returns: Nothing
//Does: Clears the items stored in the LinkedList
template<typename ElemType>
void LinkedList<ElemType>::clear()
{
        Node *curr = front;
        while (curr != nullptr)
        {
                Node *temp = curr;
                curr = curr->next;
                delete temp;
        }
        front = nullptr;
        length = 0;
}

//size function
//Parameters: Nothing
//Returns: int
//Does: Returns the number of items stored in the
//      LinkedList
template<typename ElemType>
int LinkedList<ElemType>::size()
{
        return length;
}

//first function
//Parameters: Nothing
//Returns: ElemType
//Does: Returns the first element in the LinkedList
template<typename ElemType>
ElemType LinkedList<ElemType>::first()
{
        if (length == 0)
        {
                throw runtime_error("cannot get first " 
                                        "of empty doubly−linked list");
        }
        return front->data;
}

//last function
//Parameters: Nothing
//Returns: ElemType
//Does: Returns the last element in the LinkedList
template<typename ElemType>
ElemType LinkedList<ElemType>::last()
{
        if (length == 0)
        {
                throw runtime_error("cannot get last "
                                        "of empty doubly-linked list");
        }
        ElemType info;
        Node *curr = front;
        while (curr != nullptr)
        {
                if (curr->next == nullptr)
                {
                        info = curr->data;
                }
                curr = curr->next;
        }
        return info;
}

//element_at function
//Parameters: int index, index being accessed
//Returns: ElemType
//Does: Returns the element stored at the given index
template<typename ElemType>
ElemType LinkedList<ElemType>::element_at(int index)
{
        ensure_in_range(index, 0, length-1);
        Node *curr = front;
        ElemType info;
        for (int i = 0; i <= index; i++)
        {   
                if (i == index)
                {
                        info = curr->data;
                }
                curr = curr->next;
        }
    return info;
}

//print function
//Parameters: Nothing
//Returns: Nothing
//Does: Prints the elements of the LinkedList
template<typename ElemType>
void LinkedList<ElemType>::print()
{
        cout << "[LinkedList of size " << length << " <<";
        Node *curr = front;
        if (length == 0)
        {
                cout << ">>]" << endl;
                return;
        }
        while (curr != nullptr)
        {
                cout << curr->data;
                curr = curr->next;
        }
        cout << ">>]" << endl;
}

//push_at_back function
//Parameters: ElemType element, element being added to the 
//            back of the LinkedList
//Returns: Nothing
//Does: Adds an element to the back of the LinkedList
template<typename ElemType>
void LinkedList<ElemType>::push_at_back(ElemType element)
{
        Node *curr = front;
        while (curr != nullptr)
        {
                if (curr->next == nullptr)
                {
                Node *a_new = new Node(element, nullptr, curr);
                curr->next = a_new;
                length++;
                return;
                }
                curr = curr->next;
        }
        Node *a_new = new Node(element, nullptr, nullptr);
        front = a_new;
        length++;
}

//push_at_front function
//Parameters: ElemType element, element being added to the LinkedList
//Returns: Nothing
//Does: Adds an element to the front of the LinkedList
template<typename ElemType>
void LinkedList<ElemType>::push_at_front(ElemType element)
{
        if (front != nullptr)
        {
                Node *elem_new = new Node(element, front, nullptr);
                front->prev = elem_new;
                front = elem_new;
                length++;
                return;
        }
        Node *a_new = new Node(element, nullptr, nullptr);
        front = a_new;
        length++;
}

//insert_at function
//Parameters: ElemType element, element added to the LinkedList
//            int index, index being accessed
//Returns: Nothing
//Does: Inserts a given element at the passed in index
template<typename ElemType>
void LinkedList<ElemType>::insert_at(ElemType element, int index)
{
        ensure_in_range(index, 0,length);
        if (index == 0)
        {
                push_at_front(element);
        }
        else if (index == length)
        {
                push_at_back(element);
        }
        else 
        {
                insert_in_middle(element, index);
        }
        return;
}

//insert_in_order function
//Parameters: ElemType element, item added to the LinkedList
//Returns: Nothing
//Does: Inserts the element by value in ascending order
template<typename ElemType>
void LinkedList<ElemType>::insert_in_order(ElemType element)
{
        int index = 0;
        Node *curr = front;
        if (front == nullptr)
        {
                push_at_front(element);
                return;
        }
        while (!(element < curr->data))
        {
                if (curr->next == nullptr)
                {
                        push_at_back(element);
                return;
                }
                curr = curr->next;
                index++;
        }
        insert_at(element, index);
}

//pop_from_front function
//Parameters: Nothing
//Returns: Nothing
//Does: Deletes first item stored in LinkedList
template<typename ElemType>
void LinkedList<ElemType>::pop_from_front()
{
        if (length == 0)
        {
                throw runtime_error("cannot pop from "
                                        "empty doubly−linked list");
        }
        Node *temp = front;
        Node *next = front->next;
        front = next;
        delete temp;
        length--;
}

//pop_from_back function
//Parameters: Nothing
//Returns: Nothing
//Does: Removes last element in LinkedList
template<typename ElemType>
void LinkedList<ElemType>::pop_from_back()
{
        if (length == 0)
        {
                throw runtime_error("cannot pop from " 
                                        "empty doubly−linked list");
        } 
        else if (length == 1)
        {
                pop_from_front();
        }
        Node *curr = front;
        while (curr != nullptr)
        {
                if (curr->next == nullptr)
                {
                        Node *last_one = curr->prev;
                        delete curr;
                        last_one->next = nullptr;
                        length--;
                        return;
                }
                curr = curr->next;
        }
}

//remove_at function
//Parameters: int index, index being removed 
//Returns: Nothing
//Does: Removes the element stored at the passed in index
template<typename ElemType>
void LinkedList<ElemType>::remove_at(int index)
{
        ensure_in_range(index, 0, length-1);
        if (index == 0)
        {
                pop_from_front();
        }
        else if (index == length)
        {
                pop_from_back();
        }
        else 
        {
                remove_from_middle(index);
        }
}

//replace_at function
//Parameters: int index, index that is being accessed in the function
//            ElemType element, value that is being replaced 
//Return: Nothing
//Does: Replaces the value in the node at the given index with the passed in 
//      ElemType value
template<typename ElemType>
void LinkedList<ElemType>::replace_at(ElemType element, int index)
{
        ensure_in_range(index, 0, length-1);
        Node *curr = front;
        for (int i = 0; i <= index; i++)
        {
                if (i == index)
                {
                        curr->data = element;
                        return;
                }
                curr = curr->next;
        }
}

//copy_linked_list function
//Parameters: const LinkedList &rhs, second instance of
//            the LinkedList class
//Returns: Nothing
//Does: Copies the items in one LinkedList into the second instance
template<typename ElemType>
void LinkedList<ElemType>::copy_linked_list(const LinkedList &rhs)
{
        length = rhs.length;
    
        if (rhs.front == nullptr)
        {
                front = nullptr;
                return;
        }
        front = new Node(rhs.front->data, nullptr, nullptr);
        Node *curr = front;
        Node *orig = rhs.front;
        
        while (orig->next != nullptr)
        {
            Node *curr_next = new Node(orig->next->data, nullptr, curr);
            curr->next = curr_next;
            curr = curr->next;
            orig = orig->next;
        }
}

//ensure_in_range function
//Parameters: int index, index being accessed
//            int low, lowest index possible
//            int high, highest index possible
//Returns: Nothing
//Does: Checks if a index is within the passed in high and low values
template<typename ElemType>
void LinkedList<ElemType>::ensure_in_range(int index, int low, int high)
{
        if (index < low or index > high)
        {
                throw range_error("Index accessed is not in range");
        }
}

//insert_in_middle function
//Parameters: ElemType element, value that is being inserted into 
//            the LinkedList
//            int index, index that is being accessed
//Return: Nothing 
//Does: inserts the element value at the given index if the index is 
//      not equal to 0 or the length of the linkedlist
template<typename ElemType>
void LinkedList<ElemType>::insert_in_middle(ElemType element, int index)
{
        Node *curr = front;
        for (int i = 0; i <= index; i++)
        {
                if (i == index)
                {
                        Node *last = curr->prev;
                        Node *elem_new = new Node(element, curr, curr->prev);
                        curr->prev = elem_new;
                        last->next = elem_new;
                        length++;
                        return;
                }
                curr = curr->next;
        }
}

//remove_from_middle function
//Parameters: int index, index being accessed
//Returns: Nothing
//Does: deletes the node at the given index if the index is not equal to 
//      0 or equal to the length of the linkedlist
template<typename ElemType>
void LinkedList<ElemType>::remove_from_middle(int index)
{
        Node *curr = front;
        for (int i = 0; i <= index; i++)
        {
                if (i == index)
                {
                        Node *next_one = curr->next;
                        Node *prev_one = curr->prev;
                        delete curr;
                        next_one->prev = prev_one;
                        prev_one->next = next_one;
                        length--;
                        return;
                }
                curr = curr->next;
        }
}