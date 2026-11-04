#include <bits/stdc++.h>
using namespace std;

class GraphNode
{
public:
  int dest;
  int cost;
  int time;
  GraphNode *next;

  GraphNode(int d, int c, int t)
  {
    dest = d;
    cost = c;
    time = t;
    next = NULL;
  }
};

class graph
{
public:
  GraphNode *head[4];
  string node[4] = {"Nashik", "Mumbai", "Pune", "Delhi"};

  graph()
  {
    for (int i = 0; i < 4; i++)
      head[i] = NULL;
  }

  void read()
  {
    int s, d, cost, t;

    cout << "Enter source : ";
    cin >> s;

    cout << "Enter destination : ";
    cin >> d;

    cout << "Enter cost : ";
    cin >> cost;

    cout << "Enter time : ";
    cin >> t;

    GraphNode *temp = new GraphNode(d, cost, t);

    temp->next = head[s];
    head[s] = temp;
  }

  void display()
  {
    for (int i = 0; i < 4; i++)
    {
      cout << node[i] << " -> ";

      GraphNode *temp = head[i];

      while (temp != NULL)
      {
        cout << "[" << node[temp->dest]
             << ", Cost = " << temp->cost
             << ", Time = " << temp->time << "] -> ";

        temp = temp->next;
      }

      cout << "NULL\n\n";
    }
  }

  void exist(int s, int d)
  {
    GraphNode *temp = head[s];

    // Direct Flight
    while (temp != NULL)
    {
      if (temp->dest == d)
      {
        cout << "The direct path exists.\n";
        cout << "Cost = " << temp->cost << endl;
        cout << "Time = " << temp->time << endl;
        return;
      }

      temp = temp->next;
    }

    // Indirect Flight (One Intermediate City)
    temp = head[s];

    while (temp != NULL)
    {
      int mid = temp->dest;

      GraphNode *temp2 = head[mid];

      while (temp2 != NULL)
      {
        if (temp2->dest == d)
        {
          cout << "Indirect Path Exists\n";
          cout << node[s] << " -> "
               << node[mid] << " -> "
               << node[d] << endl;

          cout << "Cost = "
               << temp->cost + temp2->cost << endl;

          cout << "Time = "
               << temp->time + temp2->time << endl;

          return;
        }

        temp2 = temp2->next;
      }

      temp = temp->next;
    }

    cout << "No Path Exists\n";
  }
};

int main()
{
  graph g1;
  int choice;

  do
  {
    cout << "\n---------MENU-----------" << endl;
    cout << "1. Add a Flight" << endl;
    cout << "2. Check if Flight Exists" << endl;
    cout << "3. Display All Flights" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice : ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      g1.read();
      break;

    case 2:
    {
      int s, d;

      cout << "Enter source and destination : ";
      cin >> s >> d;

      g1.exist(s, d);
      break;
    }

    case 3:
      g1.display();
      break;

    case 4:
      cout << "Chalo Bye\n";
      break;

    default:
      cout << "Invalid Choice\n";
    }

  } while (choice != 4);

  return 0;
}