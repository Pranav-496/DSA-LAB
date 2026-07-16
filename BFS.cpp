#include <iostream>
#include <queue>
using namespace std;

const int MAX = 20;

class GraphNode
{
public:
  int vertex;
  GraphNode *next;

  GraphNode(int v)
  {
    vertex = v;
    next = NULL;
  }
};

class Graph
{
  int vertices;
  GraphNode *head[MAX];
  bool visited[MAX];

public:
  Graph()
  {
    vertices = 0;

    for (int i = 0; i < MAX; i++)
    {
      head[i] = NULL;
      visited[i] = false;
    }
  }

  void createGraph()
  {
    cout << "Enter number of vertices: ";
    cin >> vertices;
  }

  void addEdge(int u, int v)
  {
    if (u >= vertices || v >= vertices)
    {
      cout << "Invalid Vertex\n";
      return;
    }

    // u -> v
    GraphNode *temp = new GraphNode(v);
    temp->next = head[u];
    head[u] = temp;

    // v -> u
    temp = new GraphNode(u);
    temp->next = head[v];
    head[v] = temp;
  }

  void displayGraph()
  {
    cout << "\nAdjacency List\n";

    for (int i = 0; i < vertices; i++)
    {
      cout << i << " -> ";

      GraphNode *temp = head[i];

      while (temp != NULL)
      {
        cout << temp->vertex << " -> ";
        temp = temp->next;
      }

      cout << "NULL\n";
    }
  }

  void resetVisited()
  {
    for (int i = 0; i < vertices; i++)
      visited[i] = false;
  }

  void BFS()
  {
    int start;

    cout << "Enter starting vertex: ";
    cin >> start;

    resetVisited();

    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "BFS Traversal : ";

    while (!q.empty())
    {
      int current = q.front();
      q.pop();

      cout << current << " ";

      GraphNode *temp = head[current];

      while (temp != NULL)
      {
        if (!visited[temp->vertex])
        {
          visited[temp->vertex] = true;
          q.push(temp->vertex);
        }

        temp = temp->next;
      }
    }

    cout << endl;
  }
};

int main()
{
  Graph g;

  g.createGraph();

  int choice, u, v;

  do
  {
    cout << "\n===== MENU =====\n";
    cout << "1. Add Edge\n";
    cout << "2. Display Graph\n";
    cout << "3. BFS Traversal\n";
    cout << "4. Exit\n";

    cout << "Enter Choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      cout << "Enter source and destination: ";
      cin >> u >> v;
      g.addEdge(u, v);
      break;

    case 2:
      g.displayGraph();
      break;

    case 3:
      g.BFS();
      break;

    case 4:
      cout << "Program Ended\n";
      break;

    default:
      cout << "Invalid Choice\n";
    }

  } while (choice != 4);

  return 0;
}