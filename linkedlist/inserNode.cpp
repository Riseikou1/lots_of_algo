#include <iostream>
using namespace std;

class Node{
public :
    int data;
    Node* next;
    Node(int val){
        data = val;
        next = nullptr;
    }
};

class LinkedList{
public :
    Node* head;
    LinkedList(){
        head = nullptr;
    }
};

void deleteNodeByValue(Node*& head,int value){
    if(!head) return ;  // if the list is empty.

    // If the head node itself holds the value to be deleted.
    if(head -> data == value){
        Node* temp = head;
        head = head -> next;
        delete temp;
        return ;
    }
    // Search for the key to be deleted.
    Node* current = head;
    while(current->next && current->next->data != value){
        current = current -> next;
    }
    if(!current->next) return ;  // If the key wasn't found.

    Node* temp = current -> next;
    current -> next = current->next->next;
    delete temp;
}
void deleteNodeByPosition(Node*& head, int position){
    if(!head || position < 1) return;
    Node* temp = head;
    if(position==1){
        head = head-> next;
        delete temp;
        return ;
    }
    Node* prev= head;
    for(int i=1;i<position-1;i++){
        if(!prev->next) return;
        prev = prev ->next;
    }
    if(!prev->next) return;
    temp = prev->next;
    prev->next = temp->next;
    delete temp;

}

void traverseAndPrint(Node* head){
    Node* currentNode = head;
    while(currentNode != nullptr){
        cout << currentNode -> data << "-> ";
        currentNode = currentNode -> next;
    }
    cout << "null" << endl;
}

Node* insertNodeAtPosition(Node* head,Node* newNode,int position){
    if(position==1){
        newNode -> next = head;
        return newNode;
    }
    Node* currentNode = head;
    for(int i=1;i<position-1;++i){
        if(currentNode == nullptr){
            break;
        }
        currentNode = currentNode -> next;
    }
    newNode -> next = currentNode -> next;
    currentNode -> next = newNode;
    return head;
    
}

int main(){
    Node* head = new Node(7);
    head -> next= new Node(3);
    head ->next ->next = new Node(2);
    head ->next ->next -> next = new Node(9);

    cout << "Original List:" << endl;
    traverseAndPrint(head);

    Node* newNode = new Node(100);
    head = insertNodeAtPosition(head,newNode,2);

    cout << "After insertion: " << endl;
    traverseAndPrint(head);

    cout<< "After deleting node at position 2:" << endl;
    deleteNodeByPosition(head,2);
    traverseAndPrint(head);
    return 0;
}