#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
#include <algorithm>

using namespace std;

#define V 6

int graph[V][V] = { { 0, 16, 13, 0, 0, 0 }, { 0, 0, 10, 12, 0, 0 }, { 0, 4, 0,
		0, 14, 0 }, { 0, 0, 9, 0, 0, 20 }, { 0, 0, 0, 7, 0, 4 }, { 0, 0, 0, 0,
		0, 0 } };
bool bfs(int rGraph[V][V], int s, int t, int parent[]) {

	bool visited[V];
	memset(visited, 0, sizeof(visited));

	queue<int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (int v = 0; v < V; v++) {
			if (visited[v] == false && rGraph[u][v] > 0) {
				q.push(v);
				parent[v] = u;   //parent[0]=-1,[1]=0,[2]=0,[3]=1,[4]=2,[5]=3...
				visited[v] = true;
			}
		}
	}
	return (visited[t] == true);
}

int fordFulkerson(int graph[V][V], int s, int t) {
	int u, v;

	int rGraph[V][V];
	for (u = 0; u < V; u++)
		for (v = 0; v < V; v++)
			rGraph[u][v] = graph[u][v];

	int parent[V];

	int max_flow = 0;

	while (bfs(rGraph, s, t, parent)) {

		int path_flow = INT_MAX;
		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			path_flow = min(path_flow, rGraph[u][v]);
		}

		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;
		}

		max_flow += path_flow;
	}

	return max_flow;
}

//Modified Ford Fulkerson
void newfordFulkerson(int graph[V][V], int s, int t) {
	int n = 0;
	int u = 0, v = 0;
	int j = 0;
	int it;
	int k = 0, f = 0;

	int pa[V][V] = { { -1, -1, -1, -1, -1, -1 }, { -1, -1, -1, -1, -1, -1 }, {
			-1, -1, -1, -1, -1, -1 }, { -1, -1, -1, -1, -1, -1 }, { -1, -1, -1,
			-1, -1, -1 }, { -1, -1, -1, -1, -1, -1 } };              //pa stores the path of each augmenting path

	int a[V] = { INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX }; //'a' stores min link cap of eacg augmenting path
	int rGraph[V][V];
	for (int h = 0; h < V; h++)
		for (int l = 0; l < V; l++)
			rGraph[h][l] = graph[h][l];

	int parent[V];

	int max_flow = 0;

	while (bfs(rGraph, s, t, parent))  
	{
		int path_flow = INT_MAX;

		for (int v = t; v != s; v = parent[v]) {
			u = parent[v]; //Going back from destination to source

			path_flow = min(path_flow, rGraph[u][v]);
			pa[k][j] = v;
			j++;

		}
		cout << "j " << j << "\n";
		a[f] = path_flow; 
		f++;
		pa[k][j] = u;
		k++;

		j = 0;

		for (int v = t; v != s; v = parent[v]) {
			int u = parent[v];
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;
		}

		max_flow += path_flow;

	}

	cout << "\n" << "The smallest element is " << *std::min_element(a, a + V)
			<< "\n";
	it = *std::min_element(a, a + V);

	n = distance(a, find(a, a + V, it));
	/*for (int j = 0; j < V; j++) {
		cout << "pa" << pa[n][j] << "\n";
	}*/

	for (int r = 0; r < V; r++) {
		int q = pa[n][r]; //pa[n][r] gives the augmenting path of minmum capacity link
		int p = pa[n][r + 1];
        
        //Increasing the link capacity that less than or equal to min capacity along the path
		if (rGraph[p][q] <= 0 && q != -1 && p != -1) {
			graph[p][q]++;
		} 
	}

	
}

int main() {
	int y = 0;
	int maxcapacity;
	int change;
	int s = 0, t = 5;
	int u = 0, v = 0;
	
	cout << "enter the number x liters/sec";
	cin >> y;
	
	maxcapacity = fordFulkerson(graph, 0, 5);

	for (u = 0; u < V; u++)
		for (v = 0; v < V; v++)
			cout << "   " << graph[u][v];  //prints original graph

	cout << "\n";

	if (y > maxcapacity) {
		int loop = y - maxcapacity;
		for (int b = 0; b < loop; b++) {
			 newfordFulkerson(graph, 0, 5);

			
			for (u = 0; u < V; u++)
				for (v = 0; v < V; v++)
					cout << "   " << graph[u][v]; //prints the modified graph
			cout << "\n ";
			int maxcap = fordFulkerson(graph, 0, 5);
			cout << "maximum capacity " << maxcap << "\n";
		}

	} else
		cout << "No capacities have to be changed";

	return 0;
}

