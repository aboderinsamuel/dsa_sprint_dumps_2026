//leetcod 430 : flatten a multilevel doubly linked list

//use iterative traversal using a stack.
//IT avoids recursion and handles the multilevel structure 
//efficiently.
//the way it works simple step by step is:

//1. Initialize a stack and push the head of the list onto it.
//2. While the stack is not empty, pop a node from the stack.
//3. If the popped node has a next pointer, push the next node onto the stack.
//4. If the popped node has a child pointer, push the child node onto the stack.
//5. Connect the popped node to the previous node in the flattened list.
//6. Repeat steps 2-5 until the stack is empty.

#include <stack>
using namespace std;

//Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
class Solution{
public:
    Node* flatten(Node* head){
        if(!head) return nullptr;
        stack<Node*> nodeStack;
        nodeStack.push(head);
        Node* dummy = new Node(); // create a dummy node to simplify the connection process
        Node* prev = dummy; // previous node in the flattened list

        while(!nodeStack.empty()){
            Node* curr = nodeStack.top();
            nodeStack.pop();

            prev->next = curr; // connect the previous node to the current node
            curr->prev = prev; // connect the current node back to the previous node

            // if the current node has a next pointer, push it onto the stack
            if(curr->next){
                nodeStack.push(curr->next); // push the next node onto the stack
            }
            // if the current node has a child, push it onto the stack and remove the child pointer
            if(curr->child){
                nodeStack.push(curr->child); // push the child node onto the stack
                curr->child = nullptr; // remove the child pointer after pushing it onto the stack
            }
            prev = curr; // move the previous pointer to the current node
        }
        Node* flattenedHead = dummy->next; // the head of the flattened list is the next of the dummy node
        flattenedHead->prev = nullptr; // set the prev of the head to nullptr
        delete dummy; // free the memory of the dummy node
        return flattenedHead; // return the head of the flattened list
    }
};