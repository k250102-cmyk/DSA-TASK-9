/*AVL trees maintain a strictly balanced height logarithmic to the number of nodes , preventing search, insertion, and deletion operations from degenerating into $O(n)$ time complexity as seen in unbalanced binary search trees*/
#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    int height;

    Node(int v) : val(v), left(NULL), right(NULL), height(1) {}
};

// Helper function to update node height based on children
void updateHeight(Node* n) {
    if (!n) return;
    int hLeft = n->left ? n->left->height : 0;
    int hRight = n->right ? n->right->height : 0;
    n->height = 1 + (hLeft > hRight ? hLeft : hRight);
}

// Right Rotation Function
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Left Rotation Function
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node* convertBST_A_to_AVL(Node* root) {
    if (!root) return NULL;

    // Set initial heights of leaf and intermediate nodes
    root->left->left->height = 1;   // Node 4
    root->left->right->height = 1;  // Node 8
    root->left->height = 2;         // Node 6
    root->height = 3;               // Node 10

    // Perform Right Rotation on Root (Node 10)
    return rotateRight(root);
}


Node* convertBST_B_to_AVL(Node* root) {
    if (!root) return NULL;

    // Set initial heights of leaf and intermediate nodes
    root->right->left->height = 1;  // Node 12
    root->right->right->height = 1; // Node 18
    root->right->height = 2;        // Node 16
    root->height = 3;               // Node 10

    return rotateLeft(root);
}
