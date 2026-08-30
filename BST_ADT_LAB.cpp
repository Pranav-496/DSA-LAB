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

    Node *insertNode(Node *, int);
    Node *deleteNode(Node *, int);

    int countTotal(Node *);
    int countLeaf(Node *);
    int countInternal(Node *);
    int heightRec(Node *);

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
    Node *searchRec(Node *, int);

    void findMin(Node *);
    void findMax(Node *);

    void printASC(Node *);
    void printDESC(Node *);

    int height(Node *);
    int totalNodes(Node *);
    int leafNodes(Node *);
    int internalNodes(Node *);

    void mirror(Node *);

    void update();
};

// TC: O(h)  SC: O(1)  [h = height of tree]
void BST::findMin(Node *root)
{
    if (root == NULL)
    {
        cout << "BST is empty\n";
        return;
    }

    while (root->left != NULL)
        root = root->left;

    cout << "Minimum element is " << root->data << endl;
}

// TC: O(h)  SC: O(1)
void BST::findMax(Node *root)
{
    if (root == NULL)
    {
        cout << "BST is empty\n";
        return;
    }

    while (root->right != NULL)
        root = root->right;

    cout << "Maximum element is " << root->data << endl;
}

// TC: O(h) per insertion  SC: O(1)
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

// TC: O(h)  SC: O(1)
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

// TC: O(h)  SC: O(h) [recursive call stack]
Node *BST::searchRec(Node *root, int key)
{
    if (root == NULL)
        return NULL;

    if (root->data == key)
        return root;

    if (key < root->data)
        return searchRec(root->left, key);

    return searchRec(root->right, key);
}

// Print Ascending - Inorder of BST gives sorted order
// TC: O(n)  SC: O(h) [recursive call stack]
void BST::printASC(Node *root)
{
    if (root == NULL)
        return;

    printASC(root->left);
    cout << root->data << " ";
    printASC(root->right);
}

// Print Descending - Reverse Inorder of BST
// TC: O(n)  SC: O(h) [recursive call stack]
void BST::printDESC(Node *root)
{
    if (root == NULL)
        return;

    printDESC(root->right);
    cout << root->data << " ";
    printDESC(root->left);
}

// TC: O(n)  SC: O(h) [recursive call stack]
int BST::heightRec(Node *root)
{
    if (root == NULL)
        return 0;

    return 1 + max(heightRec(root->left),
                   heightRec(root->right));
}

// TC: O(n)  SC: O(h)
int BST::height(Node *root)
{
    return heightRec(root);
}

// TC: O(n)  SC: O(h) [recursive call stack]
int BST::countTotal(Node *root)
{
    if (root == NULL)
        return 0;

    return 1 + countTotal(root->left) + countTotal(root->right);
}

// TC: O(n)  SC: O(h)
int BST::totalNodes(Node *root)
{
    return countTotal(root);
}

// TC: O(n)  SC: O(h) [recursive call stack]
int BST::countLeaf(Node *root)
{
    if (root == NULL)
        return 0;

    if (root->left == NULL && root->right == NULL)
        return 1;

    return countLeaf(root->left) + countLeaf(root->right);
}

// TC: O(n)  SC: O(h)
int BST::leafNodes(Node *root)
{
    return countLeaf(root);
}

// TC: O(n)  SC: O(h) [recursive call stack]
int BST::countInternal(Node *root)
{
    if (root == NULL)
        return 0;

    if (root->left == NULL && root->right == NULL)
        return 0;

    return 1 + countInternal(root->left) + countInternal(root->right);
}

// TC: O(n)  SC: O(h)
int BST::internalNodes(Node *root)
{
    return countInternal(root);
}

// TC: O(n)  SC: O(h) [recursive call stack]
void BST::mirror(Node *root)
{
    if (root == NULL)
        return;

    swap(root->left, root->right);

    mirror(root->left);
    mirror(root->right);
}

// TC: O(h)  SC: O(h) [recursive call stack]
Node *BST::insertNode(Node *root, int val)
{
    if (root == NULL)
        return new Node(val);

    if (val < root->data)
        root->left = insertNode(root->left, val);

    else if (val > root->data)
        root->right = insertNode(root->right, val);

    return root;
}

// TC: O(h)  SC: O(h) [recursive call stack]
Node *BST::deleteNode(Node *root, int val)
{
    if (root == NULL)
        return NULL;

    if (val < root->data)
    {
        root->left = deleteNode(root->left, val);
    }
    else if (val > root->data)
    {
        root->right = deleteNode(root->right, val);
    }
    else
    {
        if (root->left == NULL)
        {
            Node *temp = root->right;
            delete root;
            return temp;
        }

        if (root->right == NULL)
        {
            Node *temp = root->left;
            delete root;
            return temp;
        }

        Node *temp = root->right;

        while (temp->left != NULL)
            temp = temp->left;

        root->data = temp->data;

        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

// TC: O(h)  SC: O(h) [search + delete + insert]
void BST::update()
{
    int oldValue, newValue;

    cout << "Enter value to update : ";
    cin >> oldValue;

    Node *temp = searchRec(root, oldValue);

    if (temp == NULL)
    {
        cout << "Element Not Found.\n";
        return;
    }

    cout << "Enter new value : ";
    cin >> newValue;

    if (searchRec(root, newValue) != NULL)
    {
        cout << "New value already exists.\n";
        return;
    }

    root = deleteNode(root, oldValue);
    root = insertNode(root, newValue);

    cout << "Node updated successfully.\n";
}

int main()
{
    BST tree;

    int choice;

    do
    {
        cout << "\n---------- BST ADT ----------\n";

        cout << "1. Create BST\n";
        cout << "2. Search Node\n";
        cout << "3. Search Recursive\n";
        cout << "4. Find Minimum\n";
        cout << "5. Find Maximum\n";
        cout << "6. Print Ascending\n";
        cout << "7. Print Descending\n";
        cout << "8. Find Height\n";
        cout << "9. Count Total Nodes\n";
        cout << "10. Count Leaf Nodes\n";
        cout << "11. Count Internal Nodes\n";
        cout << "12. Find Mirror\n";
        cout << "13. Update Node\n";
        cout << "14. Exit\n";

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
        {
            int key;

            cout << "Enter value to search : ";
            cin >> key;

            Node *res = tree.searchRec(tree.getRoot(), key);

            if (res != NULL)
                cout << "Element Found\n";
            else
                cout << "Element Not Found\n";

            break;
        }

        case 4:
            tree.findMin(tree.getRoot());
            break;

        case 5:
            tree.findMax(tree.getRoot());
            break;

        case 6:
            cout << "Ascending : ";
            tree.printASC(tree.getRoot());
            cout << endl;
            break;

        case 7:
            cout << "Descending : ";
            tree.printDESC(tree.getRoot());
            cout << endl;
            break;

        case 8:
            cout << "Height = "
                 << tree.height(tree.getRoot()) << endl;
            break;

        case 9:
            cout << "Total Nodes = "
                 << tree.totalNodes(tree.getRoot()) << endl;
            break;

        case 10:
            cout << "Leaf Nodes = "
                 << tree.leafNodes(tree.getRoot()) << endl;
            break;

        case 11:
            cout << "Internal Nodes = "
                 << tree.internalNodes(tree.getRoot()) << endl;
            break;

        case 12:
            tree.mirror(tree.getRoot());

            cout << "Mirror tree created.\n";
            cout << "Inorder of mirror : ";
            tree.printASC(tree.getRoot());
            cout << endl;

            break;

        case 13:
            tree.update();
            break;

        case 14:
            cout << "Thank You!\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 14);

    return 0;
}