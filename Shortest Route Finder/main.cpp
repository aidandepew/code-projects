#include <iostream>
#include <string>
#include "graph.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Check if the correct number of arguments is passed
    if (argc != 3) {
        cout << "Usage: ./prog8 <from_city_code> <to_city_code>" << endl;
        return 1;
    }

    string fromCityCode = argv[1];
    string toCityCode = argv[2];

    Graph g;
    int citySize = 20;  // Allow modification
    int roadSize = 100;  // Allow modification

    City cityArray[citySize];
    Road roadArray[roadSize];

    // Load city and road data
    g.loadCityData(cityArray, citySize);
    g.loadRoadData(roadArray, roadSize);

    // Validate the city codes
    if (!g.isValidCityCode(fromCityCode, cityArray, citySize)) {
        cout << "Invalid city code: " << fromCityCode << endl;
        return 1;
    }
    if (!g.isValidCityCode(toCityCode, cityArray, citySize)) {
        cout << "Invalid city code: " << toCityCode << endl;
        return 1;
    }

    // Find the index of the cities based on the city code
    int fromIndex = -1, toIndex = -1;
    for (int i = 0; i < citySize; i++) {
        if (cityArray[i].cityCode == fromCityCode) {
            fromIndex = i;
        }
        if (cityArray[i].cityCode == toCityCode) {
            toIndex = i;
        }
    }

    // Create adjacency list for the graph
    vector<pair<int, int>> adj[citySize];

    // Add edges (roads) to the graph
    for (int i = 0; i < roadSize; i++) {
        g.addEdge(adj, roadArray[i].start, roadArray[i].end, roadArray[i].distance);
    }

    // Call Dijkstra's algorithm to find the shortest path
    g.shortestPath(adj, citySize, fromIndex, toIndex, cityArray);

    return 0;
}
