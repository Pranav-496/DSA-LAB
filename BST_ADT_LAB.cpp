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

    Node *constructPreIn(vector<int> &pre, vector<int> &in, int &preIndex, int start, int end);
    Node *constructPostIn(vector<int> &post, vector<int> &in, int &postIndex, int start, int end);

    Node *insertNode(Node *, int);
    Node *deleteNode(Node *, int);

    int countTotal(Node *);
    int countLeaf(Node *);
    int countInternal(Node *);
    int heightRec(Node *);
    bool equalTree(Node *, Node *);

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

    void preorder(Node *);
    void inorder(Node *);
    void postorder(Node *);

    void findMin(Node *);
    void findMax(Node *);

    void printASC(Node *);
    void printDESC(Node *);

    int height(Node *);
    int totalNodes(Node *);
    int leafNodes(Node *);
    int internalNodes(Node *);

    void mirror(Node *);
    bool isEqual(Node *, Node *);

    void update();

    void constructFromPreIn();
    void constructFromPostIn();
};

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

void BST::preorder(Node *root)
{
    if (root == NULL)
        return;

    stack<Node *> s;

    s.push(root);

    while (!s.empty())
    {
        Node *temp = s.top();
        s.pop();

        cout << temp->data << " ";

        if (temp->right != NULL)
            s.push(temp->right);

        if (temp->left != NULL)
            s.push(temp->left);
    }
}

void BST::inorder(Node *root)
{
    stack<Node *> s;

    Node *temp = root;

    while (temp != NULL || !s.empty())
    {
        while (temp != NULL)
        {
            s.push(temp);
            temp = temp->left;
        }

        temp = s.top();
        s.pop();

        cout << temp->data << " ";

        temp = temp->right;
    }
}

void BST::postorder(Node *root)
{
    if (root == NULL)
        return;

    stack<Node *> s1;
    stack<Node *> s2;

    s1.push(root);

    while (!s1.empty())
    {
        Node *temp = s1.top();
        s1.pop();

        s2.push(temp);

        if (temp->left != NULL)
            s1.push(temp->left);

        if (temp->right != NULL)
            s1.push(temp->right);
    }

    while (!s2.empty())
    {
        cout << s2.top()->data << " ";
        s2.pop();
    }
}

void BST::printASC(Node *root)
{
    inorder(root);
}

void BST::printDESC(Node *root)
{
    if (root == NULL)
        return;

    stack<Node *> s;

    Node *temp = root;

    while (temp != NULL || !s.empty())
    {
        while (temp != NULL)
        {
            s.push(temp);
            temp = temp->right;
        }

        temp = s.top();
        s.pop();

        cout << temp->data << " ";

        temp = temp->left;
    }
}

int BST::heightRec(Node *root)
{
    if (root == NULL)
        return 0;

    return 1 + max(heightRec(root->left),
                   heightRec(root->right));
}

int BST::height(Node *root)
{
    return heightRec(root);
}

int BST::countTotal(Node *root)
{
    if (root == NULL)
        return 0;

    return 1 + countTotal(root->left) + countTotal(root->right);
}

int BST::totalNodes(Node *root)
{
    return countTotal(root);
}

int BST::countLeaf(Node *root)
{
    if (root == NULL)
        return 0;

    if (root->left == NULL && root->right == NULL)
        return 1;

    return countLeaf(root->left) + countLeaf(root->right);
}

int BST::leafNodes(Node *root)
{
    return countLeaf(root);
}

int BST::countInternal(Node *root)
{
    if (root == NULL)
        return 0;

    if (root->left == NULL && root->right == NULL)
        return 0;

    return 1 + countInternal(root->left) + countInternal(root->right);
}

int BST::internalNodes(Node *root)
{
    return countInternal(root);
}

void BST::mirror(Node *root)
{
    if (root == NULL)
        return;

    swap(root->left, root->right);

    mirror(root->left);
    mirror(root->right);
}

bool BST::equalTree(Node *root1, Node *root2)
{
    if (root1 == NULL && root2 == NULL)
        return true;

    if (root1 == NULL || root2 == NULL)
        return false;

    if (root1->data != root2->data)
        return false;

    return equalTree(root1->left, root2->left) &&
           equalTree(root1->right, root2->right);
}

bool BST::isEqual(Node *root1, Node *root2)
{
    return equalTree(root1, root2);
}

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

Node *BST::constructPreIn(vector<int> &pre,
                          vector<int> &in,
                          int &preIndex,
                          int start,
                          int end)
{
    if (start > end)
        return NULL;

    int value = pre[preIndex++];

    Node *newNode = new Node(value);

    int pos = start;

    while (in[pos] != value)
        pos++;

    newNode->left =
        constructPreIn(pre, in, preIndex, start, pos - 1);

    newNode->right =
        constructPreIn(pre, in, preIndex, pos + 1, end);

    return newNode;
}

void BST::constructFromPreIn()
{
    int n;

    cout << "Enter number of nodes : ";
    cin >> n;

    vector<int> pre(n);
    vector<int> in(n);

    cout << "Enter preorder : ";
    for (int i = 0; i < n; i++)
        cin >> pre[i];

    cout << "Enter inorder : ";
    for (int i = 0; i < n; i++)
        cin >> in[i];

    int preIndex = 0;

    root = constructPreIn(pre, in, preIndex, 0, n - 1);

    cout << "Tree constructed successfully.\n";
}

Node *BST::constructPostIn(vector<int> &post,
                           vector<int> &in,
                           int &postIndex,
                           int start,
                           int end)
{
    if (start > end)
        return NULL;

    int value = post[postIndex--];

    Node *newNode = new Node(value);

    int pos = start;

    while (in[pos] != value)
        pos++;

    newNode->right =
        constructPostIn(post, in, postIndex, pos + 1, end);

    newNode->left =
        constructPostIn(post, in, postIndex, start, pos - 1);

    return newNode;
}

void BST::constructFromPostIn()
{
    int n;

    cout << "Enter number of nodes : ";
    cin >> n;

    vector<int> post(n);
    vector<int> in(n);

    cout << "Enter postorder : ";
    for (int i = 0; i < n; i++)
        cin >> post[i];

    cout << "Enter inorder : ";
    for (int i = 0; i < n; i++)
        cin >> in[i];

    int postIndex = n - 1;

    root = constructPostIn(post, in, postIndex, 0, n - 1);

    cout << "Tree constructed successfully.\n";
}

int main()
{
    BST tree;

    int choice;

    do
    {
        cout << "\n---------- ARSENAL ----------\n";

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
        cout << "11. Find Height\n";
        cout << "12. Count Total Nodes\n";
        cout << "13. Count Leaf Nodes\n";
        cout << "14. Count Internal Nodes\n";
        cout << "15. Find Mirror\n";
        cout << "16. Construct using Inorder + Preorder\n";
        cout << "17. Construct using Inorder + Postorder\n";
        cout << "18. Update Node\n";
        cout << "19. Compare Two Trees\n";
        cout << "20. Exit\n";

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

        case 7:
            tree.findMin(tree.getRoot());
            break;

        case 8:
            tree.findMax(tree.getRoot());
            break;

        case 9:
            cout << "Ascending : ";
            tree.printASC(tree.getRoot());
            cout << endl;
            break;

        case 10:
            cout << "Descending : ";
            tree.printDESC(tree.getRoot());
            cout << endl;
            break;

        case 11:
            cout << "Height = "
                 << tree.height(tree.getRoot()) << endl;
            break;

        case 12:
            cout << "Total Nodes = "
                 << tree.totalNodes(tree.getRoot()) << endl;
            break;

        case 13:
            cout << "Leaf Nodes = "
                 << tree.leafNodes(tree.getRoot()) << endl;
            break;

        case 14:
            cout << "Internal Nodes = "
                 << tree.internalNodes(tree.getRoot()) << endl;
            break;

        case 15:
            tree.mirror(tree.getRoot());

            cout << "Mirror tree created.\n";
            cout << "Inorder of mirror : ";
            tree.inorder(tree.getRoot());
            cout << endl;

            break;

        case 16:
            tree.constructFromPreIn();

            cout << "Inorder : ";
            tree.inorder(tree.getRoot());
            cout << endl;

            break;

        case 17:
            tree.constructFromPostIn();

            cout << "Inorder : ";
            tree.inorder(tree.getRoot());
            cout << endl;

            break;

        case 18:
            tree.update();
            break;

        case 19:
        {
            BST tree2;

            cout << "\nCreate second BST\n";
            tree2.create();

            if (tree.isEqual(tree.getRoot(), tree2.getRoot()))
                cout << "Both trees are equal.\n";
            else
                cout << "Both trees are not equal.\n";

            break;
        }

        case 20:
            cout << "Thank You!\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 20);

    return 0;
}