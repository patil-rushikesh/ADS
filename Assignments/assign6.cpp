#include<iostream>
#include<queue>
using namespace std;

struct Red_Black {
    int data;
    Red_Black* left;
    Red_Black* right;
    bool color; // true for Red, false for Black
    Red_Black* parent;

    Red_Black(int val) {
        data = val;
        left = right = parent = NULL;
        color = true; // New nodes are always red initially
    }
};

class RedBlackTree {
private:
    Red_Black* root;

    void rotateLeft(Red_Black* node) {
        Red_Black* rightChild = node->right;
        node->right = rightChild->left;
        if (rightChild->left != NULL)
            rightChild->left->parent = node;
        rightChild->parent = node->parent;
        if (node->parent == NULL)
            root = rightChild;
        else if (node == node->parent->left)
            node->parent->left = rightChild;
        else
            node->parent->right = rightChild;
        rightChild->left = node;
        node->parent = rightChild;
    }

    void rotateRight(Red_Black* node) {
        Red_Black* leftChild = node->left;
        node->left = leftChild->right;
        if (leftChild->right != NULL)
            leftChild->right->parent = node;
        leftChild->parent = node->parent;
        if (node->parent == NULL)
            root = leftChild;
        else if (node == node->parent->right)
            node->parent->right = leftChild;
        else
            node->parent->left = leftChild;
        leftChild->right = node;
        node->parent = leftChild;
    }

    void fixInsert(Red_Black* node) {
        while (node != root && node->parent != NULL && node->parent->color == true) {
            if (node->parent == node->parent->parent->left) {
                Red_Black* uncle = node->parent->parent->right;
                if (uncle != NULL && uncle->color == true) {
                    node->parent->color = false;
                    uncle->color = false;
                    node->parent->parent->color = true;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotateLeft(node);
                    }
                    node->parent->color = false;
                    node->parent->parent->color = true;
                    rotateRight(node->parent->parent);
                }
            } else {
                Red_Black* uncle = node->parent->parent->left;
                if (uncle != NULL && uncle->color == true) {
                    node->parent->color = false;
                    uncle->color = false;
                    node->parent->parent->color = true;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotateRight(node);
                    }
                    node->parent->color = false;
                    node->parent->parent->color = true;
                    rotateLeft(node->parent->parent);
                }
            }
        }
        root->color = false;
    }

    void transplant(Red_Black* u, Red_Black* v) {
        if (u->parent == NULL)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        if (v != NULL)
            v->parent = u->parent;
    }

    Red_Black* minimum(Red_Black* node) {
        while (node->left != NULL)
            node = node->left;
        return node;
    }

    void fixDelete(Red_Black* x) {
        while (x != root && (x == NULL || x->color == false)) {
            if (x == x->parent->left) {
                Red_Black* sibling = x->parent->right;
                if (sibling->color == true) {
                    sibling->color = false;
                    x->parent->color = true;
                    rotateLeft(x->parent);
                    sibling = x->parent->right;
                }
                if ((sibling->left == NULL || sibling->left->color == false) &&
                    (sibling->right == NULL || sibling->right->color == false)) {
                    sibling->color = true;
                    x = x->parent;
                } else {
                    if (sibling->right == NULL || sibling->right->color == false) {
                        if (sibling->left != NULL)
                            sibling->left->color = false;
                        sibling->color = true;
                        rotateRight(sibling);
                        sibling = x->parent->right;
                    }
                    sibling->color = x->parent->color;
                    x->parent->color = false;
                    if (sibling->right != NULL)
                        sibling->right->color = false;
                    rotateLeft(x->parent);
                    x = root;
                }
            } else {
                Red_Black* sibling = x->parent->left;
                if (sibling->color == true) {
                    sibling->color = false;
                    x->parent->color = true;
                    rotateRight(x->parent);
                    sibling = x->parent->left;
                }
                if ((sibling->right == NULL || sibling->right->color == false) &&
                    (sibling->left == NULL || sibling->left->color == false)) {
                    sibling->color = true;
                    x = x->parent;
                } else {
                    if (sibling->left == NULL || sibling->left->color == false) {
                        if (sibling->right != NULL)
                            sibling->right->color = false;
                        sibling->color = true;
                        rotateLeft(sibling);
                        sibling = x->parent->left;
                    }
                    sibling->color = x->parent->color;
                    x->parent->color = false;
                    if (sibling->left != NULL)
                        sibling->left->color = false;
                    rotateRight(x->parent);
                    x = root;
                }
            }
        }
        if (x != NULL)
            x->color = false;
    }

    void deleteNode(Red_Black* node, int key) {
        Red_Black* z = NULL;
        Red_Black* x, *y;
        
        while (node != NULL) {
            if (node->data == key) {
                z = node;
                break;
            }
            if (key < node->data)
                node = node->left;
            else
                node = node->right;
        }

        if (z == NULL) {
            cout << "Key not found in the tree\n";
            return;
        }

        y = z;
        bool y_original_color = y->color;
        if (z->left == NULL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == NULL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                if (x != NULL)
                    x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                if (y->right != NULL)
                    y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            if (y->left != NULL)
                y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == false)
            fixDelete(x);
    }

public:
    RedBlackTree() { root = NULL; }

    void insert(int data) {
        Red_Black* node = new Red_Black(data);
        if (root == NULL) {
            root = node;
            root->color = false;
            return;
        }
        Red_Black* temp = root;
        Red_Black* parent = NULL;
        while (temp != NULL) {
            parent = temp;
            if (node->data < temp->data)
                temp = temp->left;
            else
                temp = temp->right;
        }
        node->parent = parent;
        if (node->data < parent->data)
            parent->left = node;
        else
            parent->right = node;
        fixInsert(node);
    }

    void insertMultiple() {
        int count, value;
        cout << "How many values to insert? ";
        cin >> count;
        cout << "Enter " << count << " values separated by space: ";
        for (int i = 0; i < count; i++) {
            cin >> value;
            insert(value);
        }
    }

    void remove(int data) {
        deleteNode(root, data);
    }

    void levelOrderDisplay() {
        if (root == NULL) {
            cout << "Tree is empty!\n";
            return;
        }
        queue<Red_Black*> q;
        q.push(root);
        while (!q.empty()) {
            Red_Black* temp = q.front();
            q.pop();
            cout << temp->data << (temp->color ? "(R) " : "(B) ");
            if (temp->left != NULL) q.push(temp->left);
            if (temp->right != NULL) q.push(temp->right);
        }
        cout << endl;
    }
};

int main() {
    RedBlackTree tree;
    int choice, data;
    while (true) {
        cout << "\n1. Insert\n2. Insert Multiple\n3. Level Order Display\n4. Delete\n5. Exit\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter data: ";
                cin >> data;
                tree.insert(data);
                break;
            case 2:
                tree.insertMultiple();
                break;
            case 3:
                tree.levelOrderDisplay();
                break;
            case 4:
                cout << "Enter data to delete: ";
                cin >> data;
                tree.remove(data);
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}
