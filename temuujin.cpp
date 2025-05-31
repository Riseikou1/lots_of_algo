#include <iostream>
using namespace std;

class Node{
public :
    int data;
    int height;
    Node* left = nullptr;
    Node* right =nullptr;
    Node(int data ) : data(data){height = 1;}
};

class BinaryTree{
private :
    Node* root; 

    void displayHelper(Node* root){
        if(!root) return ;
        displayHelper(root->left);
        cout << root -> data << " " ;
        displayHelper(root -> right);
    }

    Node* insertHelper(Node* root, Node* node){
        if(root == nullptr){
            return node;
        }
        else if(root->data > node -> data){
            root->left =  insertHelper(root->left, node);
        }
        else{
            root->right =  insertHelper(root->right,node);
        }
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        return balance(root);
    }

    bool searchHelper(Node* root,int data){
        if(!root) return false;
        if(root->data > data){
            return searchHelper(root->left, data);
        }
        else if(root->data < data){
            return searchHelper(root->right,data);
        }
        return data == root -> data;
    }

    Node* deleteHelper(Node* root, int data){
        if(root==nullptr){
            return root;
        }
        if(root->data > data){
            root->left = deleteHelper(root->left, data);
        }
        else if(root->data < data){
            root->right = deleteHelper(root->right,data);
        }
        else {
            if(root->right==nullptr && root->left == nullptr){
                delete root; return nullptr;
            }
            else if(root->right ==nullptr && root->left != nullptr){
                Node* temp = root->left;
                delete root;
                return temp;
            }
            else if(root->left == nullptr && root->right != nullptr ){
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else{
                Node* temp = root->right;
                while(temp->left != nullptr){
                    temp = temp->left;
                }
                root -> data = temp -> data;
                root->right = deleteHelper(root->right,temp ->data);
            }     
        }
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        return balance(root);
    }   

    int getHeight(Node * root){
        return root ? root->height : 0;
    }
    int getBalance(Node* root){
        return root ? getHeight(root->left) - getHeight(root->right) : 0;
    }

    Node* balance(Node* root){
        int balanceFactor = getBalance(root);
        if (balanceFactor > 1){
            if(getBalance(root -> left)<0){
                root -> left = leftRotate(root->left);
            }
            root = rightRotate(root);
        }
        if(balanceFactor <-1){
            if(getBalance(root->right)>0){
                root -> right = rightRotate(root->right);
            }
            root = leftRotate(root);
        }
        return root;
    }

    Node* rightRotate(Node* x){
        Node* y = x -> left;
        Node * tmp = y ->right;
        y ->right = x;
        x -> left = tmp;

        x -> height = 1 + max(getHeight(x->left),getHeight(x->right));
        y -> height = 1 + max(getHeight(y->left),getHeight(y->right));

        return y;
    }

    Node* leftRotate(Node* x){
        Node* y = x -> right;
        Node * tmp = y ->left;
        y ->left = x;
        x -> right = tmp;

        x -> height = 1 + max(getHeight(x->left),getHeight(x->right));
        y -> height = 1 + max(getHeight(y->left),getHeight(y->right));

        return y;
    }
    void destroy(Node* root) {
        if (!root) return;
        destroy(root->left);
        destroy(root->right);
        delete root;
    }

public :
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() { destroy(root); }

    void display(){
        displayHelper(root);
        cout << endl;
    }

    bool search(int data){
        return searchHelper(root,data);
    }
    void remove(int data){
        if(search(data)){
            root = deleteHelper(root,data);
        }
        else{
            cout << "Couldn't find the data.\n";
        }
    }
    void insertNode(int data){
        root = insertHelper(root,new Node(data));
    }
};

int main(){

    BinaryTree tree;
    tree.insertNode(5);
    tree.insertNode(1);
    tree.insertNode(9);
    tree.insertNode(2);
    tree.insertNode(7);
    tree.insertNode(3);
    tree.insertNode(6);
    tree.insertNode(4);
    tree.insertNode(8);

    tree.remove(4);
    tree.display();
    cout << tree.search(4) << endl;

    return 0;
}