#include <iostream>
#include <queue>
using namespace std;

int graph[7][7] = {
    {0, 1, 0, 1, 0, 0, 0},
    {1, 0, 1, 1, 1, 0, 0},
    {0, 1, 0, 0, 1, 1, 0},
    {1, 1, 0, 0, 1, 0, 1},
    {0, 1, 1, 1, 0, 1, 1},
    {0, 0, 1, 0, 1, 0, 1},
    {0, 0, 0, 1, 1, 1, 0}
};

void depthFirstSearch(int curr, int destination, int visited[]){
    cout << curr << " ";
    if(curr == destination){
        cout << "\nReached Destination (DFS)" << endl;
        return;
    }
    visited[curr] = 1;
    for(int next = 0; next < 7; next++){
        if(graph[curr][next] && !visited[next]){
            depthFirstSearch(next, destination, visited);
            return;
        }
    }
}

void breadthFirstSearch(int start, int target, int visited[]){
    queue<int> q;
    cout << start << " ";
    visited[start] = 1;
    q.push(start);
    while(!q.empty()){
        int node = q.front();
        q.pop();
        for(int next = 0; next < 7; next++){
            if(graph[node][next] && !visited[next]){
                cout << next << " ";
                visited[next] = 1;
                if(next == target){
                    cout << "\nReached Destination (BFS)" << endl;
                    return;
                }
                q.push(next);
            }
        }
    }
}

int main() {
    int source, target;
    cout << "Enter source node (0-6): ";
    cin >> source;
    cout << "Enter destination node (0-6): ";
    cin >> target;

    if(source < 0 || source >= 7 || target < 0 || target >= 7){
        cout << "Invalid input. Please enter values between 0 and 6." << endl;
        return 0;
    }

    int visitedDFS[7] = {0};
    int visitedBFS[7] = {0};

    cout << "DFS Path: ";
    depthFirstSearch(source, target, visitedDFS);
    cout << "\nBFS Path: ";
    breadthFirstSearch(source, target, visitedBFS);

    return 0;
}
