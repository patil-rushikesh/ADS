#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
    vector<int> keys;
    vector<Node*> children;
    bool leaf;
    int degree;

    Node(int t, bool isLeaf) {
        degree = t;
        leaf = isLeaf;
        keys.reserve(t - 1);
        children.reserve(t);
    }
};

class BTree {
private:
    Node* root;
    int t;

    // Insert key into a non-full node
    void insertNonFull(Node* node, int key) {
        int i = node->keys.size() - 1;

        if (node->leaf) {
            node->keys.push_back(0);
            while (i >= 0 && node->keys[i] > key) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = key;
        } else {
            while (i >= 0 && node->keys[i] > key) {
                i--;
            }
            i++;

            if (node->children[i]->keys.size() == (2 * t - 1)) {
                splitChild(node, i);
                if (node->keys[i] < key) {
                    i++;
                }
            }
            insertNonFull(node->children[i], key);
        }
    }

    // Split a full child node
    void splitChild(Node* parent, int i) {
        Node* fullChild = parent->children[i];
        Node* newChild = new Node(t, fullChild->leaf);

        parent->keys.push_back(0);
        parent->children.push_back(nullptr);
        for (int j = parent->keys.size() - 2; j > i; j--) {
            parent->keys[j + 1] = parent->keys[j];
            parent->children[j + 2] = parent->children[j + 1];
        }
        parent->keys[i] = fullChild->keys[t - 1];
        parent->children[i + 1] = newChild;

        for (int j = 0; j < t - 1; j++) {
            newChild->keys.push_back(fullChild->keys[j + t]);
        }

        if (!fullChild->leaf) {
            for (int j = 0; j < t; j++) {
                newChild->children.push_back(fullChild->children[j + t]);
            }
        }

        fullChild->keys.resize(t - 1);
        fullChild->children.resize(t);
    }

    // Delete the key from the node
    void deleteKey(Node* node, int key) {
        int i = 0;
        while (i < node->keys.size() && node->keys[i] < key) {
            i++;
        }

        if (i < node->keys.size() && node->keys[i] == key) {
            if (node->leaf) {
                node->keys.erase(node->keys.begin() + i);
            } else {
                Node* child = node->children[i];
                if (child->keys.size() >= t) {
                    node->keys[i] = child->keys.back();
                    deleteKey(child, node->keys[i]);
                } else {
                    Node* sibling = node->children[i + 1];
                    if (sibling->keys.size() >= t) {
                        node->keys[i] = sibling->keys.front();
                        deleteKey(sibling, node->keys[i]);
                    } else {
                        mergeChildren(node, i);
                        deleteKey(child, key);
                    }
                }
            }
        } else if (!node->leaf) {
            deleteKey(node->children[i], key);
        }
    }

    // Merge child nodes if they don't have enough keys
    void mergeChildren(Node* parent, int i) {
        Node* leftChild = parent->children[i];
        Node* rightChild = parent->children[i + 1];
        leftChild->keys.push_back(parent->keys[i]);
        parent->keys.erase(parent->keys.begin() + i);

        for (int j = 0; j < rightChild->keys.size(); j++) {
            leftChild->keys.push_back(rightChild->keys[j]);
        }

        if (!rightChild->leaf) {
            for (int j = 0; j < rightChild->children.size(); j++) {
                leftChild->children.push_back(rightChild->children[j]);
            }
        }

        parent->children.erase(parent->children.begin() + i + 1);
        delete rightChild;
    }

public:
    BTree(int degree) {
        t = degree;
        root = new Node(t, true);
    }

    // Insert a key into the B-tree
    void insert(int key) {
        if (root->keys.size() == (2 * t - 1)) {
            Node* newRoot = new Node(t, false);
            newRoot->children.push_back(root);
            splitChild(newRoot, 0);
            root = newRoot;
        }
        insertNonFull(root, key);
    }

    // Delete a key from the B-tree
    void deleteNode(int key) {
        deleteKey(root, key);
        if (root->keys.size() == 0) {
            if (root->leaf) {
                delete root;
                root = nullptr;
            } else {
                root = root->children[0];
                delete root;
            }
        }
    }

    // In-order traversal to display the tree
    void inorder(Node* node) {
        if (node != nullptr) {
            for (int i = 0; i < node->keys.size(); i++) {
                inorder(node->children[i]);
                cout << node->keys[i] << " ";
            }
            inorder(node->children[node->keys.size()]);
        }
    }

    void display() {
        inorder(root);
        cout << endl;
    }

    void displayMenu() {
        cout << "\n========== BTree Menu ==========\n";
        cout << "1. Insert Node\n";
        cout << "2. Delete Node\n";
        cout << "3. Display Tree (Inorder Traversal)\n";
        cout << "0. Exit\n";
        cout << "================================\n";
        cout << "Enter your choice: ";
    }
};

int main() {
    int t, choice, value;

    cout << "Enter the degree of the BTree: ";
    cin >> t;

    BTree tree(t);

    do {
        tree.displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            tree.insert(value);
            break;
        case 2:
            cout << "Enter value to delete: ";
            cin >> value;
            tree.deleteNode(value);
            break;
        case 3:
            cout << "BTree Inorder Traversal: ";
            tree.display();
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
