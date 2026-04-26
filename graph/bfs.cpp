#include <bits/stdc++.h>
using namespace std;

/*
====================================================
GRAPH TOOLKIT (0-BASED INDEXING)
----------------------------------------------------
Nodes: 0 to n-1
Works for:
    - Directed / Undirected
    - Weighted / Unweighted
    - BFS traversal (unweighted graphs)
====================================================
*/

// ===================== Edge Class =====================
class Edge {
public:
    int to;       // destination node
    int weight;   // edge weight

    Edge(int _to, int _weight) {
        to = _to;
        weight = _weight;
    }
};

// ===================== Graph Storage =====================
// Unweighted graph: adj[u] = list of neighbors of u
vector<vector<int>> adj;

// Weighted graph: adjW[u] = list of (neighbor, weight)
vector<vector<Edge>> adjW;


// ===================== Random Generator =====================
// Used to automatically generate graph edges
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// Generate random number in range [l, r]
int getRandom(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}


// ===================== Graph Generator =====================
/*
Parameters:
    n           = number of nodes (0 to n-1)
    m           = number of edges
    directed    = true -> directed graph
    weighted    = true -> weighted graph

Note:
    - Generates random edges
    - May have self-loops (u == v)
    - May have duplicate edges
*/
void generateGraph(int n, int m, bool directed, bool weighted) {
    adj.assign(n, {});
    adjW.assign(n, {});

    for (int i = 0; i < m; i++) {
        int u = getRandom(0, n - 1);
        int v = getRandom(0, n - 1);

        if (weighted) {
            int w = getRandom(1, 100);

            adjW[u].push_back(Edge(v, w));

            if (!directed) {
                adjW[v].push_back(Edge(u, w));
            }
        } else {
            adj[u].push_back(v);

            if (!directed) {
                adj[v].push_back(u);
            }
        }
    }
}


// ===================== Print Functions =====================

// Unweighted graph print
void printGraph(int n) {
    cout << "\nGraph (Adjacency List):\n";
    for (int i = 0; i < n; i++) {
        cout << i << " -> ";
        for (int neighbor : adj[i]) {
            cout << neighbor << " ";
        }
        cout << "\n";
    }
}

// Weighted graph print
void printWeightedGraph(int n) {
    cout << "\nWeighted Graph:\n";
    for (int i = 0; i < n; i++) {
        cout << i << " -> ";
        for (auto e : adjW[i]) {
            cout << "(" << e.to << ", w=" << e.weight << ") ";
        }
        cout << "\n";
    }
}


// ===================== BFS (Unweighted Graph) =====================
/*
Returns:
    dist[i] = shortest distance from startNode to i (-1 means unreachable)

Time Complexity:
    O(V + E) where V = number of vertices and E = number of edges in the graph
Space Complexity:
    O(V) for distance array and queue

Note:
    - Only works for unweighted graphs.
    - Assumes graph is stored in adj.

*/
vector<int> bfs(int n, int startNode) {
    vector<int> dist(n, -1);   // distance array
    queue<int> q;

    q.push(startNode);
    dist[startNode] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor : adj[current]) {
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[current] + 1;
                q.push(neighbor);
            }
        }
    }

    return dist;
}


// ===================== MAIN =====================
int main() {
    // User input for graph parameters
    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    bool directed, weighted;
    cout << "Directed? (1/0): ";
    cin >> directed;

    cout << "Weighted? (1/0): ";
    cin >> weighted;

    // Generate graph automatically
    generateGraph(n, m, directed, weighted);

    // Print graph
    if (weighted) {
        printWeightedGraph(n);
    } else {
        printGraph(n);
    }

    // BFS traversal
    int startNode;
    cout << "\nEnter start node (0 to " << n-1 << "): ";
    cin >> startNode;

    vector<int> dist = bfs(n, startNode);

    cout << "\nDistances from node " << startNode << ":\n";
    for (int i = 0; i < n; i++) {
        cout << "Node " << i << " -> " << dist[i] << "\n";
    }

    return 0;
}