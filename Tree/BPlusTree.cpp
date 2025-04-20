#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
    vector<int> keys;   // List of keys
    vector<Node*> children;  // List of child pointers
    bool leaf;  // Flag to check if node is a leaf

    Node(int t, bool isLeaf) {
        leaf = isLeaf;
        keys.reserve(t - 1);
        children.reserve(t);
    }
};

class BPlusTree {
private:
    Node* root;
    int t;  // Minimum degree of the tree (defines the range of children per node)

    // Helper function for deletion
    void deleteFromLeaf(Node* node, int key) {
        int index = findKey(node, key);
        if (index < 0) {
            cout << "Key " << key << " not found in the tree.\n";
            return;
        }
        node->keys.erase(node->keys.begin() + index);  // Remove the key from leaf
    }

    // Find the index of the key in a node
    int findKey(Node* node, int key) {
        int index = 0;
        while (index < node->keys.size() && node->keys[index] < key) {
            index++;
        }
        if (index < node->keys.size() && node->keys[index] == key) {
            return index;
        }
        return -1;  // Key not found
    }

    // Delete key from non-leaf node
    void deleteFromNonLeaf(Node* node, int key) {
        int index = findKey(node, key);

        if (index != -1) {  // Key is present in the internal node
            if (node->children[index]->keys.size() >= t) {
                // Predecessor key
                int pred = getPred(node, index);
                node->keys[index] = pred;
                deleteFromLeaf(node->children[index], pred);
            } else if (node->children[index + 1]->keys.size() >= t) {
                // Successor key
                int succ = getSucc(node, index);
                node->keys[index] = succ;
                deleteFromLeaf(node->children[index + 1], succ);
            } else {
                merge(node, index);
                deleteFromNonLeaf(node->children[index], key);
            }
        } else {
            if (node->leaf) {
                cout << "Key " << key << " not found.\n";
                return;
            }
            bool flag = (index == node->keys.size());
            if (node->children[index]->keys.size() < t) {
                fill(node, index);
            }
            if (flag && index > node->keys.size())
                deleteFromNonLeaf(node->children[index - 1], key);
            else
                deleteFromNonLeaf(node->children[index], key);
        }
    }

    // Get predecessor key
    int getPred(Node* node, int index) {
        Node* curr = node->children[index];
        while (!curr->leaf)
            curr = curr->children[curr->children.size() - 1];
        return curr->keys[curr->keys.size() - 1];
    }

    // Get successor key
    int getSucc(Node* node, int index) {
        Node* curr = node->children[index + 1];
        while (!curr->leaf)
            curr = curr->children[0];
        return curr->keys[0];
    }

    // Merge nodes
    void merge(Node* node, int index) {
        Node* child = node->children[index];
        Node* sibling = node->children[index + 1];

        child->keys.push_back(node->keys[index]);
        for (int i = 0; i < sibling->keys.size(); i++) {
            child->keys.push_back(sibling->keys[i]);
        }

        if (!child->leaf) {
            for (int i = 0; i < sibling->children.size(); i++) {
                child->children.push_back(sibling->children[i]);
            }
        }

        node->keys.erase(node->keys.begin() + index);
        node->children.erase(node->children.begin() + index + 1);
        delete sibling;
    }

    // Fill the node if it has less than t keys
    void fill(Node* node, int index) {
        if (index != 0 && node->children[index - 1]->keys.size() >= t)
            borrowFromPrev(node, index);
        else if (index != node->keys.size() && node->children[index + 1]->keys.size() >= t)
            borrowFromNext(node, index);
        else {
            if (index != node->keys.size())
                merge(node, index);
            else
                merge(node, index - 1);
        }
    }

    // Borrow a key from the previous sibling
    void borrowFromPrev(Node* node, int index) {
        Node* child = node->children[index];
        Node* sibling = node->children[index - 1];

        child->keys.insert(child->keys.begin(), node->keys[index - 1]);
        node->keys[index - 1] = sibling->keys[sibling->keys.size() - 1];
        sibling->keys.pop_back();

        if (!child->leaf) {
            child->children.insert(child->children.begin(), sibling->children[sibling->children.size() - 1]);
            sibling->children.pop_back();
        }
    }

    // Borrow a key from the next sibling
    void borrowFromNext(Node* node, int index) {
        Node* child = node->children[index];
        Node* sibling = node->children[index + 1];

        child->keys.push_back(node->keys[index]);
        node->keys[index] = sibling->keys[0];
        sibling->keys.erase(sibling->keys.begin());

        if (!child->leaf) {
            child->children.push_back(sibling->children[0]);
            sibling->children.erase(sibling->children.begin());
        }
    }

    // Insert a key into a node that is not full
    void insertNonFull(Node* node, int key) {
        int i = node->keys.size() - 1;

        if (node->leaf) {
            // If the node is a leaf, insert the key directly
            while (i >= 0 && node->keys[i] > key) {
                i--;
            }
            node->keys.insert(node->keys.begin() + i + 1, key);
        } else {
            // If the node is not a leaf, find the appropriate child to insert into
            while (i >= 0 && node->keys[i] > key) {
                i--;
            }
            i++;

            // If the child node is full, split it
            if (node->children[i]->keys.size() == (2 * t - 1)) {
                splitChild(node, i);

                // After splitting, the middle key of the child moves up to the parent node
                if (node->keys[i] < key) {
                    i++;
                }
            }
            insertNonFull(node->children[i], key);
        }
    }

    // Split the child when it is full
    void splitChild(Node* parent, int i) {
        Node* fullChild = parent->children[i];
        Node* newChild = new Node(t, fullChild->leaf);
        parent->children.insert(parent->children.begin() + i + 1, newChild);
        parent->keys.insert(parent->keys.begin() + i, fullChild->keys[t - 1]);

        for (int j = t; j < fullChild->keys.size(); j++) {
            newChild->keys.push_back(fullChild->keys[j]);
        }

        if (!fullChild->leaf) {
            for (int j = t; j < fullChild->children.size(); j++) {
                newChild->children.push_back(fullChild->children[j]);
            }
        }

        fullChild->keys.resize(t - 1);
        fullChild->children.resize(t);
    }

public:
    BPlusTree(int degree) {
        t = degree;
        root = new Node(t, true);  // Root is initially a leaf
    }

    // Insert a new key into the B+ tree
    void insert(int key) {
        if (root->keys.size() == (2 * t - 1)) {
            Node* newRoot = new Node(t, false);
            newRoot->children.push_back(root);
            splitChild(newRoot, 0);
            root = newRoot;
        }
        insertNonFull(root, key);
    }

    // Delete key from the B+ Tree
    void deleteKey(int key) {
        deleteFromNonLeaf(root, key);
    }

    // Display the tree in inorder traversal
    void display() {
        inorder(root);
        cout << endl;
    }

    // Menu display
    void displayMenu() {
        cout << "\n========== B+ Tree Menu ==========\n";
        cout << "1. Insert Node\n";
        cout << "2. Delete Node\n";
        cout << "3. Display Tree (Inorder Traversal)\n";
        cout << "0. Exit\n";
        cout << "================================\n";
        cout << "Enter your choice: ";
    }

    // Inorder traversal for display
    void inorder(Node* node) {
        if (node != nullptr) {
            for (int i = 0; i < node->keys.size(); i++) {
                inorder(node->children[i]);
                cout << node->keys[i] << " ";
            }
            inorder(node->children[node->children.size() - 1]);
        }
    }
};

int main() {
    BPlusTree tree(3);  // B+ Tree with minimum degree 3
    int choice, value;

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
            tree.deleteKey(value);
            break;
        case 3:
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
