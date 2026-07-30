#include <bits/stdc++.h>
using namespace std;

class node
{
public:
    int val;
    node *left;
    node *right;

    node(int data)
    {
        val = data;
        left = NULL;
        right = NULL;
    }
};

class btree
{
    node *root;

public:
    btree()
    {
        root = NULL;
    }

    node *getRoot();

    void InsertNode(node *);
    void Display(node *);

    int CountNode(node *);
    int CountLeaf(node *);
};

node *btree::getRoot()
{
    return root;
}

void btree::InsertNode(node *temp)
{
    if (root == NULL)
    {
        root = temp;
        return;
    }

    node *curr = root;

    while (true)
    {
        char ch;

        cout << "\nCurrent Node = " << curr->val;
        cout << "\nInsert Left (L) or Right (R): ";
        cin >> ch;

        if (ch == 'L' || ch == 'l')
        {
            if (curr->left == NULL)
            {
                curr->left = temp;
                return;
            }
            curr = curr->left;
        }
        else if (ch == 'R' || ch == 'r')
        {
            if (curr->right == NULL)
            {
                curr->right = temp;
                return;
            }
            curr = curr->right;
        }
        else
        {
            cout << "Invalid Choice!\n";
        }
    }
}

// Level Order Traversal
void btree::Display(node *temp)
{
    if (temp == NULL)
    {
        cout << "Tree is Empty!" << endl;
        return;
    }

    queue<node *> q;
    q.push(temp);

    while (!q.empty())
    {
        node *curr = q.front();
        q.pop();

        cout << curr->val << " ";

        if (curr->left != NULL)
            q.push(curr->left);

        if (curr->right != NULL)
            q.push(curr->right);
    }

    cout << endl;
}

int btree::CountNode(node *temp)
{
    if (temp == NULL)
        return 0;

    return 1 + CountNode(temp->left) + CountNode(temp->right);
}

int btree::CountLeaf(node *temp)
{
    if (temp == NULL)
        return 0;

    if (temp->left == NULL && temp->right == NULL)
        return 1;

    return CountLeaf(temp->left) + CountLeaf(temp->right);
}

int main()
{
    btree tree;
    int choice, value;

    do
    {
        cout << "\n========== Binary Tree ==========\n";
        cout << "1. Insert Node\n";
        cout << "2. Count Total Nodes\n";
        cout << "3. Count Leaf Nodes\n";
        cout << "4. Display (Level Order)\n";
        cout << "5. Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter Value: ";
            cin >> value;
            tree.InsertNode(new node(value));
            break;

        case 2:
            cout << "Total Nodes = "
                 << tree.CountNode(tree.getRoot()) << endl;
            break;

        case 3:
            cout << "Leaf Nodes = "
                 << tree.CountLeaf(tree.getRoot()) << endl;
            break;

        case 4:
            cout << "Level Order Traversal : ";
            tree.Display(tree.getRoot());
            cout << endl;
            break;

        case 5:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 5);

    return 0;
}