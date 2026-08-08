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
    BST()
    {
        root = NULL;
    }

    Node *getRoot()
    {
        return root;
    }

    void create();
    void search();
    Node* searchRec(Node*, int);
    void preorder(Node*);
    void inorder(Node*);
    void postorder(Node*);
    void findMin(Node*);
    void findMax(Node*);
    void printASC(Node*);
    void printDESC(Node*);
};

void BST::findMin(Node *root)
{
    if (root == NULL) return;

    while (root->left != NULL)
        root = root->left;

    cout << "Minimum element is " << root->data << endl;
}

void BST::findMax(Node *root)
{
    if (root == NULL) return;

    while (root->right != NULL)
        root = root->right;

    cout << "Maximum element is " << root->data << endl;
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

            while (true)
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

Node* BST::searchRec(Node* root, int key)
{
    if (root == NULL)
        return NULL;

    if (root->data == key)
        return root;

    if (key < root->data)
        return searchRec(root->left, key);

    return searchRec(root->right, key);
}

void BST::preorder(Node *root)
{
    if (root == NULL) return;

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void BST::inorder(Node *root)
{
    if (root == NULL) return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void BST::postorder(Node *root)
{
    if (root == NULL) return;

    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

void BST::printASC(Node *root){
    if(root == NULL) return;

    printASC(root->left);
    cout << root->data << " ";
    printASC(root->right);
}

void BST::printDESC(Node *root){
    if(root == NULL) return;

    printDESC(root->right);
    cout << root->data << " ";
    printDESC(root->left);
}


int main()
{
    BST tree;
    int choice;

    do
    {
        cout << "----------ARSENAL----------\n";
        cout << "1. Create BST\n";
        cout << "2. Search Node\n";
        cout << "3. Preorder\n";
        cout << "4. Inorder\n";
        cout << "5. Postorder\n";
        cout << "6. Search Recursive\n";
        cout << "7. Find Minimum\n";
        cout << "8. Find Maximum\n";
        cout << "9. Print Ascending\n";
        cout << "10. Print Descending\n";
        cout << "11. Exit\n";

        cout << "Enter choice : ";
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
            tree.preorder(tree.getRoot());
            cout << endl;
            break;

        case 4:
            tree.inorder(tree.getRoot());
            cout << endl;
            break;

        case 5:
            tree.postorder(tree.getRoot());
            cout << endl;
            break;

        case 6:
        {
            int key;
            cout << "Enter value to search : ";
            cin >> key;

            Node* res = tree.searchRec(tree.getRoot(), key);

            if (res) cout << "Element Found\n";
            else cout << "Element Not Found\n";
            break;
        }

        case 7:
            tree.findMin(tree.getRoot());
            break;

        case 8:
            tree.findMax(tree.getRoot());
            break;

        case 9:
            tree.printASC(tree.getRoot());
            cout<<endl;
            break;

        case 10:
            tree.printDESC(tree.getRoot());
            cout<<endl;
            break;

        case 11:
            cout << "Thank You!\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 11);

    return 0;
}