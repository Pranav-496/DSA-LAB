#include <bits/stdc++.h>
using namespace std;

//==================== ADJACENCY LIST ====================//

class GraphNode
{
public:
  int dest, cost, tim;
  GraphNode *next;

  GraphNode(int d, int c, int t)
  {
    dest = d;
    cost = c;
    tim = t;
    next = NULL;
  }
};

class AdjList
{
public:
  GraphNode *head[4];
  string node[4] = {"Nashik", "Mumbai", "Pune", "Delhi"};

  AdjList()
  {
    for (int i = 0; i < 4; i++)
      head[i] = NULL;
  }

  void addFlight(int s, int d, int cost, int tim)
  {
    GraphNode *temp = new GraphNode(d, cost, tim);
    temp->next = head[s];
    head[s] = temp;
  }

  void display()
  {
    cout << "\n----- Adjacency List -----\n\n";

    for (int i = 0; i < 4; i++)
    {
      cout << node[i] << " -> ";

      GraphNode *temp = head[i];

      while (temp != NULL)
      {
        cout << "[" << node[temp->dest]
             << ", Cost=" << temp->cost
             << ", Time=" << temp->tim
             << "] -> ";

        temp = temp->next;
      }

      cout << "NULL\n\n";
    }
  }

  void exist(int s, int d)
  {
    GraphNode *temp = head[s];

    while (temp != NULL)
    {
      if (temp->dest == d)
      {
        cout << "\nDirect Path Exists\n";
        cout << "Cost = " << temp->cost << endl;
        cout << "Time = " << temp->tim << endl;
        return;
      }
      temp = temp->next;
    }

    temp = head[s];

    while (temp != NULL)
    {
      int mid = temp->dest;
      GraphNode *temp2 = head[mid];

      while (temp2 != NULL)
      {
        if (temp2->dest == d)
        {
          cout << "\nIndirect Path Exists\n";
          cout << node[s] << " -> "
               << node[mid] << " -> "
               << node[d] << endl;

          cout << "Cost = "
               << temp->cost + temp2->cost << endl;

          cout << "Time = "
               << temp->tim + temp2->tim << endl;

          return;
        }

        temp2 = temp2->next;
      }

      temp = temp->next;
    }

    cout << "No Path Exists\n";
  }
};

//==================== ADJACENCY MATRIX ====================//

class AdjMatrix
{
public:
  int mat[4][4] = {0};
  int tim[4][4] = {0};

  string node[4] = {"Nashik", "Mumbai", "Pune", "Delhi"};

  void addFlight(int s, int d, int cost, int t)
  {
    mat[s][d] = cost;
    tim[s][d] = t;
  }

  void display()
  {
    cout << "\n----- Adjacency Matrix -----\n\n";

    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        if (i == j)
          continue;

        cout << node[i] << " -> " << node[j]
             << " | Cost = " << mat[i][j]
             << " | Time = " << tim[i][j] << endl;
      }
      cout << endl;
    }
  }

  void exist(int s, int d)
  {
    if (mat[s][d])
    {
      cout << "\nDirect Path Exists\n";
      cout << "Cost = " << mat[s][d] << endl;
      cout << "Time = " << tim[s][d] << endl;
      return;
    }

    for (int i = 0; i < 4; i++)
    {
      if (mat[s][i] && mat[i][d])
      {
        cout << "\nIndirect Path Exists\n";
        cout << node[s] << " -> "
             << node[i] << " -> "
             << node[d] << endl;

        cout << "Cost = "
             << mat[s][i] + mat[i][d] << endl;

        cout << "Time = "
             << tim[s][i] + tim[i][d] << endl;

        return;
      }
    }

    cout << "No Path Exists\n";
  }
};

//==================== MAIN ====================//

int main()
{
  AdjList listGraph;
  AdjMatrix matrixGraph;

  int choice;

  do
  {
    cout << "\n========== MAIN MENU ==========\n";
    cout << "1. Add Flight\n";
    cout << "2. Check Flight (Adjacency List)\n";
    cout << "3. Check Flight (Adjacency Matrix)\n";
    cout << "4. Display Adjacency List\n";
    cout << "5. Display Adjacency Matrix\n";
    cout << "6. Exit\n";

    cout << "Enter Choice : ";
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
      int s, d, cost, t;

      cout << "\nCities:\n";
      cout << "0. Nashik\n";
      cout << "1. Mumbai\n";
      cout << "2. Pune\n";
      cout << "3. Delhi\n";

      cout << "Enter Source : ";
      cin >> s;

      cout << "Enter Destination : ";
      cin >> d;

      cout << "Enter Cost : ";
      cin >> cost;

      cout << "Enter Time : ";
      cin >> t;

      // Add to both representations
      listGraph.addFlight(s, d, cost, t);
      matrixGraph.addFlight(s, d, cost, t);

      cout << "Flight Added Successfully.\n";
      break;
    }

    case 2:
    {
      int s, d;
      cout << "Enter Source and Destination : ";
      cin >> s >> d;
      listGraph.exist(s, d);
      break;
    }

    case 3:
    {
      int s, d;
      cout << "Enter Source and Destination : ";
      cin >> s >> d;
      matrixGraph.exist(s, d);
      break;
    }

    case 4:
      listGraph.display();
      break;

    case 5:
      matrixGraph.display();
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