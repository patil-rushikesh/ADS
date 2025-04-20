#include <iostream>
#include <queue>
using namespace std;

class Node
{
public:
    int data;
    Node *left, *right;

    Node(int val)
    {
        data = val;
        left = right = nullptr;
    }
};

class BinaryTree
{
private:
    Node *root;

    Node *insert(Node *node, int val)
    {
        if (!node)
            return new Node(val);
        if (val < node->data)
        {
            node->left = insert(node->left, val);
        }
        else
        {
            node->right = insert(node->right, val);
        }
        return node;
    }

    Node *findMin(Node *node)
    {
        while (node && node->left)
            node = node->left;
        return node;
    }

    Node *deleteNode(Node *node, int val)
    {
        if (!node)
            return nullptr;

        if (val < node->data)
            node->left = deleteNode(node->left, val);
        else if (val > node->data)
            node->right = deleteNode(node->right, val);
        else
        {
            if (!node->left && !node->right)
            {
                delete node;
                return nullptr;
            }
            else if (!node->left)
            {
                Node *temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right)
            {
                Node *temp = node->left;
                delete node;
                return temp;
            }
            else
            {
                Node *temp = findMin(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data);
            }
        }
        return node;
    }

    void inorder(Node *node)
    {
        if (!node)
            return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(Node *node)
    {
        if (!node)
            return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node *node)
    {
        if (!node)
            return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    void levelOrder(Node *node)
    {
        if (!node)
            return;
        queue<Node *> q;
        q.push(node);
        while (!q.empty())
        {
            Node *current = q.front();
            q.pop();
            cout << current->data << " ";
            if (current->left)
                q.push(current->left);
            if (current->right)
                q.push(current->right);
        }
    }

    int countNodes(Node *node)
    {
        if (!node)
            return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    int countLeafNodes(Node *node)
    {
        if (!node)
            return 0;
        if (!node->left && !node->right)
            return 1;
        return countLeafNodes(node->left) + countLeafNodes(node->right);
    }

    int height(Node *node)
    {
        if (!node)
            return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    void mirror(Node *node)
    {
        if (!node)
            return;
        mirror(node->left);
        mirror(node->right);
        swap(node->left, node->right);
    }

    Node *copy(Node *node)
    {
        if (!node)
            return nullptr;
        Node *newNode = new Node(node->data);
        newNode->left = copy(node->left);
        newNode->right = copy(node->right);
        return newNode;
    }

    void deleteTree(Node *node)
    {
        if (!node)
            return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    BinaryTree()
    {
        root = nullptr;
    }

    ~BinaryTree()
    {
        deleteTree(root);
    }

    void insert(int val)
    {
        root = insert(root, val);
    }

    void deleteValue(int val)
    {
        root = deleteNode(root, val);
    }

    void inorder()
    {
        cout << "Inorder: ";
        inorder(root);
        cout << endl;
    }

    void preorder()
    {
        cout << "Preorder: ";
        preorder(root);
        cout << endl;
    }

    void postorder()
    {
        cout << "Postorder: ";
        postorder(root);
        cout << endl;
    }

    void levelOrder()
    {
        cout << "Level Order: ";
        levelOrder(root);
        cout << endl;
    }

    void countNodes()
    {
        cout << "Total Nodes: " << countNodes(root) << endl;
    }

    void countLeafNodes()
    {
        cout << "Leaf Nodes: " << countLeafNodes(root) << endl;
    }

    void height()
    {
        cout << "Height: " << height(root) << endl;
    }

    void mirror()
    {
        mirror(root);
        cout << "Tree mirrored.\n";
    }

    void copyTree()
    {
        Node *newRoot = copy(root);
        cout << "Copied Tree Inorder: ";
        inorder(newRoot);
        cout << endl;
        deleteTree(newRoot); // Clean copied tree memory
    }
};

// === Menu ===
void displayMenu()
{
    cout << "\n========== Binary Tree Menu ==========\n";
    cout << "1. Insert Node\n";
    cout << "2. Delete Node\n";
    cout << "3. Inorder Traversal\n";
    cout << "4. Preorder Traversal\n";
    cout << "5. Postorder Traversal\n";
    cout << "6. Level Order Traversal\n";
    cout << "7. Count Total Nodes\n";
    cout << "8. Count Leaf Nodes\n";
    cout << "9. Height of Tree\n";
    cout << "10. Mirror the Tree\n";
    cout << "11. Copy the Tree (display inorder)\n";
    cout << "0. Exit\n";
    cout << "======================================\n";
    cout << "Enter your choice: ";
}

int main()
{
    BinaryTree tree;
    int choice, value;

    do
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            tree.insert(value);
            break;
        case 2:
            cout << "Enter value to delete: ";
            cin >> value;
            tree.deleteValue(value);
            break;
        case 3:
            tree.inorder();
            break;
        case 4:
            tree.preorder();
            break;
        case 5:
            tree.postorder();
            break;
        case 6:
            tree.levelOrder();
            break;
        case 7:
            tree.countNodes();
            break;
        case 8:
            tree.countLeafNodes();
            break;
        case 9:
            tree.height();
            break;
        case 10:
            tree.mirror();
            break;
        case 11:
            tree.copyTree();
            break;
        case 0:
            cout << "Exiting and cleaning up memory.\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
