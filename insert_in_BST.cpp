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

class Tree
{
private:
    TreeNode *root;

public:
    Tree() : root(nullptr) {}
    void InsertNode(int);
    void inorder(TreeNode *);
    TreeNode *getRoot() { return root; }
};

void Tree::InsertNode(int data)
{
    if (root == nullptr)
    {
        root = new TreeNode(data);
        return;
    }
    TreeNode *curr = root;
    TreeNode *parent = nullptr;
    while (curr != nullptr)
    {
        parent = curr;
        if (data < curr->data)
            curr = curr->left;
        else
            curr = curr->right;
    }
    if (data < parent->data)
        parent->left = new TreeNode(data);
    else
        parent->right = new TreeNode(data);
}

void Tree::inorder(TreeNode *curr)
{
    if (curr == nullptr)
        return;
    inorder(curr->left);
    cout << curr->data << " ";
    inorder(curr->right);
}

int main()
{
    Tree tree;
    tree.InsertNode(10);
    tree.InsertNode(5);
    tree.InsertNode(15);
    tree.InsertNode(2);
    tree.InsertNode(7);
    tree.InsertNode(12);
    tree.InsertNode(20);

    cout << "Inorder Traversal: ";
    tree.inorder(tree.getRoot());
    cout << endl;
    
    return 0;
}
