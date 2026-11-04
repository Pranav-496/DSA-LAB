#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// ---------- DFS using Adjacency Matrix ----------
void DFSMatrix(int v, int n, int adj[10][10], int visited[])
{
    cout << v << " ";
    visited[v] = 1;

    for(int i = 0; i < n; i++)
    {
        if(adj[v][i] == 1 && visited[i] == 0)
        {
            DFSMatrix(i, n, adj, visited);
        }
    }
}

// ---------- BFS using Adjacency Matrix ----------
void BFSMatrix(int start, int n, int adj[10][10])
{
    int visited[10] = {0};
    queue<int> q;

    visited[start] = 1;
    q.push(start);

    while(!q.empty())
    {
        int v = q.front();
        q.pop();

        cout << v << " ";

        for(int i = 0; i < n; i++)
        {
            if(adj[v][i] == 1 && visited[i] == 0)
            {
                visited[i] = 1;
                q.push(i);
            }
        }
    }
}

// ---------- DFS using Adjacency List ----------
void DFSList(int v, vector<int> adj[], int visited[])
{
    cout << v << " ";
    visited[v] = 1;

    for(int i : adj[v])
    {
        if(visited[i] == 0)
        {
            DFSList(i, adj, visited);
        }
    }
}

// ---------- BFS using Adjacency List ----------
void BFSList(int start, int n, vector<int> adj[])
{
    int visited[10] = {0};
    queue<int> q;

    visited[start] = 1;
    q.push(start);

    while(!q.empty())
    {
        int v = q.front();
        q.pop();

        cout << v << " ";

        for(int i : adj[v])
        {
            if(visited[i] == 0)
            {
                visited[i] = 1;
                q.push(i);
            }
        }
    }
}

int main()
{
    int n, e;
    int adj[10][10] = {0};
    vector<int> list[10];

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> e;

    cout << "Enter edges:\n";

    for(int i = 0; i < e; i++)
    {
        int u, v;
        cin >> u >> v;

        // Undirected graph
        adj[u][v] = 1;
        adj[v][u] = 1;

        list[u].push_back(v);
        list[v].push_back(u);
    }

    int start;
    cout << "Enter starting vertex: ";
    cin >> start;

    // Matrix DFS
    int visited1[10] = {0};
    cout << "\nDFS using Matrix: ";
    DFSMatrix(start, n, adj, visited1);

    // Matrix BFS
    cout << "\nBFS using Matrix: ";
    BFSMatrix(start, n, adj);

    // List DFS
    int visited2[10] = {0};
    cout << "\nDFS using List: ";
    DFSList(start, list, visited2);

    // List BFS
    cout << "\nBFS using List: ";
    BFSList(start, n, list);

    return 0;
}