
#include <iostream>
using namespace std;

class AVLTree {

private:

    struct Node {
        int key;
        int height;
        Node* left;
        Node* right;

        Node(int value) {
            key = value;
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

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    int getBalance(Node* node) {
        if (node == NULL)
            return 0;

        return getHeight(node->left) -
               getHeight(node->right);
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

    // AVL Insertion
    Node* insert(Node* node, int value) {

        if (node == NULL)
            return new Node(value);

        if (value < node->key)
            node->left = insert(node->left, value);

        else if (value > node->key)
            node->right = insert(node->right, value);

        else
            return node;

        node->height = 1 + max(getHeight(node->left),
                               getHeight(node->right));

        int balance = getBalance(node);

        // LL Case
        if (balance > 1 && value < node->left->key)
            return rightRotate(node);

        // RR Case
        if (balance < -1 && value > node->right->key)
            return leftRotate(node);

        // LR Case
        if (balance > 1 && value > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL Case
        if (balance < -1 && value < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // Find kth smallest using inorder
    bool kthSmallest(Node* node, int k,
                     int& count, int& result) {

        if (node == NULL)
            return false;

        if (kthSmallest(node->left, k, count, result))
            return true;

        count++;

        if (count == k) {
            result = node->key;
            return true;
        }

        return kthSmallest(node->right, k, count, result);
    }

    // Find kth largest using reverse inorder
    bool kthLargest(Node* node, int k,
                    int& count, int& result) {

        if (node == NULL)
            return false;

        if (kthLargest(node->right, k, count, result))
            return true;

        count++;

        if (count == k) {
            result = node->key;
            return true;
        }

        return kthLargest(node->left, k, count, result);
    }

    // Count total nodes
    int countNodes(Node* node) {

        if (node == NULL)
            return 0;

        return 1 + countNodes(node->left)
                 + countNodes(node->right);
    }

    // Display tree
    void inorder(Node* node) {

        if (node == NULL)
            return;

        inorder(node->left);
        cout << node->key << " ";
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

    void findKthSmallest(int k) {

        int count = 0;
        int result = 0;

        if (k <= 0 || k > countNodes(root)) {
            cout << "Invalid k value!" << endl;
            return;
        }

        kthSmallest(root, k, count, result);

        cout << "Kth Smallest Key: " << result << endl;
    }

    void findKthLargest(int k) {

        int count = 0;
        int result = 0;

        if (k <= 0 || k > countNodes(root)) {
            cout << "Invalid k value!" << endl;
            return;
        }

        kthLargest(root, k, count, result);

        cout << "Kth Largest Key: " << result << endl;
    }

    void showSideHeights() {

        if (root == NULL) {
            cout << "Tree is empty!" << endl;
            return;
        }

        cout << "Root Key: " << root->key << endl;

        cout << "Left Side Height: "
             << getHeight(root->left) << endl;

        cout << "Right Side Height: "
             << getHeight(root->right) << endl;
    }
};

int main() {

    AVLTree tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);

    cout << "AVL Tree (Inorder): ";
    tree.display();

    int k = 2;

    cout << "\nK = " << k << endl;

    tree.findKthSmallest(k);

    tree.findKthLargest(k);

    cout << "\nSubtree Heights:" << endl;

    tree.showSideHeights();

    return 0;
}

