/*
 *
 * ArrayList Reimplementation
 * Author: Alec Xu
 * Last Motified: April 17, 2020
 * 
 * ArrayList.h
 * Header and function declarations
 * 
 */

#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_

template<typename ElemType>
class ArrayList
{
        public:
                //default constructor
                ArrayList();
                //initial capacity constructor
                ArrayList(int initial_capacity);
                //array constructor
                ArrayList(ElemType *temp_array, int size);
                //copy constructor
                ArrayList(const ArrayList &rhs);
                //destructor
                ~ArrayList();

                //assignment operator
                ArrayList &operator=(const ArrayList &rhs);

                //checks if ArrayList is empty
                bool is_empty();
                //clears the ArrayList
                void clear();
                //returns number of items
                int size();
                //returns first element
                ElemType first();
                //returns the last element
                ElemType last();
                //returns the element at the given index
                ElemType element_at(int index);
                //prints contents stored in the array
                void print();
                //adds an element to the back
                void push_at_back(ElemType element);
                //adds an element to the front
                void push_at_front(ElemType element);
                //adds an element to the given index
                void insert_at(ElemType element, int index);
                //inserts element by value in ascending order
                void insert_in_order(ElemType element);
                //removes first element
                void pop_from_front();
                //removes last element
                void pop_from_back();
                //removes element from given index
                void remove_at(int index);
                //replaces element at given index
                void replace_at(ElemType element, int index);
                
        private:

                //array of data
                ElemType *array;
                //current number of elements
                int num_items;
                //maximum number of items before increasing 
                //memory allocation
                int max_capacity;

                //ensure enough memory is allocated
                void ensure_capacity(int desired_capacity);
                //ensure given index is valid
                void ensure_in_range(int index, int low, int high);
                //shift elements to the right
                void shift_right(int begin, int end);
                //shift elements to the left
                void shift_left(int begin, int end);
                //copies one array into another
                void copy_array(ElemType from[], ElemType to[], int length);

};

#endif