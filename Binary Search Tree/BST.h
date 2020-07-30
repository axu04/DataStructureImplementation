/*
 *
 * Binary Search Tree Reimplementation
 * Author: Alec Xu
 * Last Motified: Jul 19, 2020
 * 
 * BST.h
 * Class Header and Declaration
 * 
 */

#ifndef BST_H_
#define BST_H_

template<typename ElemType>
class BST
{
        public:
                //Constructor
                BST();
                //Destructor
                ~BST();
                //Copy Constructor
                BST(const BST &rhs);
                //Assignment Operator
                BST &operator=(const BST &rhs);
                //checks if an element is stored in the BST 
                bool contains(ElemType element);
                //inserts an element
                void insert(ElemType element);
                //removes an element
                bool remove(ElemType element);
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
                        Node *left;
                        Node *right;
                };
                //root of the BST
                Node *root;
                //creates a deep copy of a tree
                Node *copy_tree(Node *node);
                //removes all nodes from a tree
                void delete_tree(Node *node);
                //finds the minimum value stored in a tree
                Node *find_min_recur(Node *node);
                //finds maximum value stored in a tree
                Node *find_max_recur(Node *node);
                //checks if an element is stored in a BST
                bool contains_recur(Node *node, ElemType element);
                //removes element from the current subtree
                bool remove_recur(Node *node, Node *parent, ElemType element);
                //function called when a node is found when removing an element
                void node_found(Node *node, Node *parent, ElemType element);
                //function called when element is a leaf node
                void empty_case(Node *node, Node *parent, ElemType element);
                //function called when left node is empty
                void right_case(Node *node, Node *parent);
                //function called when right node is empty
                void left_case(Node *node, Node *parent);
                //updates values stored in node
                void update(Node *node);
                //finds the height of a tree starting at the passed in node
                int tree_height_recur(Node *node);
                //determines if a node is a leaf 
                bool is_a_leaf(Node *node);
                //counts the number of nodes starting at the passed in node
                int node_count_recur(Node *node);
                //sums to total of all values stored in the tree starting 
                //at the passed in node
                int count_total_recur(Node *node);
                //insert to a specific tree 
                Node *insert_recur(Node *node, ElemType element);
                //in order traversal print
                void in_order_print(Node *root);
                //pre order traversal print
                void pre_order_print(Node *root);
                //level order traversal print
                void level_order_print(Node *root);
                //creates and allocates memory for a new node
                Node *new_node(ElemType info);
};

#endif 