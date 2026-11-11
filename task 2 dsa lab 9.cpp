
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

    void display(Node* node, int space) {

        if (node == NULL)
            return;

        space += 5;

        display(node->right, space);

        cout << endl;

        for (int i = 5; i < space; i++)
            cout << " ";

        cout << node->data << endl;

        display(node->left, space);
    }

public:

    AVLTree() {
        root = NULL;
    }

    void insert(int value) {
        root = insert(root, value);
    }

    void performLeftRotation() {

        if (root != NULL && root->right != NULL)
            root = leftRotate(root);
    }

    void restoreBalance() {

        if (root != NULL && getBalance(root) > 1)
            root = rightRotate(root);
    }

    void displayTree() {
        display(root, 0);
    }
};

int main() {

    AVLTree tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "Original Tree:" << endl;
    tree.displayTree();

    tree.insert(55);

    cout << "\nAfter Inserting 55:" << endl;
    tree.displayTree();

    tree.performLeftRotation();

    cout << "\nAfter Left Rotation:" << endl;
    tree.displayTree();

    tree.restoreBalance();

    cout << "\nFinal Balanced AVL Tree:" << endl;
    tree.displayTree();

    return 0;
}

