/*
 *
 * AVL Tree Reimplementation
 * Author: Alec Xu
 * Last Motified: Jul 22, 2020
 * 
 * AVL.h
 * Class Header and Declaration
 * 
 */

#ifndef AVL_H_
#define AVL_H_

template<typename ElemType>
class AVL
{
        public:
                //Constructor
                AVL();
                //Destructor
                ~AVL();
                //Copy Constructor
                AVL(const AVL &rhs);
                //Assignment operator
                AVL &operator=(const AVL &rhs);
                //checks if an element is stored in the AVL
                bool contains(ElemType element);
                //isnerts an element
                void insert(ElemType element);
                //removes an element
                void remove(ElemType element);
                //Checks the height of a tree
                int tree_height();
                //Counts number of nodes
                int node_count();
                //Counts the total value stored in the tree
                int count_total();
                //prints values stored in the AVL
                void print_tree();

        private:

                //struct to store node information
                struct Node 
                {
                        ElemType data;
                        int count;
                        int height;
                        Node *right;
                        Node *left;
                };
                //root of the AVL
                Node *root;
                //creates a deep copy of a tree
                Node *copy_tree(Node *node);
                //removes all nodes from a tree
                void delete_tree(Node *node);
                //checks if an element is stored in a AVL
                bool contains_recur(Node *node, ElemType element);
                //insert to a specific tree
                Node *insert_recur(Node *node, ElemType element);
                //removes element from the current subtree
                Node *remove_recur(Node *node, ElemType element);
                //finds the minimum value stored in a tree
                Node *find_min_value(Node *node);
                //Balances a tree to satisfy invariants
                Node *balance(Node *node);
                //Creates and allocates memory for a new node
                Node *new_node(ElemType element, int height, int count, Node *right, Node *left);
                //Rotates the current node rightward to maintain AVL invariants
                Node *right_rotate(Node *node);
                //Rotates the current node leftward to maintain AVL invariants
                Node *left_rotate(Node *node);
                //Returns difference in heights of each subtree given a node
                int height_diff(Node *node);
                //Returns the height of a given node
                int node_height(Node *node);
                //finds the height of a tree starting at the passed in node
                int tree_height_recur(Node *node);
                //determines if a node is a leaf
                bool is_a_leaf(Node *node);
                //counts the number of nodes starting at the passed in node
                int node_count_recur(Node *node);
                //sums the total of all values stored in the tree starting
                //at the passed in node
                int count_total_recur(Node *node);
                //in order traversal print
                void in_order_print(Node *root);
                //pre order traversal print
                void pre_order_print(Node *root);
                //level order traversal print
                void level_order_print(Node *root);
};

#endif