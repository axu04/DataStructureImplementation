/*
 *
 * Red Black Tree Reimplementation
 * Author: Alec Xu
 * Last Motified: July 23, 2020
 * 
 * RBT.h
 * Class Header and Declaration
 * 
 */

#ifndef RBT_H_
#define RBT_H_

//define the color options for each node
enum Colors {RED, BLACK};

template<typename ElemType>
class RBT
{
        public:
                //Constructor
                RBT();
                //Destructor
                ~RBT();
                //Copy Constructor
                RBT(const RBT &rhs);
                //Assignment Operator
                RBT &operator=(const RBT &rhs);
                //checks if an element is stored in the BST 
                bool contains(ElemType element);
                //inserts an element
                void insert(ElemType element);
                //removes an element
                void remove(ElemType element);
                //Checks the height of the tree
                int tree_height();
                //Counts number of nodes
                int node_count();
                //Returns total value stored in the tree
                int count_total();
                //prints values stored in the BST
                void print_tree();
        private:

                //struct to store node information
                struct Node 
                {
                        ElemType data;
                        int count;
                        Colors color;
                        Node *left;
                        Node *right;
                        Node *parent;
                };
                //root of the RBT
                Node *root;
                //creates a deep copy of a tree
                Node *copy_tree(Node *node);
                //removes all nodes from a tree
                void delete_tree(Node *node);
                //creates and allocates memory for a new node
                Node *new_node(ElemType element);
                //balances a tree to satisfy invariants
                void balance_tree(Node *node);
                //Updates color if there is a right sibling to the current node's parent
                Node *left_uncle(Node *node);
                //Updates color if there is a left sibling to the current node's parent
                Node *right_uncle(Node *node);
                //rotates the current node rightward to maintain RBT invariants
                void right_rotate(Node *node);
                //rotates the current node leftward to maintain RBT invariants
                void left_rotate(Node *node);
                //swaps the position of two nodes
                void rb_swap(Node *x, Node *y);
                //removes an element from the tree starting at the passed in node
                void remove_helper(Node *node, ElemType element);
                //finds the minimum node stored in a subtree
                Node *min_node(Node *node);
                //balances tree by updating color to maintain RBT invariants after deletion
                void balance_after_delete(Node *node);
                //checks if an element is stored in an AVL
                bool contains_recur(Node *node, ElemType element);
                //finds the height of a tree starting at the passed in node
                int tree_height_recur(Node *node);
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