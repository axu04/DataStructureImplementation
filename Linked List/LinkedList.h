/*
 *
 * LinkedList Reimplementation
 * Author: Alec Xu
 * Last Motified: April 18, 2020
 * 
 * LinkedList.h
 * Header and function declarations
 * 
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

template<typename ElemType>
class LinkedList 
{
        public:
                //default constructor
                LinkedList();
                //single element constructor
                LinkedList(ElemType element);
                //array constructor
                LinkedList(ElemType *array, int size);
                //copy constructor
                LinkedList(const LinkedList &rhs);
                //destructor
                ~LinkedList();
                //equal assignment operator
                LinkedList &operator=(const LinkedList &rhs);
                //checks if LinkedList is empty
                bool is_empty();
                //clears the entire LinkedList
                void clear();
                //returns number of elements
                int size();
                //returns first value stored in the LinkedList
                ElemType first();
                //returns last value stored in hte LinkedList
                ElemType last();
                //returns the element at a given index
                ElemType element_at(int index);
                //prints values
                void print();
                //adds an element to the back
                void push_at_back(ElemType element);
                //adds an element to the front
                void push_at_front(ElemType element);
                //inserts element at a given index
                void insert_at(ElemType element, int index);
                //inserts element by value in ascending order
                void insert_in_order(ElemType element);
                //removes an element from the front
                void pop_from_front();
                //removes an element from the back 
                void pop_from_back();
                //removes an element from a given index
                void remove_at(int index);
                //replaces value at a given index
                void replace_at(ElemType element, int index);

        private:

                //Node struct
                struct Node 
                {
                        ElemType data;
                        Node *next;
                        Node *prev;
                        //Node constructor function
                        Node(ElemType value, Node *next_p, Node *prev_p)
                        {
                                data = value;
                                next = next_p;
                                prev = prev_p;
                        }
                };

                //pointer to front of the LinkedList
                Node *front;
                //length of the LinkedList
                int length;

                //copies values from one object to another
                void copy_linked_list(const LinkedList &rhs);
                //checks that passed in indices are valid
                void ensure_in_range(int index, int low, int high);
                //inserts value into middle of a LinkedList
                void insert_in_middle(ElemType element, int index);
                //removes value from middle of a LinkedList
                void remove_from_middle(int index);

};

#endif