/// @file prqueue.h
/// @author Ahmik Ruben Nallamala
/// @date October 20, 2023
/// Description: This file creates a custom binary search
/// that creates a priority queue based on priority values
/// and updates the queue of people based on lowest priority.


#pragma once

#include <iostream>
#include <sstream>
#include <set>

using namespace std;

template<typename T>
class prqueue {
private:
    struct NODE {
        int priority;  // Used to build the Binary Search Tree (BST)
        T value;       // Stored data for the priority queue
        bool dup;      // Marked true when there are duplicate priorities
        NODE* parent;  // Links back to the parent
        NODE* link;    // Links to a linked list of NODEs with duplicate priorities
        NODE* left;    // Links to the left child
        NODE* right;   // Links to the right child
    };

    // Helper function to compare two linked lists for equality
    bool areLinkedListsEqual(NODE* list1, NODE* list2) const {
        // Traverse both linked lists and compare their nodes
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->priority != list2->priority || list1->value != list2->value) {
                return false; // Nodes in linked lists are not equal
            }
            list1 = list1->link;
            list2 = list2->link;
        }
        
        // If one of the linked lists is not empty and the other is, they are not equal
        return list1 == nullptr && list2 == nullptr;
    }

    // Helper function for converting the prqueue to a string
 void _toStringRecursive(NODE* node, ostream& output) {
        if (node) {
            _toStringRecursive(node->left, output);

            // Format and append the node information to the output stream
            output << node->priority << " value: " << node->value << endl;
            if (node->link) {
                // If there are duplicate priorities, traverse the linked list
                NODE* current = node->link;
                while (current) {
                    output << current->priority << " value: " << current->value << endl;
                    current = current->link;
                }
            }

            _toStringRecursive(node->right, output);
        }
 }


    // Helper function to create a deep copy of a BST
    NODE* copyTree(NODE* otherNode) {
        if (otherNode == nullptr) {
            return nullptr;
        }

        NODE* newNode = new NODE;
        newNode->priority = otherNode->priority;
        newNode->value = otherNode->value;
        newNode->dup = otherNode->dup;
        newNode->parent = nullptr;
        newNode->link = copyLinkedList(otherNode->link);  // Copy the linked list
        newNode->left = copyTree(otherNode->left);        // Recursively copy left subtree
        newNode->right = copyTree(otherNode->right);      // Recursively copy right subtree

        // Update parent pointers (if not null)
        if (newNode->left) {
            newNode->left->parent = newNode;
        }
        if (newNode->right) {
            newNode->right->parent = newNode;
        }

        return newNode;
    }

    // Helper function to create a deep copy of a linked list
    NODE* copyLinkedList(NODE* otherHead) {
        NODE* newHead = nullptr;
        NODE* current = nullptr;

        while (otherHead) {
            NODE* newNode = new NODE;
            newNode->priority = otherHead->priority;
            newNode->value = otherHead->value;
            newNode->dup = otherHead->dup;
            newNode->parent = nullptr;
            newNode->link = nullptr;
            newNode->left = nullptr;
            newNode->right = nullptr;

            if (current) {
                current->link = newNode;
                newNode->parent = current;
                current = newNode;
            } else {
                newHead = newNode;
                current = newNode;
            }

            otherHead = otherHead->link;
        }

        return newHead;
    }

    // Function to clear the tree and free memory
    void clearTree(NODE* node) {
        if (node) {
            clearTree(node->left);
            clearTree(node->right);
          
            if (node->link) {
                NODE* current = node->link;
                while (current) {
                    NODE* temp = current;
                    current = current->link;
                    delete temp;
                }
            }
            
            delete node;
        }
    }

    // Helper function to compare two BSTs for equality
    bool areTreesEqual(NODE* node1, NODE* node2) const {
        if (node1 == nullptr && node2 == nullptr) {
            return true; // Both trees are empty or have reached the end
        }
        if (node1 != nullptr && node2 != nullptr) {
            // Check if priorities and values are equal
            if (node1->priority == node2->priority && node1->value == node2->value) {
                // Recursively compare left and right subtrees
                bool leftSubtreeEqual = areTreesEqual(node1->left, node2->left);
                bool rightSubtreeEqual = areTreesEqual(node1->right, node2->right);

                // Check if linked lists are equal
                bool linkedListsEqual = areLinkedListsEqual(node1->link, node2->link);

                // Return true only if both subtrees and linked lists are equal
                return leftSubtreeEqual && rightSubtreeEqual && linkedListsEqual;
            }
        }
        // If any of the above conditions doesn't hold, the trees are not equal
        return false;
    }

    NODE* root; // Pointer to root node of the BST
    int sz;     // Number of elements in the prqueue
    NODE* curr; // Pointer to the next item in prqueue (used for traversal)

public:
    // Default constructor
    prqueue() : root(nullptr), sz(0), curr(nullptr) {
        // Initialize the private members:
        // - `root` is set to nullptr, indicating an empty tree.
        // - `sz` is set to 0, indicating that there are no elements in the priority queue.
        // - `curr` is set to nullptr, as there's no current item in the queue.
    }

    // Assignment operator
    prqueue& operator=(const prqueue& other) {
        // Step 1: Check for self-assignment
        if (this == &other) {
            return *this;  // Return the current object if self-assignment
        }

        // Step 2: Clear the current object
        clear();

        // Step 3: Make a deep copy of the 'other' priority queue
        if (other.root) {
            root = copyTree(other.root); // Create a deep copy of the other tree
        }
        sz = other.sz;
        curr = nullptr; // Reset the 'curr' pointer

        return *this;
    }

    // Clear function to free memory associated with the priority queue
    void clear() {
        clearTree(root);
        root = nullptr;
        sz = 0;
        curr = nullptr;
    }

    // Destructor to free the memory associated with the priority queue
    ~prqueue() {
        clear();
    }

    // Enqueue: Inserts the value into the custom BST in the correct location based on priority
void enqueue(T value, int priority){
   // Create a new node to hold the provided value and priority
   NODE* newNode = new NODE();
   newNode->value = value; 
   newNode->priority = priority; 
   newNode->dup = false; 
   newNode->parent = nullptr; 
   newNode->link = nullptr; 
   newNode->left = nullptr; 
   newNode->right = nullptr; 

   // If the tree is empty, set the new node as the root and update the size (sz)
   if (root == nullptr){
       root = newNode;
       sz = 1;
       return;
   }



   // Initialize pointers for traversal
   NODE* beforeNode = nullptr;
   NODE* present = root;

   // Traverse the tree to find the appropriate location for the new node
   while (present){

       beforeNode = present;

       if (priority < present->priority){

           present = present->left;
       }
       else if (priority > present->priority){

           present = present->right;
       } else {
           // If a node with the same priority is found, mark the new node as a duplicate
           newNode->dup = true;
           // Traverse the linked list of nodes with the same priority and add the new node at the end
           while(present->link) {
               present = present->link;
           }
           present->link = newNode;

           newNode->link = nullptr;

           newNode->parent = present;

           sz++; // Update the size of the priority queue
           return;
       }
   }

   // Insert the new node as the left or right child of the previous node based on priority
   if (priority < beforeNode->priority) {
       beforeNode->left = newNode;

   } 
   else {
       beforeNode->right = newNode;
   }

   // Set the parent of the new node
   newNode->parent = beforeNode;
   // Update the size of the priority queue
   sz++;
}



    // Dequeue: Returns the value of the next element in the priority queue and removes it
    T dequeue() {
        if (!root) {
            return {};
        }

        NODE* current = root;
        NODE* parent = nullptr;

        // Traverse to the leftmost (lowest priority) leaf node
        while (current->left) {
            parent = current;
            current = current->left;
        }

        // Retrieve the value 
        T value = current->value;

        // Remove the lowest-priority element
        if (current->link) {
            NODE* replaceNode = current->link;
            if (parent) {
                parent->left = replaceNode;
            } else {
                root = replaceNode;
            }
            replaceNode->left = current->left;
            replaceNode->right = current->right;
            replaceNode->parent = parent;
        } else {
            // If there's no linked node
            if (parent) {
                // Otherwise, update the parent's left child to the right child of the current node
                parent->left = current->right;
            } else {
                // Root case to replace root if it is the next to get dequeued
                root = current->right;
            }
            if (current->right) {
                // Set the right path with the parent that lost its other child
                current->right->parent = parent;
            }
        }

        delete current;

        // Decrease the size of the priority queue
        sz--;

        return value;
    }

    // Size: Returns the number of elements in the priority queue
    int size() {
        return sz;
    }

    // Begin: Resets internal state for an inorder traversal
    void begin() {
        if (root == nullptr) {
            curr = nullptr; // The tree is empty, so no elements to traverse
            return;
        }

        // Find the leftmost (smallest priority) node to start the traversal
        curr = root;
        while (curr->left != nullptr) {
            curr = curr->left;
        }
    }

    // Next: Uses the internal state to return the next inorder priority
bool next(T& value, int& priority) {
    if (curr == nullptr) {
        return false; // Internal state has reached null, indicating the end of traversal
    }

    value = curr->value;
    priority = curr->priority;
    // Check for duplicates and move to the next linked list node
    if (curr->link) {
        curr = curr->link; // Move to the next node in the linked list of duplicates

    } else if (curr->right != nullptr){
        // If there's a right subtree, go to the right child
        curr = curr->right;
        while (curr->left != nullptr) {
            curr = curr->left;
        }
    } else{

    
    while (curr->dup == true){
        curr = curr->parent;
    }
    // Find the next inorder node (successor) in the BST
    if (curr->right != nullptr) {
        // If there's a right subtree, go to the right child
        curr = curr->right;
        while (curr->left != nullptr) {
            curr = curr->left;
        }
    } else {
        // If there's no right subtree, move up to the parent until we reach a node that hasn't been traversed

        while ( curr->parent != nullptr && curr->parent->priority < priority) {
            curr = curr->parent;
        }
        curr = curr->parent;
    }

    // Retrieve the value and priority from the current node


    }
    if (curr == nullptr){
        return false;
    }

    return  true; // Return true, indicating that a value and priority were successfully returned
}


    // toString: Returns a string representation of the entire priority queue
string toString() {
    ostringstream oss;  // Create a stringstream to build the result
    _toStringRecursive(root, oss);  // Start the recursive traversal
    return oss.str();  // Convert the stringstream to a string and return it
}


    // Peek: Returns the value of the next element in the priority queue without removing it
    T peek() {
        T value;
        int priority;

        // Start at the root
        NODE* current = root;

        // Traverse to the leftmost (lowest priority) leaf node
        while (current->left != nullptr) {
            current = current->left;
        }

        value = current->value;

        return value;
    }

    // Equality operator: Compares two priority queues for equality
    bool operator==(const prqueue& other) const {
        // Check if the sizes are different
        if (sz != other.sz) {
            return false;
        }

        // Recursively compare the content of both BSTs
        return areTreesEqual(root, other.root);
    }

    // getRoot - Used for testing the BST, do not edit/change
    void* getRoot() {
        return root;
    }
};



