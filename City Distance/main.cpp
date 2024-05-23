#include <iostream>
#include <string>
#include <sstream>
#include <climits>
#include <unordered_map>

#include "dijkstra.cpp"

using namespace std;

unordered_map<string, int> buildMap() {
  unordered_map<string, int> city_map;
  string city_names;

  // Read line of city names
  getline(cin, city_names);

  // Split string by spaces
  stringstream ss(city_names);
  string city;
  int count = 0;

  // Iterate over each city name and add to map
  while (getline(ss, city, ' ')) {
    city_map[city] = count++;
  }

  return city_map;
}

int main() {
    unordered_map<string, int> city_map;
    city_map = buildMap();
    Graph city_graph(city_map.size());

    string city1, city2;
    int distance;

    while(cin >> city1 >> city2 >> distance) {
        if(city_map.find(city1) == city_map.end() || city_map.find(city2) == city_map.end()) {
            cout << "Invalid city name" << endl;
            continue;
        }
        if(distance == 0) break;
        city_graph.addEdge(city_map[city1], city_map[city2], distance);
    }

    auto dist = city_graph.dijkstra(city_map[city1]);
    if(dist[city_map[city2]] == INT_MAX) {
        cout << "No path found" << endl;
    } else {
    	cout << "Distance to " << city2 << ": " << dist[city_map[city2]] << endl;
    }
}