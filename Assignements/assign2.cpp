#include <iostream>
using namespace std;

class PlayerNode {
public:
    int id;
    int score;
    PlayerNode* left;
    PlayerNode* right;
    int height;

    PlayerNode(int pid, int val) {
        id = pid;
        score = val;
        left = NULL;
        right = NULL;
        height = 1;
    }
};

class PlayerTree {
public:
    PlayerNode* root;

    PlayerTree();

    void insert(int id, int score);
    void insert(PlayerNode*& root, int id, int score);

    PlayerNode* deleteNode(PlayerNode* root, int id);
    PlayerNode* minValueNode(PlayerNode* node);

    void inOrderDescending(PlayerNode* root);

    PlayerNode* rightRotate(PlayerNode* y);
    PlayerNode* leftRotate(PlayerNode* x);

    int height(PlayerNode* node);
    int balanceFactor(PlayerNode* node);

    void create();
};

PlayerTree::PlayerTree() {
    root = NULL;
}

void PlayerTree::insert(int id, int score) {
    insert(root, id, score);
}

void PlayerTree::insert(PlayerNode*& root, int id, int score) {
    if (root == NULL) {
        root = new PlayerNode(id, score);
        return;
    }

    if (score < root->score) {
        insert(root->left, id, score);
    } else {
        insert(root->right, id, score);
    }

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = balanceFactor(root);

    if (balance > 1 && score < root->left->score) {
        root = rightRotate(root);
    } else if (balance < -1 && score > root->right->score) {
        root = leftRotate(root);
    } else if (balance > 1 && score > root->left->score) {
        root->left = leftRotate(root->left);
        root = rightRotate(root);
    } else if (balance < -1 && score < root->right->score) {
        root->right = rightRotate(root->right);
        root = leftRotate(root);
    }
}

PlayerNode* PlayerTree::deleteNode(PlayerNode* root, int id) {
    if (root == NULL) {
        return root;
    }

    if (id < root->id) {
        root->left = deleteNode(root->left, id);
    } else if (id > root->id) {
        root->right = deleteNode(root->right, id);
    } else {
        if ((root->left == NULL) || (root->right == NULL)) {
            PlayerNode* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp; 
            }
            delete temp;
        } else {
            PlayerNode* temp = minValueNode(root->right);
            root->id = temp->id;
            root->score = temp->score;
            root->right = deleteNode(root->right, temp->id);
        }
    }

    if (root == NULL) return root;

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance = balanceFactor(root);

    if (balance > 1 && balanceFactor(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && balanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && balanceFactor(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && balanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

PlayerNode* PlayerTree::minValueNode(PlayerNode* node) {
    PlayerNode* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

void PlayerTree::inOrderDescending(PlayerNode* root) {
    if (root != NULL) {
        inOrderDescending(root->right);
        cout << "Player ID: " << root->id << " | Score: " << root->score << "\n";
        inOrderDescending(root->left);
    }
}

PlayerNode* PlayerTree::rightRotate(PlayerNode* y) {
    PlayerNode* x = y->left;
    PlayerNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

PlayerNode* PlayerTree::leftRotate(PlayerNode* x) {
    PlayerNode* y = x->right;
    PlayerNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int PlayerTree::height(PlayerNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int PlayerTree::balanceFactor(PlayerNode* node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

void PlayerTree::create() {
    int choice, id, score;
    while (true) {
        cout << "\n--- Player Score Tree Menu ---\n";
        cout << "1. Insert Player\n";
        cout << "2. Delete Player\n";
        cout << "3. Display Players\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Player ID and Score to insert: ";
                cin >> id >> score;
                insert(id, score);
                cout << "Player inserted successfully.\n";
                break;
            case 2:
                cout << "Enter Player ID to delete: ";
                cin >> id;
                root = deleteNode(root, id);
                cout << "Player deleted successfully.\n";
                break;
            case 3:
                cout << "Player Details:\n";
                inOrderDescending(root);
                break;
            case 4:
                cout << "Exiting...\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    PlayerTree tree;
    tree.create();
    return 0;
}
