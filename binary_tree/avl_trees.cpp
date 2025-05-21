#include <iostream>
using namespace std;

class Node {
public:
    int data;
    int height;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        height = 1;
        left = right = nullptr;
    }
};

class AVLTree {
public:
    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node* rightRotate(Node* y) {
        cout << "Rotate right on node " << y->data << "\n";
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    Node* leftRotate(Node* x) {
        cout << "Rotate left on node " << x->data << "\n";
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    Node* insert(Node* node, int data) {
        if (!node) return new Node(data);

        if (data < node->data)
            node->left = insert(node->left, data);
        else if (data > node->data)
            node->right = insert(node->right, data);
        else
            return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        return balance(node);
    }

    Node* minValueNode(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    Node* deleteNode(Node* node, int data) {
        if (!node) return node;

        if (data < node->data)
            node->left = deleteNode(node->left, data);
        else if (data > node->data)
            node->right = deleteNode(node->right, data);
        else {
            if (!node->left)
                return node->right;
            else if (!node->right)
                return node->left;

            Node* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        return balance(node);
    }

    Node* balance(Node* node) {
        int balanceFactor = getBalance(node);

        if (balanceFactor > 1) {
            if (getBalance(node->left) < 0)
                node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balanceFactor < -1) {
            if (getBalance(node->right) > 0)
                node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inOrderTraversal(Node* node) {
        if (node) {
            inOrderTraversal(node->left);
            cout << node->data << " ";
            inOrderTraversal(node->right);
        }
    }
};

int main() {
    AVLTree tree;
    Node* root = nullptr;

    int values[] = {10, 20, 30, 40, 50, 25};

    for (int i : values) {
        root = tree.insert(root, i);
    }

    cout << "In-order Traversal: ";
    tree.inOrderTraversal(root);
    cout << "\n";

    root = tree.deleteNode(root, 30);
    cout << "After deleting 30, In-order Traversal: ";
    tree.inOrderTraversal(root);
    cout << "\n";

    return 0;
}
