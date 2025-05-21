from collections import deque

class Graph:
    def __init__(self, size: int):
        self.size = size
        self.adj_matrix = [[0] * size for _ in range(size)]
        self.vertex_data = [''] * size

    def add_edge(self, u: int, v: int):
        """Adds an undirected edge between vertices u and v."""
        if 0 <= u < self.size and 0 <= v < self.size:
            self.adj_matrix[u][v] = 1
            self.adj_matrix[v][u] = 1  # comment this shit for directed graph.

    def add_vertex(self, vertex: int, data: str):
        """Assigns data to a vertex."""
        if 0 <= vertex < self.size:
            self.vertex_data[vertex] = data

    def print_graph(self):
        """Prints the adjacency matrix and vertex data."""
        print("Adjacency Matrix:")
        for row in self.adj_matrix:
            print(" ".join(map(str, row)))
        
        print("\nVertex Data:")
        for vertex, data in enumerate(self.vertex_data):
            print(f"Vertex {vertex}: {data}")

    def bfs(self, start_vertex_data: str):
        """Performs Breadth-First Search (BFS) from the given vertex data."""
        if start_vertex_data not in self.vertex_data:
            print("Start vertex not found!")
            return
        
        start_vertex = self.vertex_data.index(start_vertex_data)
        queue = deque([start_vertex])
        visited = [False] * self.size
        visited[start_vertex] = True

        print("BFS Traversal:", end=" ")
        while queue:
            current_vertex = queue.popleft()
            print(self.vertex_data[current_vertex], end=" ")

            for neighbor in range(self.size):
                if self.adj_matrix[current_vertex][neighbor] == 1 and not visited[neighbor]:
                    queue.append(neighbor)
                    visited[neighbor] = True
        print()

# Example usage
g = Graph(5)
g.add_vertex(0, 'A')
g.add_vertex(1, 'B')
g.add_vertex(2, 'C')
g.add_vertex(3, 'D')
g.add_vertex(4, 'E')

g.add_edge(0, 1)
g.add_edge(1, 2)
g.add_edge(1, 4)
g.add_edge(2, 3)
g.add_edge(2, 4)
g.add_edge(4, 0)
g.add_edge(4, 2)

g.print_graph()
g.bfs('A')
