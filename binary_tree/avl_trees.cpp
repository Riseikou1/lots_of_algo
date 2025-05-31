#include <iostream>
using namespace std;

class Node{
public:
    int data, height;
    Node* left;
    Node* right;
    Node(int data) : data(data), height(1), left(nullptr), right(nullptr) {}
};

class BinaryTree{
private:
    Node* root;

    void displayHelper(Node* root){
        if (!root) return;
        displayHelper(root->left);
        cout << root->data << " ";
        displayHelper(root->right);
    }

    int getHeight(Node* node) {
        return node ? node->height : 0;
    }
    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    Node* balance(Node* node) {
        int balanceFactor = getBalance(node);

        // Left heavy
        if (balanceFactor > 1) {
            if (getBalance(node->left) < 0)
                node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // Right heavy
        if (balanceFactor < -1) {
            if (getBalance(node->right) > 0)
                node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    Node* insertHelper(Node* node, int data) {
        if (node == nullptr)
            return new Node(data);
        if (data < node->data)
            node->left = insertHelper(node->left, data);
        else
            node->right = insertHelper(node->right, data);

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        return balance(node);
    }

    Node* deleteHelper(Node* node, int data) {
        if (!node) return nullptr;
        if (data < node->data)
            node->left = deleteHelper(node->left, data);
        else if (data > node->data)
            node->right = deleteHelper(node->right, data);
        else {
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            else if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            else {
                Node* temp = node->right;
                while (temp->left)
                    temp = temp->left;
                node->data = temp->data;
                node->right = deleteHelper(node->right, temp->data);
            }
        }
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        return balance(node);
    }

    bool searchHelper(Node* node, int data) {
        if (!node) return false;
        if (data < node->data)
            return searchHelper(node->left, data);
        else if (data > node->data)
            return searchHelper(node->right, data);
        return true;
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() { destroy(root); }

    void display() {
        displayHelper(root);
        cout << endl;
    }

    bool search(int data) {
        return searchHelper(root, data);
    }
    void remove(int data) {
        if (search(data))
            root = deleteHelper(root, data);
        else
            cout << "Couldn't find the data.\n";
    }
    void insertNode(int data) {
        root = insertHelper(root, data);
    }
};

int main() {
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
