#include <iostream>
#include <list>
#include <stack>

using namespace std;

const int MAX_VERTICES = 100;

class Graph {
    int V;
    list<int> adj[MAX_VERTICES];

    void orderVertices(int v, bool visited[], stack<int> &Stack);
    void exploreComponent(int v, bool visited[]);

public:
    Graph(int V);
    void addEdge(int v, int w);
    void findSCCs();
    Graph transposeGraph();
};

Graph::Graph(int V) {
    this->V = V;
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w); // Add w to v's list.
}

void Graph::exploreComponent(int v, bool visited[]) {
    // Mark the current node as visited and print it
    visited[v] = true;
    cout << v << " ";

   // Setup an iterator to go through each connected vertex.
list<int>::iterator i;

// Start the loop from the first to the last connected vertex to 'v'.
for (i = adj[v].begin(); i != adj[v].end(); ++i) {
    // Check if the vertex at the current position has not been visited.
    if (!visited[*i]) {
        // If it hasn't been visited, start exploring from this vertex.
        exploreComponent(*i, visited);
    }
}

}

Graph Graph::transposeGraph() {
    Graph g(V);
    for (int v = 0; v < V; v++)
        for(list<int>::iterator i = adj[v].begin(); i != adj[v].end(); ++i)
            g.adj[*i].push_back(v);
    return g;
}

void Graph::orderVertices(int v, bool visited[], stack<int> &Stack) {
    // Marks the current node as visited
    visited[v] = true;

    // Recur for all vertices adjacent to this vertex
    // Create an iterator to go through the list of connected vertices.
list<int>::iterator i;

// Loop through all vertices connected to vertex 'v'.
for (i = adj[v].begin(); i != adj[v].end(); ++i) {
    // If the current vertex hasn't been visited yet,
    if (!visited[*i]) {
        // Call the function 'orderVertices' to continue the search from this vertex.
        orderVertices(*i, visited, Stack);
    }
}


    // All vertices reachable from v are processed by now, push v to Stack
    Stack.push(v);
}

void Graph::findSCCs() {
    stack<int> Stack;

    // Mark all the vertices as not visited (For first DFS)
    bool visited[MAX_VERTICES] = {false};

    // Fill vertices in stack according to their finishing times
    for(int i = 0; i < V; i++)
        if (!visited[i])
            orderVertices(i, visited, Stack);

    // Create a reversed graph
    Graph gr = transposeGraph();

    // Mark all vertices as not visited (For second DFS)
    for(int i = 0; i < MAX_VERTICES; i++)
        visited[i] = false;

    // Now process all vertices in order defined by Stack
    while (!Stack.empty()) {
        // Pop a vertex from stack
        int v = Stack.top();
        Stack.pop();

        // Print Strongly connected component of the popped vertex
        if (!visited[v]) {
            cout << "Connected component: ";
            gr.exploreComponent(v, visited);
            cout << endl;
        }
    }
}

int main() {
    Graph s(6); // Increase number of vertices to 6
    s.addEdge(0, 1);
    s.addEdge(1, 2);
    s.addEdge(2, 0); // Create a cycle between 0, 1, 2
    s.addEdge(2, 3);
    s.addEdge(3, 4);
    s.addEdge(4, 5);
    s.addEdge(5, 3); // Create another cycle between 3, 4, 5

    cout << " connected components:" << endl;
    s.findSCCs();

    return 0;
}

