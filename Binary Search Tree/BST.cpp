/*
 *
 * Binary Search Tree Reimplementation
 * Author: Alec Xu
 * Last Motified: July 19, 2020
 * 
 * BST.cpp
 * Full function declaration
 * 
 */

#include "BST.h"
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
BST<ElemType>::BST()
{
        root = nullptr;
}

//destructor
//Parameters: Nothing
//Returns: Nothing
//Does: Deletes all dynamically allocated memory
template<typename ElemType>
BST<ElemType>::~BST()
{
        delete_tree(root);
}

//copy constructor
//Parameters: const BST &rhs, the already initialized instance
//            of the BST class that is being copied 
//Returns: Nothing
//Does: Takes in an instance of the BinarySearchTree class and makes a 
//      deep copy of the instance 
template<typename ElemType>
BST<ElemType>::BST(const BST &rhs)
{
        root = copy_tree(rhs.root);
}

//copy_tree function
//Parameters: Node *node, the current node being manipulated
//            and copied to the new tree
//Returns: Node, returns node to the beginning of the tree being 
//         copied
//Does: Makes a deep copy of the tree beginning at the passed in
//      node
template<typename ElemType>
typename BST<ElemType>::Node *BST<ElemType>::copy_tree(Node *node)
{
        if (node != nullptr)
        {
                Node *temp_node;
                temp_node = new Node();
                temp_node->data = node->data;
                temp_node->count = node->count;
                temp_node->left = copy_tree(node->left);
                temp_node->right = copy_tree(node->right);
        }
        return node;
}

//assignment operator
//Parameters: const BST &rhs, the tree that is being copied 
//            into the current instance
//Returns: BST<ElemType>, the object that copied all data
//         from the source passed into the function
//Does: Copes the tree passed into the function into the
//      current instance of the class
template<typename ElemType>
BST<ElemType> &BST<ElemType>::operator=(const BST &rhs)
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
void BST<ElemType>::delete_tree(Node *node)
{
        if (node == nullptr)
        {
                return;
        }
        delete_tree(node->left);
        delete_tree(node->right);
        delete node;
}

//contains Function 
//Paramters: ElemType element - the value being checked for
//Returns: bool - whether or not the value is stored in the tree
//Does: Checks if a passed in value is stored within the tree 
template<typename ElemType>
bool BST<ElemType>::contains(ElemType element) {
        return contains_recur(root, element);
}

//contains Function (private)
//Parameters: Node *node - the root of the current tree being checked 
//            ElemType element - the value being checked for 
//Returns: bool - whether or not the value is stored in the tree 
//Does: Checks, recursively, if a value is stored in the tree 
template<typename ElemType> 
bool BST<ElemType>::contains_recur(Node *node, ElemType element){
        if (node == nullptr) {
                return false;
        }
        if (node->data == element) {
                return true;
        }
        if (node->data < element) {
                return contains_recur(node->right, element);
        }
        return contains_recur(node->left, element);
}

//remove Function 
//Parameters: ElemType value - the integer value that is being removed 
//                        from the tree
//Returns: bool - whether or not the integer was removed from the 
//                binary search tree
//Does: Removes the passed in value from the tree
template<typename ElemType>
bool BST<ElemType>::remove(ElemType element) {
        return remove_recur(root, nullptr, element);
}

//remove_recur Function (private)
//Parameters: Node *node - the root of the current tree being checked 
//            Node *parent - the parent node of the node currently 
//                           being checked (if it is the root of the 
//                           entire tree the parent will be nullptr)
//            ElemType element - the value being removed from the tree 
//Returns: bool - whether or not the node was removed from the tree 
//Does: Removes the passed in value from the tree starting at the passed
//      in node
template<typename ElemType> 
bool BST<ElemType>::remove_recur(Node *node, Node *parent, ElemType element) {
        if (node == nullptr) {
                return false;
        } else if (element < node->data) {
                if (node->left != nullptr) {
                        return remove_recur(node->left, node, element);
                }
        } else if (element > node->data) {
                if (node->right != nullptr) {
                        return remove_recur(node->right, node, element);
                }
        } else {
                node_found(node, parent, element);
                return true;
        }
        return false;
}

//node_found Function 
//Parameters: Node *node - the root of the tree currently being checked 
//            Node *parent - the parent node of the node currently 
//                           being checked (if it is the root of the 
//                           entire tree the parent will be nullptr)
//            int value - the value that is being checked for
//Returns: Nothing 
//Does: Checks 3 different cases if the value is found within the tree 
template<typename ElemType>
void BST<ElemType>::node_found(Node *node, Node *parent, ElemType element) {
        if (node->count > 1) {
                node->count--;
                return;
        }
        if (node->left == nullptr and node->right == nullptr) {
                empty_case(node, parent, element);
        }
        else if (node->left == nullptr and node->right != nullptr) {
                right_case(node, parent);
        }
        else if (node->right == nullptr and node->left !=  nullptr) {
                left_case(node, parent);
        }
        else {
                update(node);
                remove_recur(node->right, node, node->data);
        }
}

//empty_case Function 
//Parameters: Node *node - the root of the tree currently being checked 
//            Node *parent - the parent node of the node currently 
//                           being checked (if it is the root of the 
//                           entire tree the parent will be nullptr)
//            int value - the value that is being checked for
//Returns: Nothing 
//Does: Checks and deletes node if the current node is considered to 
//      be a leaf (meaning it has no children)
template<typename ElemType>
void BST<ElemType>::empty_case(Node *node, Node *parent, ElemType element) {
        if (node == root) {
                delete node;
                root = nullptr;
        }
        else if (parent->left != nullptr and parent->left->data == element) {
                delete node;
                parent->left = nullptr;
        }
        else {
                delete node;
                parent->right = nullptr;
        }
}


//right_case Function 
//Parameters: Node *node - the root of the tree currently being checked 
//            Node *parent - the parent node of the node currently 
//                           being checked (if it is the root of the 
//                           entire tree the parent will be nullptr)
//Returns: Nothing 
//Does: Deletes the node if the parent node only has a right child 
template<typename ElemType>
void BST<ElemType>::right_case(Node *node, Node *parent) {
        Node *temp = node->right;
        delete node;
        parent->left = temp;
}

//left_case Function 
//Parameters: Node *node - the root of the tree currently being checked 
//            Node *parent - the parent node of the node currently 
//                           being checked (if it is the root of the 
//                           entire tree the parent will be nullptr)
//Returns: Nothing 
//Does: Deletes the node if the parent node only has a left child 
template<typename ElemType>
void BST<ElemType>::left_case(Node *node, Node *parent) {
        Node *temp = node->left;
        delete node;
        parent->left = temp;
}

//update Function 
//Parameters: Node *node - the root of the current tree being manipulated 
//Returns: Nothing 
//Does: Updates the values stored in the current node if the current node 
//      has 2 children 
template<typename ElemType>
void BST<ElemType>::update(Node *node) {
        Node *right_min = find_min_recur(node->right);
        node->data = right_min->data;
        node->count = right_min->count;
}

//tree_height Function 
//Parameters: Nothing 
//Returns: Int - the height of the tree
//Does: Searches for and returns the height of the BinarySearchTree
template<typename ElemType>
int BST<ElemType>::tree_height() {
        return tree_height_recur(root);
}

//tree_height_recur Function (private)
//Parameters: Node *node - the root of the tree currently being manipulated
//Returns: Int - the height of the current tree
//Does: Checks and returns the height of the current tree
template<typename ElemType>
int BST<ElemType>::tree_height_recur(Node *node) {
        if (root == nullptr) {
                return -1;
        }
        else if (node == nullptr) {
                return 0;
        }
        else if (is_a_leaf(node)) {
                return 0;
        }
        int left_max = tree_height_recur(node->left);
        int right_max = tree_height_recur(node->right);
        if (left_max > right_max) {
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
bool BST<ElemType>::is_a_leaf(Node *node) {
        if (node == nullptr) {
                return false;
        }
        if (node->left == nullptr and node->right == nullptr) {
                return true;
        } 
        return false;
}

//node_count Function 
//Parameters: Nothing 
//Returns: Int - total node count
//Does: Returns the total amount of nodes in a tree
template<typename ElemType>
int BST<ElemType>::node_count() {
        return node_count_recur(root);
}

//node_count_recur Function (private)
//Parameters: Node *node - the root of the tree currently being checked
//Returns: Int - the number of nodes in the current tree
//Does: Checks for the number of nodes in the tree starting at the
//      passed in node 
template<typename ElemType>
int BST<ElemType>::node_count_recur(Node *node) {
        int total_count = 0;
        if (node == nullptr) {
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
int BST<ElemType>::count_total() {
        return count_total_recur(root);
}

//count_tatal_recur Function (private)
//Parameters: Node *node - the root of the current tree being checked
//Returns: Int - sum of all values in current tree
//Does: Returns the sum of all the node values (including duplicates)
//      in the tree starting at the passed in node
template<typename ElemType>
int BST<ElemType>::count_total_recur(Node *node) {
        if (node == nullptr) {
                return 0;
        }
        if (node->count > 1) {
             return ((node->count)*(node->data) + count_total_recur(node->left) + 
                     count_total_recur(node->right));   
        }
        return (node->data + count_total_recur(node->left) + count_total_recur(node->right));
}

//insert function
//Parameters: ElemType element, element being added to the object
//Returns: Nothing
//Does: Inserts an element into the tree 
template<typename ElemType>
void BST<ElemType>::insert(ElemType element) {
        root = insert_recur(root, element);
}

//insert_recur (private) function
//Parameters: Node *node, the root of the current tree being inserted
//                        into
//            ElemType element, element being added to the BST
//Returns: Node
//Does: Recursively inserts the given element into the BST object
template<typename ElemType>
typename BST<ElemType>::Node *BST<ElemType>::insert_recur(Node *node, 
                                                        ElemType element)
{
      	if (node == nullptr) 
        {
                return new_node(element);
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
        }
        return node;
}

//print_tree function
//Parameters: Nothing
//Returns: Nothing
//Does: prints all elements within the tree (uncomment the type 
//      of traversal used)
template<typename ElemType>
void BST<ElemType>::print_tree()
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
void BST<ElemType>::in_order_print(Node *root)
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
void BST<ElemType>::pre_order_print(Node *root)
{
        stack<Node *> list;
        if (root != nullptr) {
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
void BST<ElemType>::level_order_print(Node *root)
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

//new_node function
//Parameters: ElemType info, value being stored in the node
//Returns: Node, the node that was dynamically created
//Does: Creates a node and stores the passed in data
template<typename ElemType>
typename BST<ElemType>::Node *BST<ElemType>::new_node(ElemType info)
{
        Node *temp = new Node;
        temp->data = info;
        temp->count = 1;
        temp->left = nullptr;
        temp->right = nullptr;
        return temp;
}
