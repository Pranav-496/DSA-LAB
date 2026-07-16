#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX = 20;

class GraphNode
{
public:
  int vertex;
  int cost;
  GraphNode *next;

  GraphNode(int v, int c)
  {
    vertex = v;
    cost = c;
    next = NULL;
  }
};

class Graph
{
  int n;
  string city[MAX];
  int matrix[MAX][MAX];
  GraphNode *head[MAX];

public:
  Graph()
  {
    n = 0;
    for (int i = 0; i < MAX; i++)
    {
      head[i] = NULL;

      for (int j = 0; j < MAX; j++)
        matrix[i][j] = 0;
    }
  }

  int getIndex(string name)
  {
    for (int i = 0; i < n; i++)
    {
      if (city[i] == name)
        return i;
    }
    return -1;
  }

  void createGraph()
  {
    cout << "Enter number of cities: ";
    cin >> n;

    cout << "Enter city names:\n";
    for (int i = 0; i < n; i++)
      cin >> city[i];
  }

  void addFlight()
  {
    string src, dest;
    int cost;

    cout << "Enter source city: ";
    cin >> src;

    cout << "Enter destination city: ";
    cin >> dest;

    cout << "Enter cost (Time/Fuel): ";
    cin >> cost;

    int u = getIndex(src);
    int v = getIndex(dest);

    if (u == -1 || v == -1)
    {
      cout << "Invalid city!\n";
      return;
    }

    // Adjacency Matrix
    matrix[u][v] = cost;
    matrix[v][u] = cost;

    // Adjacency List
    GraphNode *temp = new GraphNode(v, cost);
    temp->next = head[u];
    head[u] = temp;

    temp = new GraphNode(u, cost);
    temp->next = head[v];
    head[v] = temp;

    cout << "Flight Added Successfully.\n";
  }

  void displayMatrix()
  {
    cout << "\nAdjacency Matrix\n\n";

    cout << setw(10) << "";

    for (int i = 0; i < n; i++)
      cout << setw(10) << city[i];

    cout << endl;

    for (int i = 0; i < n; i++)
    {
      cout << setw(10) << city[i];

      for (int j = 0; j < n; j++)
        cout << setw(10) << matrix[i][j];

      cout << endl;
    }
  }

  void displayList()
  {
    cout << "\nAdjacency List\n";

    for (int i = 0; i < n; i++)
    {
      cout << city[i] << " -> ";

      GraphNode *temp = head[i];

      while (temp != NULL)
      {
        cout << "(" << city[temp->vertex] << ", " << temp->cost << ") -> ";
        temp = temp->next;
      }

      cout << "NULL\n";
    }
  }

  void checkConnection()
  {
    string src, dest;

    cout << "Enter source city: ";
    cin >> src;

    cout << "Enter destination city: ";
    cin >> dest;

    int u = getIndex(src);
    int v = getIndex(dest);

    if (u == -1 || v == -1)
    {
      cout << "Invalid City!\n";
      return;
    }

    if (matrix[u][v] != 0)
      cout << "Flight Exists. Cost = " << matrix[u][v] << endl;
    else
      cout << "No Direct Flight Exists.\n";
  }

  void compareStorage()
  {
    int edges = 0;

    for (int i = 0; i < n; i++)
    {
      GraphNode *temp = head[i];

      while (temp != NULL)
      {
        edges++;
        temp = temp->next;
      }
    }

    cout << "\nStorage Comparison\n";
    cout << "----------------------\n";
    cout << "Adjacency Matrix : O(V^2)\n";
    cout << "Memory Used = " << n * n << " integer cells\n\n";

    cout << "Adjacency List : O(V + E)\n";
    cout << "Vertices = " << n << endl;
    cout << "Edges Stored = " << edges << endl;

    cout << "\nAdjacency List is better for sparse graphs.\n";
    cout << "Adjacency Matrix is better for dense graphs.\n";
  }
};

int main()
{
  Graph g;
  g.createGraph();

  int choice;

  do
  {
    cout << "\n===== Flight Management =====\n";
    cout << "1. Add Flight\n";
    cout << "2. Display Adjacency Matrix\n";
    cout << "3. Display Adjacency List\n";
    cout << "4. Check Connection\n";
    cout << "5. Compare Storage\n";
    cout << "6. Exit\n";

    cout << "Enter Choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      g.addFlight();
      break;

    case 2:
      g.displayMatrix();
      break;

    case 3:
      g.displayList();
      break;

    case 4:
      g.checkConnection();
      break;

    case 5:
      g.compareStorage();
      break;

    case 6:
      cout << "Program Ended.\n";
      break;

    default:
      cout << "Invalid Choice!\n";
    }

  } while (choice != 6);

  return 0;
}