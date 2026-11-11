
#include <iostream>
using namespace std;

class AVLTree {

private:

    struct Node {
        int data;
        int height;
        Node* left;
        Node* right;

        Node(int value) {
            data = value;
            height = 1;
            left = right = NULL;
        }
    };

    Node* root;

    int getHeight(Node* node) {
        if (node == NULL)
            return 0;

        return node->height;
    }

    int getBalance(Node* node) {
        if (node == NULL)
            return 0;

        return getHeight(node->left) -
               getHeight(node->right);
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    // Right Rotation
    Node* rightRotate(Node* y) {

        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(getHeight(y->left),
                            getHeight(y->right));

        x->height = 1 + max(getHeight(x->left),
                            getHeight(x->right));

        return x;
    }

    // Left Rotation
    Node* leftRotate(Node* x) {

        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(getHeight(x->left),
                            getHeight(x->right));

        y->height = 1 + max(getHeight(y->left),
                            getHeight(y->right));

        return y;
    }

    Node* insert(Node* node, int value) {

        if (node == NULL)
            return new Node(value);

        if (value < node->data)
            node->left = insert(node->left, value);

        else if (value > node->data)
            node->right = insert(node->right, value);

        else
            return node;

        node->height = 1 + max(getHeight(node->left),
                               getHeight(node->right));

        int balance = getBalance(node);

        // LL Case
        if (balance > 1 && value < node->left->data)
            return rightRotate(node);

        // RR Case
        if (balance < -1 && value > node->right->data)
            return leftRotate(node);

        // LR Case
        if (balance > 1 && value > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL Case
        if (balance < -1 && value < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inorder(Node* node) {
        if (node == NULL)
            return;

        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

public:

    AVLTree() {
        root = NULL;
    }

    void insert(int value) {
        root = insert(root, value);
    }

    void display() {
        inorder(root);
        cout << endl;
    }

    void showHeight() {
        cout << "Tree Height: " << getHeight(root) << endl;
    }

    void showBalanceFactors() {
        cout << "\nBalance Factors (Inorder):" << endl;
        showBF(root);
    }

    void showBF(Node* node) {
        // Not accessible here as this is a private nested type.
    }
};

int main() {

    AVLTree tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    cout << "Initial AVL Tree: ";
    tree.display();

    tree.insert(12);

    cout << "\nAfter inserting 12: ";
    tree.display();

    tree.showHeight();

    return 0;
}

