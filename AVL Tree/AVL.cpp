/*
 *
 * AVL Tree Reimplementation
 * Author: Alec Xu
 * Last Motified: July 22, 2020
 * 
 * AVL.cpp
 * Full function declaration
 * 
 */

#include "AVL.h"
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
AVL<ElemType>::AVL()
{
        root = nullptr;
}

//destructor
//Parameters: Nothing
//Returns: Nothing
//Does: Deletes all dynamically allocated memory
template<typename ElemType>
AVL<ElemType>::~AVL()
{
        delete_tree(root);
}

//copy constructor
//Parameters: const AVL &rhs, the already initialized instance
//            of the AVL class that is being copied 
//Returns: Nothing
//Does: Takes in an instance of the AVL class and makes a 
//      deep copy of the instance 
template<typename ElemType>
AVL<ElemType>::AVL(const AVL &rhs)
{
        root = copy_tree(rhs.root);
}

//assignment operator
//Parameters: const AVL &rhs, the tree that is being copied 
//            into the current instance
//Returns: AVL<ElemType>, the object that copied all data
//         from the source passed into the function
//Does: Copes the tree passed into the function into the
//      current instance of the class
template<typename ElemType>
AVL<ElemType> &AVL<ElemType>::operator=(const AVL &rhs)
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
void AVL<ElemType>::delete_tree(Node *node)
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
typename AVL<ElemType>::Node *AVL<ElemType>::copy_tree(Node *node)
{
        if (node != nullptr) 
        {
                Node *temp_node;
                temp_node = new Node();
                temp_node->data = node->data;
                temp_node->count = node->count;
                temp_node->height = node->height;
                temp_node->left = copy_tree(node->left);
                temp_node->right = copy_tree(node->right);
        }
        return node;
}

//contains Function 
//Paramters: ElemType element - the value being checked for
//Returns: bool - whether or not the value is stored in the tree
//Does: Checks if a passed in value is stored within the tree 
template<typename ElemType>
bool AVL<ElemType>::contains(ElemType element)
{
        return contains_recur(root, element);
}

//contains_recur Function (private)
//Parameters: Node *node - the root of the current tree being checked 
//            ElemType element - the value being checked for 
//Returns: bool - whether or not the value is stored in the tree 
//Does: Checks, recursively, if a value is stored in the tree 
template<typename ElemType>
bool AVL<ElemType>::contains_recur(Node *node, ElemType element)
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

//insert Function 
//Parameters: ElemType element - the value that is being stored in the tree 
//Returns: Nothing 
//Does: Inserts an element into the tree 
template<typename ElemType>
void AVL<ElemType>::insert(ElemType element) 
{
        root = insert_recur(root, element);
}

//insert_recur Function (private)
//Parameters: Node *node - the root of the current tree being inserted 
//                         into
//            ElemType element - the value being inserted into the tree
//Returns: Nothing 
//Does: inserts the value into the tree recursively
template<typename ElemType>
typename AVL<ElemType>::Node *AVL<ElemType>::insert_recur(Node *node, ElemType element)
{
        if (node == nullptr)
        {
                return new_node(element, 0, 1, nullptr, nullptr);
        }
        else if (element < node->data)
        {
                node->left = insert_recur(node->left, element);
        }
        else if (element > node->data)
        {
                node->right = insert_recur(node->right, element);
        }
        else
        {
                node->count++;
                return node;
        }
        node->height = 1 + max(node_height(node->left), node_height(node->right));
        node = balance(node);

        return node;
}

//remove function
//Parameters: ElemType element - value being removed from the AVL Tree
//Returns: Nothing
//Does: Removes a passed in element from the tree
template<typename ElemType>
void AVL<ElemType>::remove(ElemType element)
{
        root = remove_recur(root, element);
}

//remove_recur function (Private)
//Parameters: Node *node - the root of the tree being analyzed
//            ElemType element - the element being removed from the tree
//Returns: Node - the new node of the subtree
//Does: Recursively removes the value from the passed in tree
template<typename ElemType>
typename AVL<ElemType>::Node *AVL<ElemType>::remove_recur(Node *node, ElemType element)
{
        if (node == nullptr) 
        {
                return node;
        }
        if (element < node->data)
        {
                node->left = remove_recur(node->left, element);
        } 
        else if (element > node->data)
        {
                node->right = remove_recur(node->right, element);
        }
        else 
        {
                if (node->right == nullptr || node->left == nullptr)
                {
                        Node *temp = node->left ? node->left : node->right;
                        if (temp == nullptr)
                        {
                                temp = node;
                                node = nullptr;
                        }
                        else 
                        {
                                *node = *temp;
                                
                        }
                        delete temp;
                }
                else 
                {
                        Node *temp = find_min_value(node->right);
                        node->data = temp->data;
                        node->right = remove_recur(node->right, temp->data);
                }
        }
        if (node == nullptr)
        {
                return node;
        }
        node->height = 1 + max(node_height(node->left), node_height(node->right));
        node = balance(node);

        return node;
}

//find_min_value function
//Parameters: Node *node - the node being analyzed
//Returns: Node of the minimum value
//Does: Returns the ndoe with the minimum value stored in a particular subtree
template<typename ElemType>
typename AVL<ElemType>::Node *AVL<ElemType>::find_min_value(Node *node)
{
        Node *temp = node;
        while(temp->left != nullptr)
        {
                temp = temp->left;
        }
        return temp;
}

//balance function 
//Parameters: Node *node - root of the tree being analyzed
//Returns: Node - the new root of the tree
//Does: Checks if the current subtree is balanced and balances
//      the tree if necessary
template<typename ElemType>
typename AVL<ElemType>::Node *AVL<ElemType>::balance(Node *node)
{
        if (node == nullptr) { 
                return nullptr;
        }

        int diff = height_diff(node);
        if (diff > 1) { 
                if (height_diff(node->left) > 0) {
                        return right_rotate(node);
                }
                else {
                        node->left = left_rotate(node->left);
                        return right_rotate(node);
                }
        }
        if (diff < -1) { 
                if (height_diff(node->right) < 0) {
                        return left_rotate(node);
                }
                else {
                        node->right = right_rotate(node->right);
                        return left_rotate(node);
                }
        }
        return node;
}

//right_rotate function
//Parameters: Node *node - a node of the AVL tree
//Returns: Node - the root of the balanced subtree
//Does: Performs a right rotation of the subtree starting at node
template<typename ElemType>
typename AVL<ElemType>::Node *AVL<ElemType>::right_rotate(Node *node)
{
        Node *left_node = node->left;
        Node *right_node = left_node->right;

        left_node->right = node;
        node->left = right_node;

        node->height = max(node_height(node->left), node_height(node->right)) + 1;
        left_node->height = max(node_height(left_node->left), 
                                node_height(left_node->right)) + 1;

        return left_node;
}

//left_rotate function
//Parameters: Node *node - a node of the AVL tree
//Returns: Node - the root ofthe balanced subtree
//Does: Performs a left rotation of the subtree starting at node
template<typename ElemType>
typename AVL<ElemType>::Node *AVL<ElemType>::left_rotate(Node *node)
{
        Node *right_node = node->right;
        Node *left_node = right_node->left;

        right_node->left = node;
        node->right = left_node;

        node->height = max(node_height(node->left), node_height(node->right)) + 1;
        right_node->height = max(node_height(right_node->left), 
                                node_height(right_node->right)) + 1;

        return right_node;
}

//height_diff function
//Parameters: Node np - a node of the avl tree.
//Returns: integer value signifying the height difference.
//Does: calculates the difference in the height of the left and child 
//      subtree of np
template<typename ElemType>
int AVL<ElemType>::height_diff(Node *node)
{
        int l_height = node_height(node->left);
        int r_height = node_height(node->right);

        int b_factor= l_height - r_height;
        return b_factor;
}

//new_node function
//Parameters: ElemType element - the value stored at the new node
//            int height - the height of the current node
//            int count - the number of duplicate elements
//            Node *left - the value stored as the left child
//            Node *right - the value stored as the right child
//Returns: Node - the new node created
//Does: Creates a new node in the leaf position of an AVL tree
template<typename ElemType>
typename AVL<ElemType>::Node *AVL<ElemType>::new_node(ElemType element, int height, int count, Node *left, Node *right)
{
        Node *temp_node = new Node();
    
        temp_node->data  = element;
        temp_node->height = height;
        temp_node->count = count;
        temp_node->left  = left;
        temp_node->right = right;

        return temp_node;
}

//node_height function
//Parameters: Node *node - the node currently being analyzed
//Returns: int - the height of the node
//Does: Takes a node and returns the height 
template<typename ElemType>
int AVL<ElemType>::node_height(Node *node)
{
        if (node == nullptr)
        {
                return -1;
        }
        return node->height;
}

//tree_height Function 
//Parameters: Nothing 
//Returns: Int - the height of the tree
//Does: Searches for and returns the height of the AVL Tree
template<typename ElemType>
int AVL<ElemType>::tree_height()
{
        return tree_height_recur(root);
}

//tree_height_recur Function (private)
//Parameters: Node *node - the root of the tree currently being manipulated
//Returns: Int - the height of the current tree
//Does: Checks and returns the height of the current tree
template<typename ElemType>
int AVL<ElemType>::tree_height_recur(Node *node)
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

//is_a_leaf Function 
//Parameters: Node *node - root of the tree currently being checked 
//Returns: bool - whether or not a node is considered to be a leaf 
//                (has no children)
//Does: Returns whether or not a certain node is a leaf or not
template<typename ElemType>
bool AVL<ElemType>::is_a_leaf(Node *node)
{
        if (node == nullptr)
        {
                return false;
        }
        if (node->left == nullptr and node->right == nullptr)
        {
                return true;
        }
        return false;
}

//node_count Function 
//Parameters: Nothing 
//Returns: Int - total node count
//Does: Returns the total amount of nodes in a tree
template<typename ElemType>
int AVL<ElemType>::node_count()
{
        return node_count_recur(root);
}

//node_count_recur Function (private)
//Parameters: Node *node - the root of the tree currently being checked
//Returns: Int - the number of nodes in the current tree
//Does: Checks for the number of nodes in the tree starting at the
//      passed in node 
template<typename ElemType>
int AVL<ElemType>::node_count_recur(Node *node)
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
int AVL<ElemType>::count_total()
{
        return count_total_recur(root);
}

//count_tatal_recur Function (private)
//Parameters: Node *node - the root of the current tree being checked
//Returns: Int - sum of all values in current tree
//Does: Returns the sum of all the node values (including duplicates)
//      in the tree starting at the passed in node
template<typename ElemType>
int AVL<ElemType>::count_total_recur(Node *node)
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
void AVL<ElemType>::print_tree()
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
void AVL<ElemType>::in_order_print(Node *root)
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
void AVL<ElemType>::pre_order_print(Node *root)
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
void AVL<ElemType>::level_order_print(Node *root)
{
        queue<Node *> list;
        if (root != nullptr) 
        {
                list.push(root);
        }
        while (!list.empty()) 
        {
                cout << list.front()->data << " ";
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