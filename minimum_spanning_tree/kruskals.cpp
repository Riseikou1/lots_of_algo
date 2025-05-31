#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>
#include <numeric>
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

    // No const! Modifies parent for path compression.
    int find(vector<int>& parent, int i) {
        if (parent[i] != i) {
            parent[i] = find(parent, parent[i]);
        }
        return parent[i];
    }

    // union_sets takes node indices, finds roots inside
    void union_sets(vector<int>& parent, vector<int>& rank, int x, int y) {
        int root_x = find(parent, x);
        int root_y = find(parent, y);

        if (root_x == root_y) return;
        if (rank[root_x] < rank[root_y]) {
            parent[root_x] = root_y;
        }
        else if (rank[root_x] > rank[root_y]) {
            parent[root_y] = root_x;
        }
        else {
            parent[root_y] = root_x;
            ++rank[root_x];
        }
    }

    void kruskal() {
        vector<tuple<int, int, int>> mst;
        int total_weight = 0;
        vector<tuple<int, int, int>> sorted_edges = edges;
        sort(sorted_edges.begin(), sorted_edges.end(), [](const auto& a, const auto& b) {
            return get<2>(a) < get<2>(b);
        });
        vector<int> parent(size), rank(size, 0);
        iota(parent.begin(), parent.end(), 0);

        for (const auto& [u, v, w] : sorted_edges) {
            int root_u = find(parent, u);
            int root_v = find(parent, v);
            if (root_u != root_v) {
                mst.emplace_back(u, v, w);
                total_weight += w;
                union_sets(parent, rank, u, v); // Pass indices, not roots!
            }
        }
        cout << "Edge\tWeight\n";
        for (const auto& [u, v, w] : mst) {
            cout << vertex_data[u] << " - " << vertex_data[v] << "\t  " << w << endl;
        }
        cout << "Total Weight: " << total_weight << "\n";
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
