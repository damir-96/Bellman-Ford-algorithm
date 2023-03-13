#include <vector>
#include <array>
#include <iostream>
#include <string>
#include <cstdlib>
#include <Windows.h>
#include <iomanip>
#include <fstream>
#include <shellapi.h>
using namespace std;

int V;

struct Edge {
	int src, dest, weight;
};
struct Graph {
	int V, E;
	struct Edge* edge;
};
struct Graph* createGraph(int V, int E) {
	struct Graph* graph = new Graph;
	graph->V = V;
	graph->E = E;
	graph->edge = new Edge[E];
	return graph;
}
void BellmanFord(struct Graph* graph, int src) {
	int const V = graph->V;
	int E = graph->E;
	int dist[5];
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX;
	dist[src] = 0;
	for (int i = 1; i <= V - 1; i++) {
		for (int j = 0; j < E; j++) {
			int u = graph->edge[j].src;
			int v = graph->edge[j].dest;
			int weight = graph->edge[j].weight;
			if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
				dist[v] = dist[u] + weight;
		}
	}
	for (int i = 0; i < E; i++) {
		int u = graph->edge[i].src;
		int v = graph->edge[i].dest;
		int weight = graph->edge[i].weight;
		if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
			printf("Graph contains negative weight cycle");
			return;
		}
	}
	cout << "Vertex               |";
	for (int i = 0; i < V; ++i)
		cout << " " << i << " | ";
	cout << endl;
	cout << "----------------------------------------------------" << endl;
	cout << "Distance from source |";
	for (int i = 0; i < V; ++i)
		cout << " " << dist[i] << " | ";
	cout << endl;


	return;
}
int run() {

	int V, E;
	int s, d, w;
		
		cout << "Enter the number of vertices: ";
		cin >> V;
		cout << "Enter the number of edges: ";
		cin >> E;
		struct Graph* graph = createGraph(V, E);
		for (int i = 0; i < E; i++) {
			cout << "Edge " << i;
			cout << endl;
			cout << "Enter source: ";
			cin >> s;
			cout << "Enter destination: ";
			cin >> d;
			cout << "Enter weight: ";
			cin >> w;
			graph->edge[i].src = s;
			graph->edge[i].dest = d;
			graph->edge[i].weight = w;
		}
		cout << endl;
		cout << endl;
		BellmanFord(graph, 0);
		
	
	return 0;
}

void createMatrix() {
	
	cout << "Enter number of vertices: ";
	cin >> V;
	int M[5][5];

	cout << "Enter wights of edges in the following order: " << endl;
	cout << "(for no edge set value to 0)" << endl;
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			cout << "(" << i << "," << j << "): ";
			cin >> M[i][j];

		}
	}

	for (int i = 0; i < V; i++) {
		cout << endl;
		for (int j = 0; j < V; j++) {
			cout << setw(3) << M[i][j];
		}
		cout << endl;
	}

	ofstream edgesFile("edges.txt");
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			edgesFile << setw(3) << M[i][j];
		}
		edgesFile <<";"<< endl;
	}

	edgesFile.close();
}

int main() {
	int choice = 0;
	cout << "Bellman Ford Algorithm" << endl;
	cout << "Menu: " << endl;
	cout << "1. Bellman Ford algorithm in C++" << endl;
	cout << "2. Bellman Ford algorithm in Octave" << endl;
	cout << "3. Bellman Ford algorithhm project repository link" << endl;
	

	while (choice < 1 || choice > 3) {
		cout << "Enter choice: ";
		cin >> choice;
		cout << endl;
		switch (choice) {
		case 1:
			run();
			break;
		case 2:
			createMatrix();
			cout << endl;
			cout << "A file named 'edges' has been created and recorded. The size of the matrix is " << V << " x " << V << endl;
			cout << "The matrix can be used to trigger the Bellman Ford algorithm within Matlab or Octave" << endl;
			break;
		case 3:
			system("start Chrome www.github.com/damir-96/Bellman-Ford-algorithm.git");
			break;
		default:
			cout << "Illegal choice!" << endl;
			break;
		}
	}
	

	return 0;
}