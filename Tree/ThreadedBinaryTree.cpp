#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node *left, *right;
    bool lthread, rthread;

    Node(int val) {
        data = val;
        left = right = nullptr;
        lthread = rthread = true;
    }
};

class ThreadedBinaryTree {
private:
    Node *root;

public:
    ThreadedBinaryTree() {
        root = nullptr;
    }

    ~ThreadedBinaryTree() {
        clear();
    }

    void insert(int val) {
        Node *ptr = root;
        Node *par = nullptr;

        while (ptr != nullptr) {
            if (val == ptr->data) {
                cout << "Duplicate value not allowed.\n";
                return;
            }

            par = ptr;

            if (val < ptr->data) {
                if (!ptr->lthread)
                    ptr = ptr->left;
                else
                    break;
            } else {
                if (!ptr->rthread)
                    ptr = ptr->right;
                else
                    break;
            }
        }

        Node *tmp = new Node(val);

        if (par == nullptr) {
            root = tmp;
        } else if (val < par->data) {
            tmp->left = par->left;
            tmp->right = par;
            par->lthread = false;
            par->left = tmp;
        } else {
            tmp->right = par->right;
            tmp->left = par;
            par->rthread = false;
            par->right = tmp;
        }
    }

    void inorder() {
        Node *ptr = root;
        if (!ptr) {
            cout << "Tree is empty\n";
            return;
        }

        while (!ptr->lthread)
            ptr = ptr->left;

        while (ptr != nullptr) {
            cout << ptr->data << " ";

            if (ptr->rthread)
                ptr = ptr->right;
            else {
                ptr = ptr->right;
                while (!ptr->lthread)
                    ptr = ptr->left;
            }
        }
        cout << endl;
    }

    Node* inorderPredecessor(Node* ptr) {
        if (ptr->lthread)
            return ptr->left;

        ptr = ptr->left;
        while (!ptr->rthread)
            ptr = ptr->right;
        return ptr;
    }

    Node* inorderSuccessor(Node* ptr) {
        if (ptr->rthread)
            return ptr->right;

        ptr = ptr->right;
        while (!ptr->lthread)
            ptr = ptr->left;
        return ptr;
    }

    void deleteNode(int val) {
        Node *parent = nullptr, *curr = root;
        bool found = false;

        while (curr != nullptr) {
            if (val == curr->data) {
                found = true;
                break;
            }

            parent = curr;
            if (val < curr->data) {
                if (!curr->lthread)
                    curr = curr->left;
                else
                    break;
            } else {
                if (!curr->rthread)
                    curr = curr->right;
                else
                    break;
            }
        }

        if (!found) {
            cout << "Value not found in the tree.\n";
            return;
        }

        // Case 1: Two children
        if (!curr->lthread && !curr->rthread) {
            Node *inSucc = curr->right;
            Node *parSucc = curr;

            while (!inSucc->lthread) {
                parSucc = inSucc;
                inSucc = inSucc->left;
            }

            curr->data = inSucc->data;
            curr = inSucc;
            parent = parSucc;
        }

        // Case 2 & 3: Node with one or no child
        Node *child = nullptr;
        if (!curr->lthread)
            child = curr->left;
        else if (!curr->rthread)
            child = curr->right;

        if (parent == nullptr) {
            root = child;
        } else if (curr == parent->left) {
            if (curr->lthread && curr->rthread) {
                parent->lthread = true;
                parent->left = curr->left;
            } else {
                parent->left = child;
                Node *pred = inorderPredecessor(curr);
                Node *succ = inorderSuccessor(curr);
                if (!curr->lthread)
                    pred->right = succ;
                else if (!curr->rthread)
                    succ->left = pred;
            }
        } else {
            if (curr->lthread && curr->rthread) {
                parent->rthread = true;
                parent->right = curr->right;
            } else {
                parent->right = child;
                Node *pred = inorderPredecessor(curr);
                Node *succ = inorderSuccessor(curr);
                if (!curr->lthread)
                    pred->right = succ;
                else if (!curr->rthread)
                    succ->left = pred;
            }
        }

        delete curr;
    }

    void clear() {
        while (root != nullptr) {
            deleteNode(root->data);
        }
    }

    void menu() {
        int choice, val;
        do {
            cout << "\n===== Threaded Binary Tree Menu =====\n";
            cout << "1. Insert\n";
            cout << "2. Inorder Traversal\n";
            cout << "3. Delete\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Enter value to insert: ";
                    cin >> val;
                    insert(val);
                    break;
                case 2:
                    cout << "Inorder Traversal: ";
                    inorder();
                    break;
                case 3:
                    cout << "Enter value to delete: ";
                    cin >> val;
                    deleteNode(val);
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
    ThreadedBinaryTree tbt;
    tbt.menu();
    return 0;
}
