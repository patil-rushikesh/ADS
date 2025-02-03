//This program demonstrates the operations of maximum heap tree

#include <iostream>
using namespace std;

class TreeNode
{
public:
    int data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

class MaxHeap
{
private:
    TreeNode *root;

    TreeNode* insertNode(TreeNode* node, int value)
    {
        if (!node)
            return new TreeNode(value);
        if (value > node->data)
            node->left = insertNode(node->left, value);
        else
            node->right = insertNode(node->right, value);
        return node;
    }

    TreeNode* deleteMaxNode(TreeNode* node)
    {
        if (!node) return nullptr;
        if (!node->left) return node->right;
        node->left = deleteMaxNode(node->left);
        return node;
    }

    bool searchNode(TreeNode* node, int value)
    {
        if (!node) return false;
        if (node->data == value) return true;
        return searchNode(node->left, value) || searchNode(node->right, value);
    }

    void inorderTraversal(TreeNode* node)
    {
        if (!node) return;
        inorderTraversal(node->left);
        cout << node->data << " ";
        inorderTraversal(node->right);
    }

public:
    MaxHeap() : root(nullptr) {}

    void insert(int value) { root = insertNode(root, value); }
    void deleteMax() { root = deleteMaxNode(root); }
    bool search(int value) { return searchNode(root, value); }
    void printHeap() { inorderTraversal(root); cout << endl; }
};

int main()
{
    MaxHeap heap;
    int choice, value;
    do
    {
        cout << "\nMenu:\n1. Insert\n2. Delete Max\n3. Search\n4. Print Heap\n5. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            heap.insert(value);
            break;
        case 2:
            cout << "Deleting max element...\n";
            heap.deleteMax();
            break;
        case 3:
            cout << "Enter value to search: ";
            cin >> value;
            cout << (heap.search(value) ? "Found" : "Not Found") << endl;
            break;
        case 4:
            cout << "Heap (Inorder Traversal): ";
            heap.printHeap();
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);
    return 0;
}