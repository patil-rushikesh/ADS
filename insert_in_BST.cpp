#include <iostream>
#include <queue>
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
    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode *curr = q.front();
        q.pop();
        if (curr->left != nullptr)
            q.push(curr->left);
        else
        {
            curr->left = new TreeNode(data);
            return;
        }

        if (curr->right != nullptr)
            q.push(curr->right);
        else
        {
            curr->right = new TreeNode(data);
            return;
        }
    }
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
    tree.InsertNode(20);
    tree.InsertNode(30);
    tree.InsertNode(40);
    tree.InsertNode(50);
    tree.InsertNode(60);

    cout << "Inorder Traversal: ";
    tree.inorder(tree.getRoot());
    cout << endl;
    
    return 0;
}
