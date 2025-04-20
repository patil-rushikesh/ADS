#include <iostream>
using namespace std;

class Node {
public:
    int data, height;
    Node *left, *right;

    Node(int val) {
        data = val;
        height = 1;
        left = right = nullptr;
    }
};

class AVLTree {
private:
    Node *root;

    // Custom function to get the maximum of two values
    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    // Get the height of the node
    int getHeight(Node *node) {
        return node ? node->height : 0;
    }

    // Get the balance factor of the node
    int getBalance(Node *node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // Right rotation
    Node* rotateRight(Node *y) {
        Node *x = y->left;
        Node *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    // Left rotation
    Node* rotateLeft(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    // Insert node and balance the tree
    Node* insert(Node* node, int key) {
        // 1. Perform the normal BST insert
        if (!node)
            return new Node(key);

        if (key < node->data)
            node->left = insert(node->left, key);
        else if (key > node->data)
            node->right = insert(node->right, key);
        else
            return node;  // No duplicates

        // 2. Update height of this ancestor node
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // 3. Get the balance factor
        int balance = getBalance(node);

        // 4. Balance the tree if it becomes unbalanced

        // LL Case
        if (balance > 1 && key < node->left->data)
            return rotateRight(node);

        // RR Case
        if (balance < -1 && key > node->right->data)
            return rotateLeft(node);

        // LR Case
        if (balance > 1 && key > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // RL Case
        if (balance < -1 && key < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Inorder traversal
    void inorder(Node *node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    // Delete the tree
    void deleteTree(Node *node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    AVLTree() {
        root = nullptr;
    }

    ~AVLTree() {
        deleteTree(root);
    }

    // Insert key into the tree
    void insert(int key) {
        root = insert(root, key);
    }

    // Display the inorder traversal
    void displayInorder() {
        cout << "Inorder Traversal: ";
        inorder(root);
        cout << endl;
    }

    // Menu to interact with the tree
    void menu() {
        int choice, val;
        do {
            cout << "\n===== AVL Tree Menu =====\n";
            cout << "1. Insert Node\n";
            cout << "2. Inorder Traversal\n";
            cout << "0. Exit\n";
            cout << "==========================\n";
            cout << "Enter choice: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    cout << "Enter value to insert: ";
                    cin >> val;
                    insert(val);
                    break;
                case 2:
                    displayInorder();
                    break;
                case 0:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
            }
        } while (choice != 0);
    }
};

int main() {
    AVLTree tree;
    tree.menu();
    return 0;
}
