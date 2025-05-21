#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <unordered_map>
#include <limits>
#include <optional>
#include <tuple>
#include <algorithm>

using namespace std;

class Graph {
private:
    int size;
    vector<tuple<int, int, int>> edges; // (from, to, weight)
    unordered_map<string, int> label_to_index;
    vector<string> index_to_label;

public:
    Graph(int size) : size(size), index_to_label(size) {}

    void add_vertex_data(int index, const string& label) {
        if (index >= 0 && index < size) {
            label_to_index[label] = index;
            index_to_label[index] = label;
        }
    }

    void add_edge(int from, int to, int weight) {
        edges.emplace_back(from, to, weight);
    }

    optional<tuple<vector<int>, vector<int>>> bellman_ford(string_view start_label) const {
        auto it = label_to_index.find(string(start_label));
        if (it == label_to_index.end()) return nullopt;

        int start = it->second;
        vector<int> dist(size, numeric_limits<int>::max());
        vector<int> pred(size, -1);
        dist[start] = 0;

        for (int i = 0; i < size - 1; ++i) {
            for (const auto& [u, v, w] : edges) {
                if (dist[u] != numeric_limits<int>::max() && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pred[v] = u;
                }
            }
        }

        for (const auto& [u, v, w] : edges) {
            if (dist[u] != numeric_limits<int>::max() && dist[u] + w < dist[v]) {
                return nullopt; // negative cycle
            }
        }

        return make_tuple(dist, pred);
    }

    string get_path(string_view start_label, string_view end_label, const vector<int>& pred) const {
        int start = label_to_index.at(string(start_label));
        int end = label_to_index.at(string(end_label));
        vector<string> path;

        for (int curr = end; curr != -1; curr = pred[curr]) {
            path.push_back(index_to_label[curr]);
            if (curr == start) break;
        }

        reverse(path.begin(), path.end());
        if (path.front() != start_label) return "No path";

        string result;
        for (const auto& node : path) result += node + "->";
        result.pop_back(); result.pop_back(); // remove last arrow
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

    g.add_edge(3, 0, 4);  // D -> A
    g.add_edge(3, 2, 7);  // D -> C
    g.add_edge(3, 4, 3);  // D -> E
    g.add_edge(0, 2, 4);  // A -> C
    g.add_edge(2, 0, -3); // C -> A
    g.add_edge(0, 4, 5);  // A -> E
    g.add_edge(4, 2, 3);  // E -> C
    g.add_edge(1, 2, -4); // B -> C
    g.add_edge(4, 1, 2);  // E -> B

    auto result = g.bellman_ford("D");
    if (!result) {
        cout << "Negative weight cycle detected. Cannot compute shortest paths.\n";
        return 0;
    }

    const auto& [distances, preds] = *result;
    for (int i = 0; i < distances.size(); ++i) {
        cout << "Shortest path from D to " << g.index_to_label[i] << ": ";
        if (distances[i] == numeric_limits<int>::max()) {
            cout << "No path, Distance: ∞\n";
        } else {
            cout << g.get_path("D", g.index_to_label[i], preds) << ", Distance: " << distances[i] << '\n';
        }
    }

    return 0;
}
