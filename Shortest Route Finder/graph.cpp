#include "graph.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>
#include <queue>
#include <unordered_map>

using namespace std;

void Graph::loadCityData(City cityArray[], int& citySize) {
	ifstream infile("city.txt");
	if (infile.is_open()) {
		int i = 0;
		while (infile >> cityArray[i].cityNum >> cityArray[i].cityCode >> cityArray[i].cityName >> cityArray[i].pop >> cityArray[i].elev) {
			i++;
		}
		citySize = i;  // Update citySize to match the actual number of cities read
	}
	else {
		cout << "Error opening city file!" << endl;
	}
}

void Graph::loadRoadData(Road roadArray[], int& roadSize) {
	ifstream infile("road.txt");
	if (infile.is_open()) {
		int i = 0;
		while (infile >> roadArray[i].start >> roadArray[i].end >> roadArray[i].distance) {
			i++;
		}
		roadSize = i;  // Update roadSize to match the actual number of roads read
	}
	else {
		cout << "Error opening road file!" << endl;
	}
}

bool Graph::isValidCityCode(const string& cityCode, City cityArray[], int citySize) {
for (int i = 0; i < citySize; i++) {
if (cityArray[i].cityCode == cityCode) {
return true;
}
}
return false;
}

void Graph::addEdge(vector<pair<int, int>> adj[], int u, int v, int wt) {
adj[u].push_back(make_pair(v, wt)); // add edge u -> v with weight
}

void Graph::shortestPath(vector<pair<int, int>> adj[], int V, int src, int target, City cityArray[]) {
priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
vector<int> dist(V, INT_MAX);
dist[src] = 0;
vector<int> prev(V, -1);
pq.push(make_pair(0, src));

while (!pq.empty()) {
int u = pq.top().second;
pq.pop();

for (auto& neighbor : adj[u]) {
int v = neighbor.first;
int weight = neighbor.second;

if (dist[v] > dist[u] + weight) {
dist[v] = dist[u] + weight;
pq.push(make_pair(dist[v], v));
prev[v] = u;
}
}
}

if (dist[target] == INT_MAX) {
cout << "No route from " << cityArray[src].cityName << " to " << cityArray[target].cityName << endl;
return;
}

cout << "From City: " << cityArray[src].cityName
<< ", population " << cityArray[src].pop
<< ", elevation " << cityArray[src].elev << endl;

cout << "To City: " << cityArray[target].cityName
<< ", population " << cityArray[target].pop
<< ", elevation " << cityArray[target].elev << endl;

cout << "The shortest distance from " << cityArray[src].cityName
<< " to " << cityArray[target].cityName
<< " is " << dist[target] << endl;

vector<string> path;
int curr = target;
while (curr != -1) {
path.push_back(cityArray[curr].cityName);
curr = prev[curr];
}

cout << "through the route: ";
for (int i = path.size() - 1; i >= 0; i--) {
cout << path[i];
if (i > 0) cout << "->";
}
cout << endl;
}

