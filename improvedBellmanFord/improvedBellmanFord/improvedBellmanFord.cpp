#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;

struct Edge {
    int from, to, weight;
};

vector<int> bellman_ford(int source, vector<Edge>& edges, int num_vertices) {
    //initialize distances to all vertices as infinity except the source vertex
    vector<int> distances(num_vertices, INF);
    distances[source] = 0;

    //initialize a min-heap priority queue to store vertices to visit next
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, source));

    //initialize the vector to keep track of which vertices are in the priority queue
    vector<int> in_queue(num_vertices, 0);
    in_queue[source] = 1;

    //Bellman Ford algorithm
    int num_iterations = 0;

    while (!pq.empty() && num_iterations < num_vertices - 1) {
        //pop the vertex with the smallest distance from the priority queue
        int u = pq.top().second;
        pq.pop();
        in_queue[u] = 0;

        //relax all edges
        for (int i = 0; i < edges.size(); i++) {
            int v = edges[i].to;
            int weight = edges[i].weight;
            if (edges[i].from == u && distances[u] + weight < distances[v]) {
                //update distance if it can be updated
                distances[v] = distances[u] + weight;

                //add vertex v to the priority queue if it is not already in it
                if (!in_queue[v]) {
                    pq.push(make_pair(distances[v], v));
                    in_queue[v] = 1;
                }
            }
        }

        //increment number of iterations performed
        num_iterations++;
    }


    return distances;
}

int main() {
    //define number of vertices
    int num_vertices = 5;
    vector<Edge> edges = {
        {0, 1, 1},
        {2, 1, 2},
        {0, 2, 4},
        {1, 2, 1},
        {1, 3, 8},
        {4, 3, 4},
        {2, 4, 2},
        {3, 4, 2}
   
    };
    int source = 0;

    //run the Bellman Ford algorithm
    vector<int> distances = bellman_ford(source, edges, num_vertices);
    for (int i = 0; i < distances.size(); i++) {
        cout << "Shortest distance from source to vertex " << i << " is " << distances[i] << endl;
    }
    return 0;
}
