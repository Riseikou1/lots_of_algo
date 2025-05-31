#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>
#include <numeric>
#include <string_view>
#include <optional>
using namespace std;

class Graph {
    int size;
    vector<string> vertex_data;
    vector<tuple<int, int, int>> edges;
public:
    Graph(int size) : size(size), vertex_data(size, "") {}

    void add_vertex_data(int vertex, const string& data) {
        vertex_data[vertex] = data;
    }

    void add_edge(int u, int v, int weight) {
        edges.emplace_back(u, v, weight);
    }

    optional<tuple<vector<int>,vector<int>>> bellman_ford(string_view start_label){
        auto it = label_to_index.find(string(start_label));
        if(it == label_to_index.end()) return nullopt;
    }


};

int main() {
    Graph g(7);
    vector<string> labels = { "A", "B", "C", "D", "E", "F", "G" };
    for (int i = 0; i < labels.size(); ++i) {
        g.add_vertex_data(i, labels[i]);
    }

    g.add_edge(0, 1, 4);   // A-B
    g.add_edge(0, 6, 10);  // A-G
    g.add_edge(0, 2, 9);   // A-C
    g.add_edge(1, 2, 8);   // B-C
    g.add_edge(2, 3, 5);   // C-D
    g.add_edge(2, 4, 2);   // C-E
    g.add_edge(2, 6, 7);   // C-G
    g.add_edge(3, 4, 3);   // D-E
    g.add_edge(3, 5, 7);   // D-F
    g.add_edge(4, 6, 6);   // E-G
    g.add_edge(5, 6, 11);  // F-G

    cout << string(44, '*') << "\nKruskal's Algorithm - Minimum Spanning Tree:\n" << string(44, '*') << endl;

    g.kruskal();

    return 0;
}
