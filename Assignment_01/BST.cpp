// Storing a Binary Search tree in Nodes
#include <iostream>
#include <queue>
using namespace std;
class Tree
{
private:
    int data;

public:
    Tree *left;
    Tree *right;
    Tree();
    ~Tree();
    int getData();
    void setData(int);
};
Tree::Tree()
{
    data = 0;
    left = nullptr;
    right = nullptr;
}
int Tree::getData()
{
    return data;
}
void Tree::setData(const int x)
{
    data = x;
}
Tree::~Tree()
{
    delete left;
    delete right;
}
class TreeOperation
{
    Tree *root;

public:
    TreeOperation();
    void createTree();
    void preorder(Tree *);
    void postorder(Tree *);
    void inorder(Tree *);
    void Display();
};
TreeOperation::TreeOperation()
{
    root = nullptr;
}
void TreeOperation::createTree()
{
    int data;
    queue<Tree *> q;
    root = new Tree();
    cout << "Enter the data of root :";
    cin >> data;
    root->setData(data);
    q.push(root);
    while (!q.empty())
    {
        Tree *node = q.front();
        q.pop();
        if (node != nullptr)
        {
            cout << "Enter the data for left Child of " << node->getData() << " (if no data enter -1): ";
            cin >> data;
            if (data != -1)
            {
                node->left = new Tree();
                node->left->setData(data);
                q.push(node->left);
            }

            cout << "Enter the data for right Child of " << node->getData() << " (if no data enter -1): ";
            cin >> data;
            if (data != -1)
            {
                node->right = new Tree();
                node->right->setData(data);
                q.push(node->right);
            }
        }
    }
}
void TreeOperation::preorder(Tree *node)
{
    if (node != nullptr)
    {
        cout << node->getData() << " ";
        preorder(node->left);
        preorder(node->right);
    }
}
void TreeOperation::postorder(Tree *node)
{
    if (node != nullptr)
    {
        postorder(node->left);
        postorder(node->right);
        cout << node->getData() << " ";
    }
}
void TreeOperation::inorder(Tree *node)
{
    if (node != nullptr)
    {
        inorder(node->left);
        cout << node->getData() << " ";
        inorder(node->right);
    }
}
void TreeOperation::Display(){
    cout<<"PreOrder : ";
    preorder(root);
    cout<<endl;
    cout<<"PostOrder : ";
    postorder(root);
    cout<<endl;
    cout<<"Inorder : ";
    inorder(root);
    cout<<endl;
}
int main()
{
    TreeOperation obj;
    obj.createTree();
    obj.Display();
    return 0;
}