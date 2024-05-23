#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjMatrix;

public:
    Graph(int V) : V(V), adjMatrix(V, vector<int>(V, 0)) {}

    void addEdge(int u, int v, int w) {
        adjMatrix[u][v] = adjMatrix[v][u] = w;
    }

    vector<int> dijkstra(int src) {
        vector<int> dist(V, INT_MAX);  // Vector to store shortest distances
        vector<bool> visited(V, false); // Vector to keep track of visited vertices

        // Create a priority queue to get the vertex with the minimum distance
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Start from the source vertex
        dist[src] = 0;
        pq.push(make_pair(0, src));

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (visited[u]) {
                continue;
            }

            visited[u] = true;

            // Traverse all adjacent vertices
            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v] && !visited[v] && dist[v] > dist[u] + adjMatrix[u][v]) {
                    dist[v] = dist[u] + adjMatrix[u][v];
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        return dist;
    }
};
