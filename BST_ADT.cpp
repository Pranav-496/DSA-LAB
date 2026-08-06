#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;

    Node(int val)
    {
        data = val;
        left = NULL;
        right = NULL;
    }
};

class BST
{
private:
    Node *root;

public:
    BST();

    void create();
    void search();

    void preorder(Node *);
    void inorder(Node *);
    void postorder(Node *);

    Node *getRoot();
};


BST::BST()
{
    root = NULL;
}

Node *BST::getRoot()
{
    return root;
}


void BST::create()
{
    char ch;

    do
    {
        int val;
        cout << "Enter value : ";
        cin >> val;

        Node *newNode = new Node(val);

        if (root == NULL)
        {
            root = newNode;
        }
        else
        {
            Node *temp = root;

            while (1)
            {
                if (val < temp->data)
                {
                    if (temp->left == NULL)
                    {
                        temp->left = newNode;
                        break;
                    }
                    temp = temp->left;
                }
                else if (val > temp->data)
                {
                    if (temp->right == NULL)
                    {
                        temp->right = newNode;
                        break;
                    }
                    temp = temp->right;
                }
                else
                {
                    cout << "Duplicate value not allowed.\n";
                    delete newNode;
                    break;
                }
            }
        }

        cout << "Do you want to insert another node? (y/n) : ";
        cin >> ch;

    } while (ch == 'y' || ch == 'Y');
}


void BST::search()
{
    int key;

    cout << "Enter value to search : ";
    cin >> key;

    Node *temp = root;

    while (temp != NULL)
    {
        if (temp->data == key)
        {
            cout << "Element Found.\n";
            return;
        }

        if (key < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }

    cout << "Element Not Found.\n";
}


void BST::preorder(Node *root)
{
    if (root == NULL)
        return;

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}


void BST::inorder(Node *root)
{
    if (root == NULL)
        return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

//================ Postorder ================//

void BST::postorder(Node *root)
{
    if (root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}


int main()
{
    BST tree;
    int choice;

    do
    {
        cout << "\n========== MENU ==========\n";
        cout << "1. Create BST\n";
        cout << "2. Search Node\n";
        cout << "3. Preorder Traversal\n";
        cout << "4. Inorder Traversal\n";
        cout << "5. Postorder Traversal\n";
        cout << "6. Exit\n";

        cout << "Enter your choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            tree.create();
            break;

        case 2:
            tree.search();
            break;

        case 3:
            cout << "Preorder : ";
            tree.preorder(tree.getRoot());
            cout << endl;
            break;

        case 4:
            cout << "Inorder : ";
            tree.inorder(tree.getRoot());
            cout << endl;
            break;

        case 5:
            cout << "Postorder : ";
            tree.postorder(tree.getRoot());
            cout << endl;
            break;

        case 6:
            cout << "Thank You!\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}