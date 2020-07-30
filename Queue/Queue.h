/*
 *
 * Queue Reimplementation
 * Author: Alec Xu
 * Last Motified: April 18, 2020
 * 
 * Queue.h
 * Header and function declarations
 * 
 */

#ifndef QUEUE_H_
#define QUEUE_H_

template<typename ElemType>
class Queue
{
        public:
                //default constructor
                Queue();
                //destructor
                ~Queue();
                //copy constructor
                Queue(const Queue &rhs);
                //assignment operator
                Queue &operator=(const Queue &rhs);
                //checks if Queue is empty
                bool is_empty();
                //returns the number of items in the Queue
                int size();
                //returns first element in the Queue
                ElemType front();
                //returns last element in the Queue
                ElemType back();
                //adds an element to the end of the Queue
                void push(ElemType element);
                //removes first element from the Queue
                void pop();

        private:

                //array storing data
                ElemType *array;
                //number of items currently stored
                int num_items;
                //maximum number of elements 
                int max_capacity;
                //verify memory is correctly allocated
                void ensure_capacity(int desired_capacity);
                //copies one array into another
                void copy_array(ElemType from[], ElemType to[], int length);
                //shifts all elements to the left from one index to another
                void shift_left(int begin, int end);

};

#endif