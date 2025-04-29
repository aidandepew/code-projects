#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Define a structure to hold city data
struct City {
    int cityNum; // City ID
    string cityCode; // 2-letter City Code
    string cityName; // Full City Name
    int pop; // Population
    int elev; // Elevation
};

// Define a structure to hold road (edge) data
struct Road {
    int start; // Starting city ID
    int end;   // Ending city ID
    int distance; // Distance from start to end
};

// Define a structure for the graph class
class Graph {
public:
    // Load city data from the file
    void loadCityData(City cityArray[], int& citySize);

    // Load road data from the file
    void loadRoadData(Road roadArray[], int& roadSize);

    // Check if city code is valid
    bool isValidCityCode(const string& cityCode, City cityArray[], int citySize);

    // Add an edge between cities in the adjacency list
    void addEdge(vector<pair<int, int>> adj[], int u, int v, int wt);

    // Run Dijkstra's algorithm to find the shortest path
    void shortestPath(vector<pair<int, int>> adj[], int V, int src, int target, City cityArray[]);

private:
    // Helper structure for priority queue (used in Dijkstra)
    typedef pair<int, int> iPair;
};

#endif
