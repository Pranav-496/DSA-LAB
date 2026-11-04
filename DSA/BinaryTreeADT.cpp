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

class BinaryTree
{
private:
    Node *root;

    Node *constructPreIn(vector<int> &pre, vector<int> &in, int &preIndex, int start, int end);
    Node *constructPostIn(vector<int> &post, vector<int> &in, int &postIndex, int start, int end);

    int heightRec(Node *);
    int countTotal(Node *);
    int countLeaf(Node *);
    bool equalTree(Node *, Node *);
    Node *copyTreeHelper(Node *);

public:
    BinaryTree()
    {
        root = NULL;
    }

    Node *getRoot()
    {
        return root;
    }

    void create();

    // Recursive Traversals
    void preorder(Node *);
    void inorder(Node *);
    void postorder(Node *);

    // Non-Recursive Traversals
    void preorderNR(Node *);
    void inorderNR(Node *);
    void postorderNR(Node *);

    int totalNodes(Node *);
    int leafNodes(Node *);
    int height(Node *);

    void mirror(Node *);
    bool isEqual(Node *, Node *);
    BinaryTree copyTree();

    void constructFromPreIn();
    void constructFromPostIn();

    // DFS and BFS
    void dfs(Node *);
    void bfs(Node *);
};

// TC: O(n) per insertion  SC: O(n) [queue for level order]
// Inserts node at first available spot (left to right, level by level)
void BinaryTree::create()
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
            // Level order insertion - find first empty spot
            queue<Node *> q;
            q.push(root);

            while (!q.empty())
            {
                Node *temp = q.front();
                q.pop();

                if (temp->left == NULL)
                {
                    temp->left = newNode;
                    break;
                }
                else
                    q.push(temp->left);

                if (temp->right == NULL)
                {
                    temp->right = newNode;
                    break;
                }
                else
                    q.push(temp->right);
            }
        }

        cout << "Do you want to insert another node? (y/n) : ";
        cin >> ch;

    } while (ch == 'y' || ch == 'Y');
}

// Recursive Preorder: Root -> Left -> Right
// TC: O(n)  SC: O(h) [recursive call stack]
void BinaryTree::preorder(Node *root)
{
    if (root == NULL)
        return;

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// Recursive Inorder: Left -> Root -> Right
// TC: O(n)  SC: O(h) [recursive call stack]
void BinaryTree::inorder(Node *root)
{
    if (root == NULL)
        return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Recursive Postorder: Left -> Right -> Root
// TC: O(n)  SC: O(h) [recursive call stack]
void BinaryTree::postorder(Node *root)
{
    if (root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// Non-Recursive Preorder: Root -> Left -> Right
// Use one stack. Push root, pop & print, push right then left.
// TC: O(n)  SC: O(n) [stack space]
void BinaryTree::preorderNR(Node *root)
{
    if (root == NULL)
        return;

    stack<Node *> s;
    s.push(root);

    while (!s.empty())
    {
        Node *curr = s.top();
        s.pop();

        cout << curr->data << " ";

        if (curr->right != NULL)
            s.push(curr->right);

        if (curr->left != NULL)
            s.push(curr->left);
    }
}

// Non-Recursive Inorder: Left -> Root -> Right
// Use one stack. Go left pushing nodes, pop & print, move right.
// TC: O(n)  SC: O(n) [stack space]
void BinaryTree::inorderNR(Node *root)
{
    stack<Node *> s;
    Node *curr = root;

    while (curr != NULL || !s.empty())
    {
        while (curr != NULL)
        {
            s.push(curr);
            curr = curr->left;
        }

        curr = s.top();
        s.pop();

        cout << curr->data << " ";

        curr = curr->right;
    }
}

// Non-Recursive Postorder: Left -> Right -> Root
// Use two stacks. Push to s1, pop to s2 (push left then right to s1).
// Finally print s2.
// TC: O(n)  SC: O(n) [two stacks]
void BinaryTree::postorderNR(Node *root)
{
    if (root == NULL)
        return;

    stack<Node *> s1, s2;
    s1.push(root);

    while (!s1.empty())
    {
        Node *curr = s1.top();
        s1.pop();

        s2.push(curr);

        if (curr->left != NULL)
            s1.push(curr->left);

        if (curr->right != NULL)
            s1.push(curr->right);
    }

    while (!s2.empty())
    {
        cout << s2.top()->data << " ";
        s2.pop();
    }
}

// TC: O(n)  SC: O(h) [recursive call stack]
int BinaryTree::heightRec(Node *root)
{
    if (root == NULL)
        return 0;

    return 1 + max(heightRec(root->left),
                   heightRec(root->right));
}

// TC: O(n)  SC: O(h)
int BinaryTree::height(Node *root)
{
    return heightRec(root);
}

// TC: O(n)  SC: O(h) [recursive call stack]
int BinaryTree::countTotal(Node *root)
{
    if (root == NULL)
        return 0;

    return 1 + countTotal(root->left) + countTotal(root->right);
}

// TC: O(n)  SC: O(h)
int BinaryTree::totalNodes(Node *root)
{
    return countTotal(root);
}

// TC: O(n)  SC: O(h) [recursive call stack]
int BinaryTree::countLeaf(Node *root)
{
    if (root == NULL)
        return 0;

    if (root->left == NULL && root->right == NULL)
        return 1;

    return countLeaf(root->left) + countLeaf(root->right);
}

// TC: O(n)  SC: O(h)
int BinaryTree::leafNodes(Node *root)
{
    return countLeaf(root);
}

// TC: O(n)  SC: O(h) [recursive call stack]
void BinaryTree::mirror(Node *root)
{
    if (root == NULL)
        return;

    swap(root->left, root->right);

    mirror(root->left);
    mirror(root->right);
}

// TC: O(n)  SC: O(h) [recursive call stack]
bool BinaryTree::equalTree(Node *root1, Node *root2)
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

// TC: O(n)  SC: O(h)
bool BinaryTree::isEqual(Node *root1, Node *root2)
{
    return equalTree(root1, root2);
}

// TC: O(n)  SC: O(h) [recursive call stack]
Node *BinaryTree::copyTreeHelper(Node *root)
{
    if (root == NULL)
        return NULL;

    Node *newNode = new Node(root->data);
    newNode->left = copyTreeHelper(root->left);
    newNode->right = copyTreeHelper(root->right);
    return newNode;
}

// TC: O(n)  SC: O(h)
// Creates and returns a deep copy of the tree
BinaryTree BinaryTree::copyTree()
{
    BinaryTree newTree;
    newTree.root = copyTreeHelper(root);
    return newTree;
}

// TC: O(n^2)  SC: O(n) [recursive call stack + linear search]
Node *BinaryTree::constructPreIn(vector<int> &pre,
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

// TC: O(n^2)  SC: O(n)
void BinaryTree::constructFromPreIn()
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

// TC: O(n^2)  SC: O(n) [recursive call stack + linear search]
Node *BinaryTree::constructPostIn(vector<int> &post,
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

// TC: O(n^2)  SC: O(n)
void BinaryTree::constructFromPostIn()
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

// Non-Recursive DFS (Depth First Search) - same as Preorder
// Uses stack: push root, pop & print, push right then left
// TC: O(n)  SC: O(n) [stack space]
void BinaryTree::dfs(Node *root)
{
    if (root == NULL)
        return;

    stack<Node *> s;
    s.push(root);

    while (!s.empty())
    {
        Node *curr = s.top();
        s.pop();

        cout << curr->data << " ";

        if (curr->right != NULL)
            s.push(curr->right);

        if (curr->left != NULL)
            s.push(curr->left);
    }
}

// BFS (Breadth First Search) - Level Order Traversal
// Uses queue: push root, pop & print, push left then right
// TC: O(n)  SC: O(n) [queue space]
void BinaryTree::bfs(Node *root)
{
    if (root == NULL)
        return;

    queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        Node *curr = q.front();
        q.pop();

        cout << curr->data << " ";

        if (curr->left != NULL)
            q.push(curr->left);

        if (curr->right != NULL)
            q.push(curr->right);
    }
}

int main()
{
    BinaryTree tree;

    int choice;

    do
    {
        cout << "\n---------- BINARY TREE ADT ----------\n";

        cout << "1. Create Binary Tree\n";
        cout << "2. Recursive Preorder\n";
        cout << "3. Recursive Inorder\n";
        cout << "4. Recursive Postorder\n";
        cout << "5. Non-Recursive Preorder\n";
        cout << "6. Non-Recursive Inorder\n";
        cout << "7. Non-Recursive Postorder\n";
        cout << "8. Count Total Nodes\n";
        cout << "9. Count Leaf Nodes\n";
        cout << "10. Find Height\n";
        cout << "11. Mirror Tree\n";
        cout << "12. Check Equal Trees\n";
        cout << "13. Copy Tree\n";
        cout << "14. Construct using Inorder + Preorder\n";
        cout << "15. Construct using Inorder + Postorder\n";
        cout << "16. DFS (Non-Recursive)\n";
        cout << "17. BFS (Level Order)\n";
        cout << "18. Exit\n";

        cout << "Enter choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            tree.create();
            break;

        case 2:
            cout << "Recursive Preorder : ";
            tree.preorder(tree.getRoot());
            cout << endl;
            break;

        case 3:
            cout << "Recursive Inorder : ";
            tree.inorder(tree.getRoot());
            cout << endl;
            break;

        case 4:
            cout << "Recursive Postorder : ";
            tree.postorder(tree.getRoot());
            cout << endl;
            break;

        case 5:
            cout << "Non-Recursive Preorder : ";
            tree.preorderNR(tree.getRoot());
            cout << endl;
            break;

        case 6:
            cout << "Non-Recursive Inorder : ";
            tree.inorderNR(tree.getRoot());
            cout << endl;
            break;

        case 7:
            cout << "Non-Recursive Postorder : ";
            tree.postorderNR(tree.getRoot());
            cout << endl;
            break;

        case 8:
            cout << "Total Nodes = "
                 << tree.totalNodes(tree.getRoot()) << endl;
            break;

        case 9:
            cout << "Leaf Nodes = "
                 << tree.leafNodes(tree.getRoot()) << endl;
            break;

        case 10:
            cout << "Height = "
                 << tree.height(tree.getRoot()) << endl;
            break;

        case 11:
            tree.mirror(tree.getRoot());

            cout << "Mirror tree created.\n";
            cout << "Inorder of mirror : ";
            tree.inorder(tree.getRoot());
            cout << endl;

            break;

        case 12:
        {
            BinaryTree tree2;

            cout << "\nCreate second Binary Tree\n";
            tree2.create();

            if (tree.isEqual(tree.getRoot(), tree2.getRoot()))
                cout << "Both trees are equal.\n";
            else
                cout << "Both trees are not equal.\n";

            break;
        }

        case 13:
        {
            BinaryTree copied = tree.copyTree();

            cout << "Tree copied successfully.\n";
            cout << "Inorder of copied tree : ";
            copied.inorder(copied.getRoot());
            cout << endl;

            break;
        }

        case 14:
            tree.constructFromPreIn();

            cout << "Inorder : ";
            tree.inorder(tree.getRoot());
            cout << endl;

            break;

        case 15:
            tree.constructFromPostIn();

            cout << "Inorder : ";
            tree.inorder(tree.getRoot());
            cout << endl;

            break;

        case 16:
            cout << "DFS : ";
            tree.dfs(tree.getRoot());
            cout << endl;
            break;

        case 17:
            cout << "BFS : ";
            tree.bfs(tree.getRoot());
            cout << endl;
            break;

        case 18:
            cout << "Thank You!\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 18);

    return 0;
}