#include <iostream>
#include <queue>
#include <stack>
using namespace std;
class TreeNode
{
private:
    int data;

public:
    TreeNode *left;
    TreeNode *right;
    TreeNode();
    int getData();
    void setData(int);
    ~TreeNode();
};
TreeNode::TreeNode()
{
    data = 0;
    left = nullptr;
    right = nullptr;
}
int TreeNode::getData()
{
    return data;
}
void TreeNode::setData(const int x)
{
    data = x;
}
TreeNode::~TreeNode()
{
    delete left;
    delete right;
}
class Tree
{
private:
    TreeNode *root;

public:
    Tree();
    void Insert();
    void preOrder();
    void postOrder();
    void inOrder();
    ~Tree();
};
Tree::Tree()
{
    root = nullptr;
}
void Tree::Insert()
{
    int temp;
    cout << "Enter the root Node : ";
    cin >> temp;
    root = new TreeNode();
    root->setData(temp);
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty())
    {
        TreeNode *front = q.front();
        q.pop();
        if (front != nullptr)
        {
            cout << "Enter the data of left child of " << front->getData() << " (enter -1 is not present) : ";
            cin >> temp;
            if (temp != -1)
            {
                front->left = new TreeNode();
                front->left->setData(temp);
                q.push(front->left);
            }
            cout << "Enter the data of right child of " << front->getData() << " (enter -1 is not present) : ";
            cin >> temp;
            if (temp != -1)
            {
                front->right = new TreeNode();
                front->right->setData(temp);
                q.push(front->right);
            }
        }
    }
}
void Tree::preOrder()
{
    stack<TreeNode *> stk;
    TreeNode *node = root;
    while (node != nullptr || !stk.empty())
    {
        if (node != nullptr)
        {
            cout << node->getData() << " ";
            stk.push(node);
            node = node->left;
        }
        else
        {
            node = stk.top();
            stk.pop();
            node = node->right;
        }
    }
    cout<<endl;
}
void Tree::postOrder()
{
    if (root == nullptr)
        return;
    stack<TreeNode *> st1, st2;
    st1.push(root);
    while (!st1.empty())
    {
        TreeNode *p = st1.top();
        st1.pop();
        st2.push(p);
        if (p->left != nullptr)
            st1.push(p->left);
        if (p->right != nullptr)
            st1.push(p->right);
    }
    while (!st2.empty())
    {
        cout << st2.top()->getData() << " ";
        st2.pop();
    }
    cout<<endl;
}
void Tree::inOrder()
{
    stack<TreeNode *> stk;
    TreeNode *node = root;
    while (node != nullptr || !stk.empty())
    {
        if (node != nullptr)
        {
            stk.push(node);
            node = node->left;
        }
        else
        {
            node = stk.top();
            stk.pop();
            cout << node->getData() << " ";
            node = node->right;
        }
    }
    cout<<endl;
}
Tree::~Tree()
{
    delete root;
}
int main()
{
    Tree x;
    x.Insert();
    x.inOrder();
    x.postOrder();
    x.preOrder();
    return 0;
}