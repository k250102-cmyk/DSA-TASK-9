
#include <iostream>
using namespace std;

class BST {

private:

    struct Node {
        int data;
        Node* left;
        Node* right;

        Node(int value) {
            data = value;
            left = right = NULL;
        }
    };

    Node* root;

    // Insert into BST
    Node* insert(Node* node, int value) {

        if (node == NULL)
            return new Node(value);

        if (value < node->data)
            node->left = insert(node->left, value);

        else if (value > node->data)
            node->right = insert(node->right, value);

        return node;
    }

    // Count total nodes
    int countNodes(Node* node) {

        if (node == NULL)
            return 0;

        return 1 + countNodes(node->left)
                 + countNodes(node->right);
    }

    // Store inorder elements in array
    void inorder(Node* node, int arr[], int& index) {

        if (node == NULL)
            return;

        inorder(node->left, arr, index);

        arr[index] = node->data;
        index++;

        inorder(node->right, arr, index);
    }

    // Build balanced BST from sorted array
    Node* buildBalanced(int arr[], int start, int end) {

        if (start > end)
            return NULL;

        int mid = (start + end) / 2;

        Node* node = new Node(arr[mid]);

        node->left = buildBalanced(arr, start, mid - 1);

        node->right = buildBalanced(arr, mid + 1, end);

        return node;
    }

    // Display inorder
    void displayInorder(Node* node) {

        if (node == NULL)
            return;

        displayInorder(node->left);

        cout << node->data << " ";

        displayInorder(node->right);
    }

    // Display tree
    void displayTree(Node* node, int space) {

        if (node == NULL)
            return;

        space += 5;

        displayTree(node->right, space);

        cout << endl;

        for (int i = 5; i < space; i++)
            cout << " ";

        cout << node->data << endl;

        displayTree(node->left, space);
    }

public:

    BST() {
        root = NULL;
    }

    void insert(int value) {
        root = insert(root, value);
    }

    void convertToBalancedBST() {

        int n = countNodes(root);

        int arr[100];

        int index = 0;

        inorder(root, arr, index);

        root = buildBalanced(arr, 0, n - 1);
    }

    void display() {
        displayTree(root, 0);
    }

    void showInorder() {
        displayInorder(root);
        cout << endl;
    }
};

int main() {

    // TREE A
    BST A;

    A.insert(10);
    A.insert(6);
    A.insert(4);
    A.insert(8);

    cout << "TREE A - Original:" << endl;
    A.display();

    cout << "\nInorder: ";
    A.showInorder();

    A.convertToBalancedBST();

    cout << "\nTREE A - Balanced:" << endl;
    A.display();


    // TREE B
    BST B;

    B.insert(10);
    B.insert(16);
    B.insert(12);
    B.insert(18);

    cout << "\nTREE B - Original:" << endl;
    B.display();

    cout << "\nInorder: ";
    B.showInorder();

    B.convertToBalancedBST();

    cout << "\nTREE B - Balanced:" << endl;
    B.display();

    return 0;
}

