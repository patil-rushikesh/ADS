#include <iostream>
#include <vector>
using namespace std;

#define V 7
#define INF 99999  // Large number for no connection

class Graph {
private:
    struct Edge {
        int src, dest, weight;
    };

    vector<vector<pair<int, int>>> adjList;  // Adjacency list: pair(vertex, weight)
    vector<Edge> edges;

    int find(vector<int>& parent, int i) {
        if (parent[i] != i)
            parent[i] = find(parent, parent[i]);
        return parent[i];
    }

    void unionSets(vector<int>& parent, vector<int>& rank, int x, int y) {
        int rootX = find(parent, x);
        int rootY = find(parent, y);
        if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }

    // Manual sorting of edges (Selection Sort)
    void sortEdges() {
        int n = edges.size();
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++) {
                if (edges[j].weight < edges[minIdx].weight) {
                    minIdx = j;
                }
            }
            if (minIdx != i) {
                // Swap edges[i] and edges[minIdx]
                Edge temp = edges[i];
                edges[i] = edges[minIdx];
                edges[minIdx] = temp;
            }
        }
    }

public:
    Graph() {
        adjList = vector<vector<pair<int, int>>>(V);
    }

    void inputGraph() {
        edges.clear();
        cout << "Enter the adjacency list (" << V << " vertices):\n";
        cout << "(Enter pairs of the form 'vertex weight', use 0 for no edge)\n";
        for (int i = 0; i < V; i++) {
            cout << "Enter edges for vertex " << i << " (end with -1):\n";
            int vertex, weight;
            while (true) {
                cin >> vertex;
                if (vertex == -1) break;
                cin >> weight;
                adjList[i].push_back(make_pair(vertex, weight));

                // Store edge in the global list of edges
                if (vertex > i && weight != INF) {
                    Edge e;
                    e.src = i;
                    e.dest = vertex;
                    e.weight = weight;
                    edges.push_back(e);
                }
            }
        }
    }

    void kruskalMST() {
        sortEdges();  // Sort edges by weight using manual sort

        vector<int> parent(V), rank(V, 0);
        for (int i = 0; i < V; i++) {
            parent[i] = i;
        }

        vector<Edge> mst;
        int totalWeight = 0;

        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i].src;
            int v = edges[i].dest;

            int setU = find(parent, u);
            int setV = find(parent, v);

            if (setU != setV) {
                mst.push_back(edges[i]);
                totalWeight += edges[i].weight;
                unionSets(parent, rank, setU, setV);
            }

            if (mst.size() == V - 1) break;
        }

        cout << "\nEdge \tWeight\n";
        for (int i = 0; i < mst.size(); i++) {
            cout << mst[i].src << " - " << mst[i].dest << "\t" << mst[i].weight << "\n";
        }
        cout << "Total Weight of MST: " << totalWeight << endl;
    }
};

int main() {
    Graph g;
    int choice;

    do {
        cout << "\n====== MENU ======\n";
        cout << "1. Input Graph\n";
        cout << "2. Apply Kruskal's Algorithm\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                g.inputGraph();
                break;
            case 2:
                g.kruskalMST();
                break;
            case 3:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
