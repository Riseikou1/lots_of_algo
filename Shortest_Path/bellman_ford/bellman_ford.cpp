#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

class Graph {
    int size;
    vector<vector<int>> adj_matrix;
    vector<string> vertex_data;

public:
    Graph(int size) : size(size), adj_matrix(size, vector<int>(size, 0)), vertex_data(size, "") {}

    void add_edge(int u, int v, int weight) {
        if (u >= 0 && u < size && v >= 0 && v < size)
            adj_matrix[u][v] = weight;
    }

    void add_vertex_data(int vertex, const string& data) {
        if (vertex >= 0 && vertex < size)
            vertex_data[vertex] = data;
    }

    // Returns tuple: (negative_cycle_detected, distances, predecessors)
    tuple<bool, vector<int>, vector<int>> bellman_ford(const string& start_vertex_data) const {
        int start_vertex = find(vertex_data.begin(), vertex_data.end(), start_vertex_data) - vertex_data.begin();
        vector<int> distances(size, numeric_limits<int>::max());
        vector<int> predecessors(size, -1);
        distances[start_vertex] = 0;

        for (int i = 0; i < size - 1; ++i) {
            bool updated = false;
            for (int u = 0; u < size; ++u) {
                for (int v = 0; v < size; ++v) {
                    if (adj_matrix[u][v] != 0 && distances[u] != numeric_limits<int>::max()) {
                        int new_dist = distances[u] + adj_matrix[u][v];
                        if (new_dist < distances[v]) {
                            distances[v] = new_dist;
                            predecessors[v] = u;
                            updated = true;
                        }
                    }
                }
            }
            if (!updated) break;
        }
        // Negative cycle detection
        for (int u = 0; u < size; ++u) {
            for (int v = 0; v < size; ++v) {
                if (adj_matrix[u][v] != 0 && distances[u] != numeric_limits<int>::max()) {
                    if (distances[u] + adj_matrix[u][v] < distances[v]) {
                        return {true, {}, {}}; // Negative cycle detected
                    }
                }
            }
        }
        return {false, distances, predecessors};
    }

    // Path as a string: D->A->E, etc.
    string get_path(const vector<int>& predecessors, const string& start_vertex_data, const string& end_vertex_data) const {
        int start_vertex = find(vertex_data.begin(), vertex_data.end(), start_vertex_data) - vertex_data.begin();
        int end_vertex = find(vertex_data.begin(), vertex_data.end(), end_vertex_data) - vertex_data.begin();
        vector<string> path;
        int current = end_vertex;
        while (current != -1) {
            path.push_back(vertex_data[current]);
            if (current == start_vertex) break;
            current = predecessors[current];
        }
        if (path.back() != vertex_data[start_vertex]) return ""; // No path exists
        reverse(path.begin(), path.end());
        string result = path[0];
        for (size_t i = 1; i < path.size(); ++i)
            result += "->" + path[i];
        return result;
    }
};

int main() {
    Graph g(5);
    g.add_vertex_data(0, "A");
    g.add_vertex_data(1, "B");
    g.add_vertex_data(2, "C");
    g.add_vertex_data(3, "D");
    g.add_vertex_data(4, "E");

    g.add_edge(3, 0, 4);   // D -> A, weight 4
    g.add_edge(3, 2, 7);   // D -> C, weight 7
    g.add_edge(3, 4, 3);   // D -> E, weight 3
    g.add_edge(0, 2, 4);   // A -> C, weight 4
    g.add_edge(2, 0, -3);  // C -> A, weight -3
    g.add_edge(0, 4, 5);   // A -> E, weight 5
    g.add_edge(4, 2, 3);   // E -> C, weight 3
    g.add_edge(1, 2, -4);  // B -> C, weight -4
    g.add_edge(4, 1, 2);   // E -> B, weight 2

    cout << "\nThe Bellman-Ford Algorithm starting from vertex D:\n";
    auto [negative_cycle, distances, predecessors] = g.bellman_ford("D");

    if (!negative_cycle) {
        for (int i = 0; i < g.vertex_data.size(); ++i) {
            if (distances[i] != numeric_limits<int>::max()) {
                string path = g.get_path(predecessors, "D", g.vertex_data[i]);
                cout << "Shortest path from D to " << g.vertex_data[i] << ": " << path
                     << ", Distance: " << distances[i] << endl;
            } else {
                cout << "No path from D to " << g.vertex_data[i] << ", Distance: Infinity" << endl;
            }
        }
    } else {
        cout << "Negative weight cycle detected. Cannot compute shortest paths.\n";
    }
    return 0;
}
