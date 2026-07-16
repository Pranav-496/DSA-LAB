#include <iostream>
#include <stack>
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

  // Recursive DFS Helper
  void DFSRecursive(int v)
  {
    visited[v] = true;
    cout << v << " ";

    GraphNode *temp = head[v];

    while (temp != NULL)
    {
      if (!visited[temp->vertex])
        DFSRecursive(temp->vertex);

      temp = temp->next;
    }
  }

  void recursiveDFS()
  {
    int start;

    cout << "Enter starting vertex: ";
    cin >> start;

    resetVisited();

    cout << "Recursive DFS : ";
    DFSRecursive(start);
    cout << endl;
  }

  void iterativeDFS()
  {
    int start;

    cout << "Enter starting vertex: ";
    cin >> start;

    resetVisited();

    stack<int> st;
    st.push(start);

    cout << "Iterative DFS : ";

    while (!st.empty())
    {
      int current = st.top();
      st.pop();

      if (!visited[current])
      {
        visited[current] = true;
        cout << current << " ";

        GraphNode *temp = head[current];

        while (temp != NULL)
        {
          if (!visited[temp->vertex])
            st.push(temp->vertex);

          temp = temp->next;
        }
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
    cout << "3. Recursive DFS\n";
    cout << "4. Iterative DFS\n";
    cout << "5. Exit\n";

    cout << "Enter choice: ";
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
      g.recursiveDFS();
      break;

    case 4:
      g.iterativeDFS();
      break;

    case 5:
      cout << "Program Ended\n";
      break;

    default:
      cout << "Invalid Choice\n";
    }

  } while (choice != 5);

  return 0;
}