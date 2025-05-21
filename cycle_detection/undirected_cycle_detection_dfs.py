from collections import deque

class Graph :

    def __init__(self,size : int) :
        self.size = size
        self.adj_matrix = [[0]*size for _ in range(size)]
        self.vertex_data = ['']*size

    def add_edge(self,u,v):
        if 0<=u<self.size and 0<= v<self.size :
            self.adj_matrix[u][v] = 1
            self.adj_matrix[v][u] = 1

    def add_vertex_data(self,vertex,data) :
        if 0<=vertex < self.size :
            self.vertex_data[vertex] = data
    
    def __str__(self):
        matrix_str = "\n".join([" ".join(map(str,row)) for row in self.adj_matrix])
        vertex_str = "\n".join([f"Vertex {i} : {data}" for i, data in enumerate(self.vertex_data)])
        return f"Adjacency Matrix :\n{matrix_str}\n\nVertex Data :\n{vertex_str}"
    
    def is_cyclic_dfs(self,v:int,visited:list,parent:int) -> bool :
        """Helper DFS function for cycle detection."""
        visited[v] = True
        
        for neighbor in range(self.size) :
            if self.adj_matrix[v][neighbor] :  # if there's an edge.
                if not visited[neighbor] :
                    if self.is_cyclic_dfs(neighbor,visited,v):
                        return True
                elif neighbor != parent :  # cycle found.
                    return True    
              
              
    def is_cyclic(self):
        """Checks if the graph contains a cycle using DFS traversal."""
        visited = [False]*self.size
        for node in range(self.size):
            if not visited[node] :
                if self.is_cyclic_dfs(node,visited,-1) :  # passing -1 here,since first node doesn't have parent node.
                    return True
        return False
    

# Example Usage
g = Graph(7)

# Add vertex labels
for i, label in enumerate(['A', 'B', 'C', 'D', 'E', 'F', 'G']):
    g.add_vertex_data(i, label)

# Add edges
edges = [(3, 0), (0, 2), (0, 4), (4, 2), (2, 5), (2, 1), (2, 6), (1, 5)]
for u, v in edges:
    g.add_edge(u, v)

# Print graph
print(g)

# Check if graph contains a cycle
print("\nGraph has cycle:", g.is_cyclic())