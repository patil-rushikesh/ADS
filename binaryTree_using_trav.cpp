#include <iostream>
#include <vector>
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
    vector<int> inOrder;
    vector<int> postOrder;
    int search(vector<int> &arr, int start, int end, int value)
    {
        for (int i = start; i <= end; i++)
            if (arr[i] == value)
                return i;
        return -1;
    }
    TreeNode *buildUtil(int inStart, int inEnd, int &postIndex)
    {
        if (inStart > inEnd)
        {
            return nullptr;
        }

        TreeNode *node = new TreeNode(postOrder[postIndex--]);
        if (inStart == inEnd)
        {
            return node;
        }

        int inIndex = search(inOrder, inStart, inEnd, node->data);
        node->right = buildUtil(inIndex + 1, inEnd, postIndex);
        node->left = buildUtil(inStart, inIndex - 1, postIndex);
        return node;
    }

public:
    Tree() : root(nullptr) {}
    void getTraversal()
    {
        int n;
        cout << "Enter the number of nodes: ";
        cin >> n;

        cout << "Enter the values of the in-order traversal:\n";
        inOrder.resize(n);
        for (int &val : inOrder)
            cin >> val;

        cout << "Enter the values of the post-order traversal:\n";
        postOrder.resize(n);
        for (int &val : postOrder)
            cin >> val;
    }
    void createBT()
    {
        int postIndex = postOrder.size() - 1;
        root = buildUtil(0, inOrder.size() - 1, postIndex);
    }
    void displayBT()
    {
        cout << "Displaying the Binary Tree in Pre-order traversal:\n";
        print(root);
        cout << endl;
    }
    void print(TreeNode *node)
    {
        if (!node)
            return;
        cout << node->data << " ";
        print(node->left);
        print(node->right);
    }
    void deleteTree(TreeNode *node)
    {
        if (node == nullptr)
        {
            return;
        }
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
    ~Tree()
    {
        delete root;
    }
};
int main()
{
    Tree tree;
    tree.getTraversal();
    tree.createBT();
    tree.displayBT();
    return 0;
}
