
// create : done
// search : done
// insert : done
// traversal ----
    // inorder : done
    // preorder : done
    // postorder : done
// clone : done
// mirror : done
// delete ----
    // leaf node : done
    // internal node : done
    // intermediate node : done
// level-wise display : done

#include <iostream>
using namespace std;

class TreeNode {
public:
    int data;
    TreeNode *left, *right;

    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

class Tree {
public:
    TreeNode *root;
    Tree();
    void insert(int value);
    void insert(TreeNode*& root, int value);
    void inOrder(TreeNode* root);
    void preOrder(TreeNode* root);
    void postOrder(TreeNode* root);
    TreeNode* deleteNode(TreeNode* root, int key);
    TreeNode* clone(TreeNode* root);
    void mirror(TreeNode*& root);
    bool search(TreeNode* root, int key);
    int height(TreeNode* root);
    void displayLevel(TreeNode* root, int level);
    void levelOrderTraversal(TreeNode* root);
    void create();
};

Tree::Tree() {
    root = nullptr;
}

void Tree::insert(TreeNode*& root, int value) {
    if (root == nullptr) {
        root = new TreeNode(value);
    } else if (value < root->data) {
        insert(root->left, value);
    } else {
        insert(root->right, value);
    }
}

void Tree::insert(int value) {
    insert(root, value);
}

void Tree::inOrder(TreeNode* root) {
    if (root != nullptr) {
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }
}

void Tree::preOrder(TreeNode* root) {
    if (root != nullptr) {
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void Tree::postOrder(TreeNode* root) {
    if (root != nullptr) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->data << " ";
    }
}

TreeNode* Tree::clone(TreeNode* root) {
    if (root == nullptr) return nullptr;
    TreeNode* newNode = new TreeNode(root->data);
    newNode->left = clone(root->left);
    newNode->right = clone(root->right);
    return newNode;
}

void Tree::mirror(TreeNode*& root) {
    if (root == nullptr) return;
    swap(root->left, root->right);
    mirror(root->left);
    mirror(root->right);
}

bool Tree::search(TreeNode* root, int key) {
    if (root == nullptr) return false;
    if (root->data == key) return true;
    if (key < root->data) return search(root->left, key);
    return search(root->right, key);
}

TreeNode* Tree::deleteNode(TreeNode* root, int key) {
    if (root == nullptr) return root;

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        TreeNode* successor = root->right;
        while (successor->left != nullptr) {
            successor = successor->left;
        }
        root->data = successor->data;
        root->right = deleteNode(root->right, successor->data);
    }
    return root;
}

int Tree::height(TreeNode* root) {
    if (root == nullptr) return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

void Tree::displayLevel(TreeNode* root, int level) {
    if (root == nullptr) return;
    if (level == 1) {
        cout << root->data << " ";
    } else {
        displayLevel(root->left, level - 1);
        displayLevel(root->right, level - 1);
    }
}

void Tree::levelOrderTraversal(TreeNode* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        displayLevel(root, i);
        cout << endl;
    }
}

void Tree::create() {
    int choice, value;
    do {
        cout << "\n--- Tree Operations ---\n";
        cout << "1. Insert multiple nodes into the tree\n";
        cout << "2. Insert a single node into the tree\n";
        cout << "3. Display in-order traversal\n";
        cout << "4. Display pre-order traversal\n";
        cout << "5. Display post-order traversal\n";
        cout << "6. Delete a node from the tree\n";
        cout << "7. Clone the tree and display in-order traversal\n";
        cout << "8. Mirror the tree and display in-order traversal\n";
        cout << "9. Search for a node\n";
        cout << "10. Display dictionary level-wise\n";
        cout << "11. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int n;
                cout << "How many nodes to insert? ";
                cin >> n;
                for (int i = 0; i < n; i++) {
                    cout << "Enter value " << (i + 1) << ": ";
                    cin >> value;
                    insert(value);
                }
                cout << "Nodes inserted successfully.\n";
                break;
            }
            case 2:
                cout << "Enter value to insert: ";
                cin >> value;
                insert(value);
                cout << "Node inserted successfully.\n";
                break;
            case 3:
                cout << "In-order traversal: ";
                inOrder(root);
                cout << "\n";
                break;
            case 4:
                cout << "Pre-order traversal: ";
                preOrder(root);
                cout << "\n";
                break;
            case 5:
                cout << "Post-order traversal: ";
                postOrder(root);
                cout << "\n";
                break;
            case 6:
                cout << "Enter value to delete: ";
                cin >> value;
                root = deleteNode(root, value);
                cout << "Node deleted successfully.\n";
                break;
            case 7: {
                TreeNode* clonedRoot = clone(root);
                cout << "Cloned tree in-order traversal: ";
                inOrder(clonedRoot);
                cout << "\n";
                break;
            }
            case 8:
                mirror(root);
                cout << "Mirrored tree in-order traversal: ";
                inOrder(root);
                cout << "\n";
                break;
            case 9:
                cout << "Enter value to search: ";
                cin >> value;
                if (search(root, value)) {
                    cout << "Value found in the dictionary.\n";
                } else {
                    cout << "Value not found in the dictionary.\n";
                }
                break;
            case 10:
                cout << "Dictionary displayed level-wise:\n";
                levelOrderTraversal(root);
                break;
            case 11:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 11);
}

int main() {
    Tree tree;
    tree.create();
    return 0;
}
