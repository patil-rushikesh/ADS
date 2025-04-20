#include <iostream>
using namespace std;

enum Color { RED, BLACK };

class Node {
public:
    int value;
    Node* left;
    Node* right;
    Node* parent;
    Color color;

    Node(int value) {
        this->value = value;
        left = right = parent = nullptr;
        color = RED;
    }
};

class RedBlackTree {
private:
    Node* root;
    Node* TNULL;

    void leftRotate(Node* node) {
        Node* rightChild = node->right;
        node->right = rightChild->left;
        if (rightChild->left != TNULL) {
            rightChild->left->parent = node;
        }
        rightChild->parent = node->parent;
        if (node->parent == nullptr) {
            root = rightChild;
        } else if (node == node->parent->left) {
            node->parent->left = rightChild;
        } else {
            node->parent->right = rightChild;
        }
        rightChild->left = node;
        node->parent = rightChild;
    }

    void rightRotate(Node* node) {
        Node* leftChild = node->left;
        node->left = leftChild->right;
        if (leftChild->right != TNULL) {
            leftChild->right->parent = node;
        }
        leftChild->parent = node->parent;
        if (node->parent == nullptr) {
            root = leftChild;
        } else if (node == node->parent->right) {
            node->parent->right = leftChild;
        } else {
            node->parent->left = leftChild;
        }
        leftChild->right = node;
        node->parent = leftChild;
    }

    void fixInsert(Node* node) {
        Node* uncle;
        while (node->parent->color == RED) {
            if (node->parent == node->parent->parent->right) {
                uncle = node->parent->parent->left;
                if (uncle->color == RED) {
                    uncle->color = BLACK;
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rightRotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    leftRotate(node->parent->parent);
                }
            } else {
                uncle = node->parent->parent->right;
                if (uncle->color == RED) {
                    uncle->color = BLACK;
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        leftRotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rightRotate(node->parent->parent);
                }
            }
            if (node == root) {
                break;
            }
        }
        root->color = BLACK;
    }

    void insertNode(int value) {
        Node* newNode = new Node(value);
        Node* parent = nullptr;
        Node* currentNode = root;

        while (currentNode != TNULL) {
            parent = currentNode;
            if (newNode->value < currentNode->value) {
                currentNode = currentNode->left;
            } else {
                currentNode = currentNode->right;
            }
        }

        newNode->parent = parent;
        if (parent == nullptr) {
            root = newNode;
        } else if (newNode->value < parent->value) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        newNode->left = TNULL;
        newNode->right = TNULL;
        newNode->color = RED;

        fixInsert(newNode);
    }

    void inorderHelper(Node* node) {
        if (node != TNULL) {
            inorderHelper(node->left);
            cout << node->value << " ";
            inorderHelper(node->right);
        }
    }

    Node* minimum(Node* node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void fixDelete(Node* node) {
        Node* sibling;
        while (node != root && node->color == BLACK) {
            if (node == node->parent->left) {
                sibling = node->parent->right;
                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    leftRotate(node->parent);
                    sibling = node->parent->right;
                }
                if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                    sibling->color = RED;
                    node = node->parent;
                } else {
                    if (sibling->right->color == BLACK) {
                        sibling->left->color = BLACK;
                        sibling->color = RED;
                        rightRotate(sibling);
                        sibling = node->parent->right;
                    }
                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    sibling->right->color = BLACK;
                    leftRotate(node->parent);
                    node = root;
                }
            } else {
                sibling = node->parent->left;
                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    rightRotate(node->parent);
                    sibling = node->parent->left;
                }
                if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                    sibling->color = RED;
                    node = node->parent;
                } else {
                    if (sibling->left->color == BLACK) {
                        sibling->right->color = BLACK;
                        sibling->color = RED;
                        leftRotate(sibling);
                        sibling = node->parent->left;
                    }
                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    sibling->left->color = BLACK;
                    rightRotate(node->parent);
                    node = root;
                }
            }
        }
        node->color = BLACK;
    }

    void deleteNodeHelper(Node* node, int value) {
        Node* targetNode = TNULL;
        Node* replaceNode, * temp;
        while (node != TNULL) {
            if (node->value == value) {
                targetNode = node;
            }
            if (node->value <= value) {
                node = node->right;
            } else {
                node = node->left;
            }
        }

        if (targetNode == TNULL) {
            cout << "Key not found\n";
            return;
        }

        temp = targetNode;
        Color originalColor = temp->color;
        if (targetNode->left == TNULL) {
            replaceNode = targetNode->right;
            transplant(targetNode, targetNode->right);
        } else if (targetNode->right == TNULL) {
            replaceNode = targetNode->left;
            transplant(targetNode, targetNode->left);
        } else {
            temp = minimum(targetNode->right);
            originalColor = temp->color;
            replaceNode = temp->right;
            if (temp->parent == targetNode) {
                replaceNode->parent = temp;
            } else {
                transplant(temp, temp->right);
                temp->right = targetNode->right;
                temp->right->parent = temp;
            }
            transplant(targetNode, temp);
            temp->left = targetNode->left;
            temp->left->parent = temp;
            temp->color = targetNode->color;
        }
        if (originalColor == BLACK) {
            fixDelete(replaceNode);
        }
    }

public:
    RedBlackTree() {
        TNULL = new Node(0);
        TNULL->color = BLACK;
        root = TNULL;
    }

    void insert(int value) {
        insertNode(value);
    }

    void deleteNode(int value) {
        deleteNodeHelper(root, value);
    }

    void inorder() {
        inorderHelper(root);
    }
};

int main() {
    RedBlackTree tree;
    int choice, value;

    do {
        cout << "\n========== Red-Black Tree Menu ==========\n";
        cout << "1. Insert Node\n";
        cout << "2. Delete Node\n";
        cout << "3. Display Tree (Inorder Traversal)\n";
        cout << "0. Exit\n";
        cout << "=========================================\n";
        cout << "Enter your choice: ";
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
            cout << "Inorder Traversal: ";
            tree.inorder();
            cout << endl;
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
