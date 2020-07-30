/*
 *
 * Stack Reimplementation
 * Author: Alec Xu
 * Last Motified: April 18, 2020
 * 
 * Stack.h
 * Header and function declarations
 * 
 */

#ifndef STACK_H_
#define STACK_H_

template<typename ElemType>
class Stack
{
        public:
                //default constructor
                Stack();
                //destructor
                ~Stack();
                //copy constructor
                Stack(const Stack &rhs);
                //assignement operator
                Stack &operator=(const Stack &rhs);
                //checks if stack is empty
                bool is_empty();
                //returns the number of items stored in the stack
                int size();
                //returns the top element of the stack
                ElemType top();
                //adds an element to the top of the stack
                void push(ElemType element);
                //removes top element from the stack
                void pop();

        private:

                //array to store data
                ElemType *array;
                //number of items in the stack
                int num_items;
                //maximum number Stack is able to store
                int max_capacity;

                //verify memory is correctly allocated
                void ensure_capacity(int desired_capacity);
                //copies one array into another
                void copy_array(ElemType from[], ElemType to[], int length);
                //shifts elements to the right from one index to antoher
                void shift_right(int begin, int end);
                //shift elements to the left from one index to another
                void shift_left(int begin, int end);
};

#endif 