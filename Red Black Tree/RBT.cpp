/*
 *
 * Red Black Tree Reimplementation
 * Author: Alec Xu
 * Last Motified: July 23, 2020
 * 
 * RBT.cpp
 * Full function declaration
 * 
 */

#include "RBT.h"
#include <iostream>
#include <stack>
#include <queue>
#include <limits>

using namespace std;

//default constructor
//Parameters: Nothing
//Returns: Nothing
//Does: Initializes an instance of the Class
template<typename ElemType>
RBT<ElemType>::RBT()
{
        root = nullptr;
}

//destructor
//Parameters: Nothing
//Returns: Nothing
//Does: Deletes all dynamically allocated memory
template<typename ElemType>
RBT<ElemType>::~RBT()
{
        delete_tree(root);
}

//copy constructor
//Parameters: const RBT &rhs, the already initialized instance
//            of the RBT class that is being copied 
//Returns: Nothing
//Does: Takes in an instance of the RBT class and makes a 
//      deep copy of the instance 
template<typename ElemType>
RBT<ElemType>::RBT(const RBT &rhs)
{
        root = copy_tree(rhs.root);
}

//assignment operator
//Parameters: const RBT &rhs, the tree that is being copied 
//            into the current instance
//Returns: RBT<ElemType>, the object that copied all data
//         from the source passed into the function
//Does: Copes the tree passed into the function into the
//      current instance of the class
template<typename ElemType>
RBT<ElemType> &RBT<ElemType>::operator=(const RBT &rhs)
{
        if (this != &rhs)
        {
                delete_tree(root);
                root = copy_tree(rhs.root);
        }
        return *this;
}

//delete_tree function
//Parameters: Node *node, the starting node of the tree
//                        being deleted
//Returns: Nothing
//Does: Using a post-order traversal, deletes all nodes 
//      stored in the tree
template<typename ElemType>
void RBT<ElemType>::delete_tree(Node *node)
{
        if (node == nullptr)
        {
                return;
        }
        delete_tree(node->left);
        delete_tree(node->right);
        delete node;
}

//copy_tree function
//Parameters: Node *node, the current node being manipulated
//            and copied to the new tree
//Returns: Node, returns node to the beginning of the tree being 
//         copied
//Does: Makes a deep copy of the tree beginning at the passed in
//      node
template<typename ElemType>
typename RBT<ElemType>::Node *RBT<ElemType>::copy_tree(Node *node)
{
        if (node != nullptr)
        {
                Node *temp_node;
                temp_node = new Node();
                temp_node->data = node->data;
                temp_node->count = node->count;
                temp_node->parent = node->parent;
                temp_node->left = copy_tree(node->left);
                temp_node->right = copy_tree(node->right);
        }
        return node;
}

//insert function
//Parameters: ElemType element, element being added to the object
//Returns: Nothing
//Does: Inserts an element into the tree
template<typename ElemType>
void RBT<ElemType>::insert(ElemType element)
{       
        Node *node = new_node(element);
	Node *temp = nullptr;
        Node *node_root = this->root;
        while (node_root != nullptr) {
                temp = node_root;
                if (node->data < node_root->data) {
                        node_root = node_root->left;
                } 
                else {
                        node_root = node_root->right;
                }
        }
        node->parent = temp;
        if (temp == nullptr) {
                root = node;
        } else if (node->data < temp->data) {
                temp->left = node;
        } else if (node->data > temp->data) {
                temp->right = node;
        } else {
                temp->count++;
        }
        if (node->parent == nullptr){
                node->color = BLACK;
                return;
        }
        if (node->parent->parent == nullptr) {
                return;
        }
        balance_tree(node);
}

//right_rotate function
//Parameters: Node *node - the root of the RBT subtree
//Returns: Node - the root of the balanced subtree
//Does: Performs a right rotation of the subtree starting at the passed
//      in node
template<typename ElemType>
void RBT<ElemType>::right_rotate(Node *node)
{
        Node *left_node = node->left;
        node->left = left_node->right;
        if (left_node->right != nullptr) {
                left_node->right->parent = node;
        }
        left_node->parent = node->parent;
        if (node->parent == nullptr) {
                this->root = left_node;
        } else if (node == node->parent->right) {
                node->parent->right = left_node;
        } else {
                node->parent->left = left_node;
        }
        left_node->right = node;
        node->parent = left_node;
}

//left_rotate function
//Paramters: Node *node - the root of the RBT subtree
//Returns: Node - the root of the balanced subtree
//Does: Performs a right rotation of the subtree starting at the passed
//      int node
template<typename ElemType>
void RBT<ElemType>::left_rotate(Node *node)
{
        Node *right_node = node->right;
        node->right = right_node->left;
        if (right_node->left != nullptr) {
                right_node->left->parent = node;
        }
        right_node->parent = node->parent;
        if (node->parent == nullptr) {
                this->root = right_node;
        } else if (node == node->parent->left) {
                node->parent->left = right_node;
        } else {
                node->parent->right = right_node;
        }
        right_node->left = node;
        node->parent = right_node;
}

//balance_tree function
//Parameters: Node *node - the root of the RBT subtree
//Returns: Nothing
//Does: Balances the tree after insertion 
template<typename ElemType>
void RBT<ElemType>::balance_tree(Node *node)
{
        while (node->parent->color == RED) {
                if (node->parent == node->parent->parent->right) {
                        node = left_uncle(node);
                } else {
                        node = right_uncle(node);
                }
                if (node == root) {
                        break;
                }
        }
        root->color = BLACK;
}

//left_uncle function
//Parameters: Node *node - the root of the RBT subtree
//Returns: Node - the new root of the passed in subtree
//Does: Changes and updates RED/BLACK colors for subtree
template<typename ElemType>
typename RBT<ElemType>::Node *RBT<ElemType>::left_uncle(Node *node)
{
        Node *temp;
        temp = node->parent->parent->left;
        if (temp != nullptr) {
                if (temp->color == RED) {
                        temp->color = BLACK;
                        node->parent->color = BLACK;
                        node->parent->parent->color = RED;
                        node = node->parent->parent;
                } else {
                        if (node == node->parent->left) {
                                node = node->parent;
                                right_rotate(node);
                        }
                        node->parent->color = BLACK;
                        node->parent->parent->color = RED;
                        left_rotate(node->parent->parent);
                }
        } else {
                if (node == node->parent->left) {
                        node = node->parent;
                        right_rotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                left_rotate(node->parent->parent);
        }
        return node;
}

//right_uncle function
//Parameters: Node *node - the root of the RBT subtree
//Returns: Node 0 the new root of the passed in subtree
//Does: Changes and updates RED/BLACK colors for subtree
template<typename ElemType>
typename RBT<ElemType>::Node *RBT<ElemType>::right_uncle(Node *node)
{
        Node *temp;
        temp = node->parent->parent->right;
        if (temp != nullptr ) {
                if (temp->color == BLACK) {
                        if (node == node->parent->right) {
                                node = node->parent;
                                left_rotate(node);
                        }
                        node->parent->color = BLACK;
                        node->parent->parent->color = RED;
                        right_rotate(node->parent->parent);
                } else {
                        temp->color = BLACK;
                        node->parent->color = BLACK;
                        node->parent->parent->color = RED;
                        node = node->parent->parent;	
                }
        } else {
                if (node == node->parent->right) {
                        node = node->parent;
                        left_rotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                right_rotate(node->parent->parent);
        }
        return node;
}

//rbSwap function
//Parameters: Node *x, Node *y - the nodes that are being swapped
//Returns: Nothing
//Does: Swap the passed in element's location within the RBT
template<typename ElemType>
void RBT<ElemType>::rb_swap(Node *x, Node *y)
{
        if (x->parent == nullptr) {
                root = y;
        } else if (x == x->parent->left){
                x->parent->left = y;
        } else {
                x->parent->right = y;
        }
        if (y != nullptr)
        {
                y->parent = x->parent;
        }
}

//remove function
//Parameters: ElemType element - element being removed from the tree
//Returns: Nothing
//Does: Removes an element from the RBT 
template<typename ElemType>
void RBT<ElemType>::remove(ElemType element)
{
        remove_helper(root, element);
}

//remove_helper function
//Parameters: Node *node - the root of the RBT subtree
//            ElemType element - the value being deleted from the tree
//Returns: Nothing
//Does: Finds and removes and element from the RBT
template<typename ElemType>
void RBT<ElemType>::remove_helper(Node *node, ElemType element)
{
        Node *elem_node = nullptr;
        Node *new_root, *temp_node;
        while (node != nullptr){
                if (node->data == element) {
                        if (node->count > 1) {
                                node->count--;
                                return;
                        }
                        elem_node = node;
                }
                if (node->data <= element) {
                        node = node->right;
                } else {
                        node = node->left;
                }
        }
        if (elem_node == nullptr) {
                return;
        } 
        temp_node = elem_node;
        Colors temp_node_original_color = temp_node->color;
        if (elem_node->left == nullptr) {
                new_root = elem_node->right;
                rb_swap(elem_node, elem_node->right);
        } else if (elem_node->right == nullptr) {
                new_root = elem_node->left;
                rb_swap(elem_node, elem_node->left);
        } else {
                temp_node = min_node(elem_node->right);
                temp_node_original_color = temp_node->color;
                new_root = temp_node->right;
                if (temp_node->parent == elem_node) {
                        new_root->parent = temp_node;
                } else {
                        rb_swap(temp_node, temp_node->right);
                        temp_node->right = elem_node->right;
                        temp_node->right->parent = temp_node;
                }

                rb_swap(elem_node, temp_node);
                temp_node->left = elem_node->left;
                temp_node->left->parent = temp_node;
                temp_node->color = elem_node->color;
        }
        delete elem_node;
        if (temp_node_original_color == RED){
                if (new_root != nullptr) {
                        balance_after_delete(new_root);
                }
        }
}

//balance_after_delete function
//Parameters: Node *node - the root of the subtree
//Returns: Nothing
//Does: Changes and updates the RED/BLACK color of each node 
//      in order to maintain invariants
template<typename ElemType>
void RBT<ElemType>::balance_after_delete(Node *node)
{
        Node *temp;
        while (node != root && node->color == RED) {
                if (node == node->parent->left) {
                        temp = node->parent->right;
                        if (temp->color == BLACK) {
                                temp->color = RED;
                                node->parent->color = BLACK;
                                left_rotate(node->parent);
                                temp = node->parent->right;
                        }

                        if (temp->left->color == RED && temp->right->color == RED) {
                                temp->color = BLACK;
                                node = node->parent;
                        } else {
                                if (temp->right->color == RED) {
                                        temp->left->color = RED;
                                        temp->color = BLACK;
                                        right_rotate(temp);
                                        temp = node->parent->right;
                                } 
                                temp->color = node->parent->color;
                                node->parent->color = RED;
                                temp->right->color = RED;
                                left_rotate(node->parent);
                                node = root;
                        }
                } else {
                        temp = node->parent->left;
                        if (temp->color == BLACK) {
                                temp->color = RED;
                                node->parent->color = BLACK;
                                right_rotate(node->parent);
                                temp = node->parent->left;
                        }

                        if (temp->right->color == RED && temp->right->color == RED) {
                                temp->color = BLACK;
                                node = node->parent;
                        } else {
                                if (temp->left->color == RED) {
                                        temp->right->color = RED;
                                        temp->color = BLACK;
                                        left_rotate(temp);
                                        temp = node->parent->left;
                                } 
                                temp->color = node->parent->color;
                                node->parent->color = RED;
                                temp->left->color = RED;
                                right_rotate(node->parent);
                                node = root;
                        }
                } 
        }
        node->color = RED;
}

//min_node function
//Parameters: Node *node - the root of the subtree being passed in 
//Returns: Node - the node of the minimum value
//Does: Given the root of a subtree, function returns the node containing the value
template<typename ElemType>
typename RBT<ElemType>::Node *RBT<ElemType>::min_node(Node *node)
{
        while (node->left != nullptr) {
                node = node->left;
        }
        return node;
}

//new_node function
//Parameters: ElemType element - value stored in the new node
//Returns: Node - a new node being created
//Does: Allocates memory for a new node, initializes values, and returns new node
template<typename ElemType>
typename RBT<ElemType>::Node *RBT<ElemType>::new_node(ElemType element)
{
        Node *temp_node = new Node();
        temp_node->data = element;
        temp_node->color = RED;
        temp_node->count = 1;
        temp_node->left = nullptr;
        temp_node->right = nullptr;
        temp_node->parent = nullptr;
        return temp_node;
}

//contains function 
//Paramters: ElemType element - the value being checked for
//Returns: bool - whether or not the value is stored in the tree
//Does: Checks if a passed in value is stored within the tree 
template<typename ElemType>
bool RBT<ElemType>::contains(ElemType element)
{
        return contains_recur(root, element);
}

//contains_recur Function
//Parameters: Node *node - the root of the current tree being checked 
//            ElemType element - the value being checked for 
//Returns: bool - whether or not the value is stored in the tree 
//Does: Checks, recursively, if a value is stored in the tree 
template<typename ElemType>
bool RBT<ElemType>::contains_recur(Node *node, ElemType element)
{
        if (node == nullptr) 
        {
                return false;
        }
        if (node->data == element) 
        {
                return true;
        }
        if (node->data < element)
        {
                return contains_recur(node->left, element);
        }
        return contains_recur(node->right, element);
}

//tree_height Function 
//Parameters: Nothing 
//Returns: Int - the height of the tree
//Does: Searches for and returns the height of the RBT Tree
template<typename ElemType>
int RBT<ElemType>::tree_height()
{
        return tree_height_recur(root);
}

//tree_height_recur Function
//Parameters: Node *node - the root of the tree currently being manipulated
//Returns: Int - the height of the current tree
//Does: Checks and returns the height of the current tree
template<typename ElemType>
int RBT<ElemType>::tree_height_recur(Node *node)
{
        if (root == nullptr)
        {
                return -1;
        }
        else if (node == nullptr)
        {
                return 0;
        }
        else if (is_a_leaf(node))
        {
                return 0;
        }
        int left_max = tree_height_recur(node->left);
        int right_max = tree_height_recur(node->right);
        if (left_max > right_max) 
        {
                return left_max + 1;
        }
        return right_max + 1;
}

//node_count Function 
//Parameters: Nothing 
//Returns: Int - total node count
//Does: Returns the total amount of nodes in a tree
template<typename ElemType>
int RBT<ElemType>::node_count()
{
        return node_count_recur(root);
}

//node_count_recur Function
//Parameters: Node *node - the root of the tree currently being checked
//Returns: Int - the number of nodes in the current tree
//Does: Checks for the number of nodes in the tree starting at the
//      passed in node 
template<typename ElemType>
int RBT<ElemType>::node_count_recur(Node *node)
{
        int total_count = 0;
        if (node == nullptr)
        {
                return 0;
        }
        total_count += node_count_recur(node->left);
        total_count += node_count_recur(node->right);
        return total_count + 1;
}

//count_total Function 
//Parameters: Nothing 
//Returns: int - total value of all nodes
//Does: Returns the sum of all the node values (including duplicates)
template<typename ElemType>
int RBT<ElemType>::count_total()
{
        return count_total_recur(root);
}

//count_tatal_recur Function (private)
//Parameters: Node *node - the root of the current tree being checked
//Returns: Int - sum of all values in current tree
//Does: Returns the sum of all the node values (including duplicates)
//      in the tree starting at the passed in node
template<typename ElemType>
int RBT<ElemType>::count_total_recur(Node *node)
{
        if (node == nullptr)
        {
                return 0;
        }
        if (node->count > 1)
        {
                return ((node->count)*(node->data) + count_total_recur(node->left) +
                        count_total_recur(node->right));
        }
        return (node->data + count_total_recur(node->left) + count_total_recur(node->right));
}

//print_tree function
//Parameters: Nothing
//Returns: Nothing
//Does: prints all elements within the tree (uncomment the type 
//      of traversal used)
template<typename ElemType>
void RBT<ElemType>::print_tree()
{
        //Uncomment the type of traversal wanted:
        // in_order_print(root);
        // pre_order_print(root);
        level_order_print(root);
        cout << endl;
}

//in_order_print function
//Parameters: Node *root, the root of the tree 
//Returns: Nothing
//Does: Prints the contents of the tree using
//      an in-order traversal
template<typename ElemType>
void RBT<ElemType>::in_order_print(Node *root)
{
        if (root == nullptr)
        {
                return;
        }
        in_order_print(root->left);
        cout << root->data << " ";
        in_order_print(root->right);
}

//pre_prder_print function
//Parameters: Node *root, the root of the tree
//Returns: Nothing
//Does: Prints the contents of the tree using
//      a pre-order traversal
template<typename ElemType>
void RBT<ElemType>::pre_order_print(Node *root)
{
        stack<Node *> list;
        if (root != nullptr){
                list.push(root);
                while (!list.empty()) {
                        Node *curr = list.top();
                        cout << curr->data << " ";
                        list.pop();
                        if (curr->right != nullptr) {
                                list.push(curr->right);
                        }
                        if (curr->left != nullptr) {
                                list.push(curr->left);
                }
        }
        }
}

//level_order_print function
//Parameters: Node *root, the root of the tree
//Returns: Nothing
//Does: Prints the contents of the tree using 
//      a level-order traversal
template<typename ElemType>
void RBT<ElemType>::level_order_print(Node *root)
{
        queue<Node *> list;
        if (root != nullptr) 
        {
                list.push(root);
        }
        while (!list.empty()) 
        {
                cout << list.front()->data << " " << list.front()->color << " ";
                if (list.front()->left != nullptr) 
                {
                        list.push(list.front()->left);
                }
                if (list.front()->right != nullptr) 
                {
                        list.push(list.front()->right);
                }
                list.pop();
        }
}