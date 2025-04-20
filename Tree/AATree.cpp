#include <iostream>
using namespace std;

class Node {
public:
    int data;
    int level;  // Level of the node
    Node *left, *right;

    Node(int val) {
        data = val;
        level = 1;
        left = right = nullptr;
    }
};

class AATree {
private:
    Node *root;

    // Right rotate
    Node* rotateRight(Node *node) {
        Node *leftChild = node->left;
        node->left = leftChild->right;
        leftChild->right = node;
        node->level = leftChild->level + 1;
        return leftChild;
    }

    // Left rotate
    Node* rotateLeft(Node *node) {
        Node *rightChild = node->right;
        node->right = rightChild->left;
        rightChild->left = node;
        return rightChild;
    }

    // Skew operation (adjusting for left children having the same level as the parent)
    Node* skew(Node *node) {
        if (node == nullptr || node->left == nullptr)
            return node;

        if (node->level == node->left->level) {
            node = rotateRight(node);
        }
        return node;
    }

    // Split operation (adjusting for right children having a level one more than the parent)
    Node* split(Node *node) {
        if (node == nullptr || node->right == nullptr || node->right->right == nullptr)
            return node;

        if (node->level == node->right->right->level) {
            node = rotateLeft(node);
            node->level++;
        }
        return node;
    }

    // Insert node and balance the tree
    Node* insert(Node *node, int val) {
        if (node == nullptr)
            return new Node(val);

        if (val < node->data) {
            node->left = insert(node->left, val);
        } else if (val > node->data) {
            node->right = insert(node->right, val);
        }

        node = skew(node);
        node = split(node);

        return node;
    }

    // Find the minimum node
    Node* findMin(Node* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

    // Delete node and balance the tree
    Node* deleteNode(Node* node, int val) {
        if (node == nullptr)
            return node;

        if (val < node->data) {
            node->left = deleteNode(node->left, val);
        } else if (val > node->data) {
            node->right = deleteNode(node->right, val);
        } else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            } else {
                Node* temp = findMin(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data);
            }
        }

        if (node == nullptr)
            return node;

        // Balance the tree after deletion
        node = skew(node);
        node = split(node);

        return node;
    }

    // Inorder traversal
    void inorder(Node *node) {
        if (node) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

    // Delete the tree
    void deleteTree(Node *node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

public:
    AATree() {
        root = nullptr;
    }

    ~AATree() {
        deleteTree(root);
    }

    // Insert value into the tree
    void insert(int val) {
        root = insert(root, val);
    }

    // Delete value from the tree
    void deleteValue(int val) {
        root = deleteNode(root, val);
    }

    // Display inorder traversal
    void displayInorder() {
        cout << "Inorder Traversal: ";
        inorder(root);
        cout << endl;
    }

    // Menu to interact with the tree
    void menu() {
        int choice, val;
        do {
            cout << "\n===== AA Tree Menu =====\n";
            cout << "1. Insert Node\n";
            cout << "2. Delete Node\n";
            cout << "3. Inorder Traversal\n";
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
                    cout << "Enter value to delete: ";
                    cin >> val;
                    deleteValue(val);
                    break;
                case 3:
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
    AATree tree;
    tree.menu();
    return 0;
}
