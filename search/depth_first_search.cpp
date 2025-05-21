#include <iostream>
#include <vector>

class Graph {
private:
    struct Node {
        char data;
        explicit Node(char data) : data(data) {}
    };

    std::vector<Node> nodes;
    std::vector<std::vector<int>> matrix;

    void dFSHelper(int src, std::vector<bool>& visited) {
        if (visited[src]) return;

        visited[src] = true;
        std::cout << nodes[src].data << " = visited.\n";

        for (size_t i = 0; i < matrix[src].size(); i++) {
            if (matrix[src][i] == 1) {
                dFSHelper(i, visited);
            }
        }
    }

public:
    explicit Graph(int size) : matrix(size, std::vector<int>(size, 0)) {}

    void addNode(char data) {
        nodes.emplace_back(data);
    }

    void addEdge(int src, int dst) {
        if (src < nodes.size() && dst < nodes.size()) {
            matrix[src][dst] = 1;
        }
    }

    bool checkEdge(int src, int dst) {
        return src < nodes.size() && dst < nodes.size() && matrix[src][dst] == 1;
    }

    void print() {
        std::cout << "  ";
        for (const auto& node : nodes) {
            std::cout << node.data << " ";
        }
        std::cout << "\n";

        for (size_t i = 0; i < matrix.size(); i++) {
            std::cout << nodes[i].data << " ";
            for (size_t j = 0; j < matrix[i].size(); j++) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    void depthFirstSearch(int src) {
        std::vector<bool> visited(matrix.size(), false);
        dFSHelper(src, visited);
    }
};

int main() {
    Graph graph(5);
    graph.addNode('A');
    graph.addNode('B');
    graph.addNode('C');
    graph.addNode('D');
    graph.addNode('E');

    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(1, 4);
    graph.addEdge(2, 3);
    graph.addEdge(2, 4);
    graph.addEdge(4, 0);
    graph.addEdge(4, 2);

    graph.print();
    graph.depthFirstSearch(4);

    return 0;
}
