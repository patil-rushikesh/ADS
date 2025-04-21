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

    vector<vector<int>> adjMatrix;
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

    void sortEdges() {
        int n = edges.size();
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++) {
                if (edges[j].weight < edges[minIdx].weight)
                    minIdx = j;
            }
            if (minIdx != i) {
                Edge temp = edges[i];
                edges[i] = edges[minIdx];
                edges[minIdx] = temp;
            }
        }
    }

public:
    Graph() {
        adjMatrix = vector<vector<int>>(V, vector<int>(V, INF));
    }

    void inputGraph() {
        edges.clear();
        cout << "Enter the adjacency matrix (" << V << "x" << V << "):\n";
        cout << "(Use 0 for no direct edge between vertices)\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                int val;
                cin >> val;
                if (val == 0 && i != j)
                    val = INF;
                adjMatrix[i][j] = val;

                if (j > i && val != INF) {
                    Edge e;
                    e.src = i;
                    e.dest = j;
                    e.weight = val;
                    edges.push_back(e);
                }
            }
        }
    }

    void kruskalMST() {
        sortEdges();

        vector<int> parent(V), rank(V, 0);
        for (int i = 0; i < V; i++)
            parent[i] = i;

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

            if (mst.size() == V - 1)
                break;
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
