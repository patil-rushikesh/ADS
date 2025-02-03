//This is a program which performs operation on threaded binary tree

#include <iostream>
#define MAX_VALUE 65536
using namespace std;
class Node
{ 
public:
    int data;
    Node *left, *right;
    bool left_thread, right_thread;
};
class ThreadedBinaryTree
{
private:
    Node *root;
public:
    ThreadedBinaryTree()
    { 
        root = new Node();
        root->right = root->left = root;
        root->left_thread = true;
        root->data = MAX_VALUE;
    }
    void makeEmpty()
    { 
        root = new Node();
        root->right = root->left = root;
        root->left_thread = true;
        root->data = MAX_VALUE;
    }
    void insert(int key)
    {
        Node *p = root;
        for (;;)
        {
            if (p->data < key)
            { // move to right thread
                if (p->right_thread)
                    break;
                p = p->right;
            }
            else if (p->data > key)
            { 
                if (p->left_thread)
                    break;
                p = p->left;
            }
            else
            {
                return;
            }
        }
        Node *temp = new Node();
        temp->data = key;
        temp->right_thread = temp->left_thread = true;
        if (p->data < key)
        {
            temp->right = p->right;
            temp->left = p;
            p->right = temp;
            p->right_thread = false;
        }
        else
        {
            temp->right = p;
            temp->left = p->left;
            p->left = temp;
            p->left_thread = false;
        }
    }
    bool search(int key)
    {
        Node *temp = root->left;
        for (;;)
        {
            if (temp->data < key)
            { 
                if (temp->right_thread)
                    return false;
                temp = temp->right;
            }
            else if (temp->data > key)
            { 
                if (temp->left_thread)
                    return false;
                temp = temp->left;
            }
            else
            {
                return true;
            }
        }
    }
    void Delete(int key)
    {
        Node *dest = root->left, *p = root;
        for (;;)
        { 
            if (dest->data < key)
            {
                if (dest->right_thread)
                    return;
                p = dest;
                dest = dest->right;
            }
            else if (dest->data > key)
            {
                if (dest->left_thread)
                    return;
                p = dest;
                dest = dest->left;
            }
            else
            {
                break;
            }
        }
        Node *target = dest;
        if (!dest->right_thread && !dest->left_thread)
        {
            p = dest;       
            target = dest->left; 
            while (!target->right_thread)
            {
                p = target;
                target = target->right;
            }
            dest->data = target->data; 
        }
        if (p->data >= target->data)
        {
            if (target->right_thread && target->left_thread)
            {
                p->left = target->left;
                p->left_thread = true;
            }
            else if (target->right_thread)
            {
                Node *largest = target->left;
                while (!largest->right_thread)
                {
                    largest = largest->right;
                }
                largest->right = p;
                p->left = target->left;
            }
            else
            {
                Node *smallest = target->right;
                while (!smallest->left_thread)
                {
                    smallest = smallest->left;
                }
                smallest->left = target->left;
                p->left = target->right;
            }
        }
        else
        { 
            if (target->right_thread && target->left_thread)
            {
                p->right = target->right;
                p->right_thread = true;
            }
            else if (target->right_thread)
            {
                Node *largest = target->left;
                while (!largest->right_thread)
                {
                    largest = largest->right;
                }
                largest->right = target->right;
                p->right = target->left;
            }
            else
            {
                Node *smallest = target->right;
                while (!smallest->left_thread)
                {
                    smallest = smallest->left;
                }
                smallest->left = p;
                p->right = target->right;
            }
        }
    }
    void displayTree()
    { 
        Node *temp = root, *p;
        for (;;)
        {
            p = temp;
            temp = temp->right;
            if (!p->right_thread)
            {
                while (!temp->left_thread)
                {
                    temp = temp->left;
                }
            }
            if (temp == root)
                break;
            cout << temp->data << " ";
        }
        cout << endl;
    }
};
int main()
{
    ThreadedBinaryTree tbt;
    cout << "ThreadedBinaryTree\n";
    char ch;
    int c, v;
    while (1)
    {
        cout << "1. Insert " << endl;
        cout << "2. Delete" << endl;
        cout << "3. Search" << endl;
        cout << "4. Clear" << endl;
        cout << "5. Display" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter Your Choice: ";
        cin >> c;
        switch (c)
        {
        case 1:
            cout << "Enter integer element to insert: ";
            cin >> v;
            tbt.insert(v);
            break;
        case 2:
            cout << "Enter integer element to delete: ";
            cin >> v;
            tbt.Delete(v);
            break;
        case 3:
            cout << "Enter integer element to search: ";
            cin >> v;
            if (tbt.search(v) == true)
                cout << "Element " << v << " found in the tree" << endl;
            else
                cout << "Element " << v << " not found in the tree" << endl;
            break;
        case 4:
            cout << "\nTree Cleared\n";
            tbt.makeEmpty();
            break;
        case 5:
            cout << "Display tree: \n ";
            tbt.displayTree();
            break;
        case 6:
            exit(1);
        default:
            cout << "\nInvalid type! \n";
        }
    }
    cout << "\n";
    return 0;
}
