#include <iostream>
#include <vector>
using namespace std;

#define V 7
#define INF 99999

class Graph {
private:
    vector<vector<int>> adjMatrix;

    int getMinDistanceVertex(const vector<int>& dist, const vector<bool>& visited) {
        int minDist = INF;
        int minVertex = -1;

        for (int i = 0; i < V; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                minVertex = i;
            }
        }

        return minVertex;
    }

public:
    Graph() {
        adjMatrix = vector<vector<int>>(V, vector<int>(V, INF));
    }

    void inputGraph() {
        cout << "Enter the adjacency matrix (" << V << "x" << V << "):\n";
        cout << "(Use 0 for no direct edge between vertices)\n";
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                int val;
                cin >> val;
                if (val == 0 && i != j)
                    val = INF;
                adjMatrix[i][j] = val;
            }
        }
    }

    void dijkstra(int source) {
        vector<int> dist(V, INF);
        vector<bool> visited(V, false);

        dist[source] = 0;

        for (int count = 0; count < V - 1; count++) {
            int u = getMinDistanceVertex(dist, visited);

            if (u == -1) break; // No more reachable vertices
            visited[u] = true;

            for (int v = 0; v < V; v++) {
                if (!visited[v] && adjMatrix[u][v] != INF && dist[u] + adjMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                }
            }
        }

        cout << "\nShortest distances from node " << source << ":\n";
        for (int i = 0; i < V; i++) {
            cout << "To " << i << " : ";
            if (dist[i] == INF)
                cout << "INF";
            else
                cout << dist[i];
            cout << "\n";
        }
    }
};

int main() {
    Graph g;
    int choice;

    do {
        cout << "\n====== MENU ======\n";
        cout << "1. Input Graph\n";
        cout << "2. Apply Dijkstra's Algorithm\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                g.inputGraph();
                break;
            case 2: {
                int src;
                cout << "Enter source vertex (0-" << V - 1 << "): ";
                cin >> src;
                if (src >= 0 && src < V)
                    g.dijkstra(src);
                else
                    cout << "Invalid source vertex.\n";
                break;
            }
            case 3:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
