#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
  char data;
  Node *left;
  Node *right;

  Node(char val)
  {
    data = val;
    left = NULL;
    right = NULL;
  }
};

class ExpressionTree
{
private:
  Node *root;

  bool isOperator(char ch);

public:
  ExpressionTree()
  {
    root = NULL;
  }

  Node *getRoot()
  {
    return root;
  }

  void create();

  void inorder(Node *);
  void preorder(Node *);
  void postorder(Node *);

  void inorderNonRecursive(Node *);
  void preorderNonRecursive(Node *);
  void postorderNonRecursive(Node *);

  void mirror(Node *);
};

bool ExpressionTree::isOperator(char ch)
{
  return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^';
}

void ExpressionTree::create()
{
  string exp;

  cout << "Enter prefix expression : ";
  cin >> exp;

  stack<Node *> s;

  for (int i = exp.length() - 1; i >= 0; i--)
  {
    Node *newNode = new Node(exp[i]);

    if (!isOperator(exp[i]))
    {
      s.push(newNode);
    }
    else
    {
      Node *left = s.top();
      s.pop();

      Node *right = s.top();
      s.pop();

      newNode->left = left;
      newNode->right = right;

      s.push(newNode);
    }
  }

  root = s.top();
  s.pop();

  cout << "Expression tree created successfully.\n";
}

void ExpressionTree::inorder(Node *root)
{
  if (root == NULL)
    return;

  inorder(root->left);
  cout << root->data << " ";
  inorder(root->right);
}

void ExpressionTree::preorder(Node *root)
{
  if (root == NULL)
    return;

  cout << root->data << " ";
  preorder(root->left);
  preorder(root->right);
}

void ExpressionTree::postorder(Node *root)
{
  if (root == NULL)
    return;

  postorder(root->left);
  postorder(root->right);
  cout << root->data << " ";
}

void ExpressionTree::inorderNonRecursive(Node *root)
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

void ExpressionTree::preorderNonRecursive(Node *root)
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

void ExpressionTree::postorderNonRecursive(Node *root)
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

void ExpressionTree::mirror(Node *root)
{
  if (root == NULL)
    return;

  swap(root->left, root->right);

  mirror(root->left);
  mirror(root->right);
}

int main()
{
  ExpressionTree tree;

  int choice;

  do
  {
    cout << "\n========== EXPRESSION TREE ==========\n";
    cout << "1. Create Expression Tree\n";
    cout << "2. Inorder Traversal (Recursive)\n";
    cout << "3. Preorder Traversal (Recursive)\n";
    cout << "4. Postorder Traversal (Recursive)\n";
    cout << "5. Inorder Traversal (Non-Recursive)\n";
    cout << "6. Preorder Traversal (Non-Recursive)\n";
    cout << "7. Postorder Traversal (Non-Recursive)\n";
    cout << "8. Mirror Tree\n";
    cout << "9. Exit\n";

    cout << "Enter choice : ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      tree.create();
      break;

    case 2:
      cout << "Inorder : ";
      tree.inorder(tree.getRoot());
      cout << endl;
      break;

    case 3:
      cout << "Preorder : ";
      tree.preorder(tree.getRoot());
      cout << endl;
      break;

    case 4:
      cout << "Postorder : ";
      tree.postorder(tree.getRoot());
      cout << endl;
      break;

    case 5:
      cout << "Inorder : ";
      tree.inorderNonRecursive(tree.getRoot());
      cout << endl;
      break;

    case 6:
      cout << "Preorder : ";
      tree.preorderNonRecursive(tree.getRoot());
      cout << endl;
      break;

    case 7:
      cout << "Postorder : ";
      tree.postorderNonRecursive(tree.getRoot());
      cout << endl;
      break;

    case 8:
      tree.mirror(tree.getRoot());
      cout << "Tree mirrored successfully.\n";
      break;

    case 9:
      cout << "Thank You!\n";
      break;

    default:
      cout << "Invalid Choice!\n";
    }

  } while (choice != 9);

  return 0;
}