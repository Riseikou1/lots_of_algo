import heapq

class Graph:
    def __init__(self,size):
        self.size = size
        self.graph = [[0]*size for _ in range(size)]
        self.vertex_data = ['']*size
    
    def add_edge(self,u,v,weight):
        self.graph[u][v] = weight

    def add_vertex_data(self,vertex,data):
        self.vertex_data[vertex] = data
    
    def dijkstra(self,start_vertex_data):
        start = self.vertex_data.index(start_vertex_data)
        distances = [float('inf')]*self.size
        distances[start] = 0
        previous = [None]*self.size
        visited = [False]*self.size

        minheap = [(0,start)]

        while minheap:
            cur_dist,u = heapq.heappop(minheap)
            if visited[u] : continue
            visited[u] = True
            for v in range(len(self.graph[u])):
                weight = self.graph[u][v]
                if weight != 0 and not visited[v]:
                    new_dist = weight + cur_dist
                    if new_dist < distances[v] and not visited[v]:
                        previous[v] = u
                        distances[v] = new_dist
                        heapq.heappush(minheap,(new_dist,v))

        return distances,previous

    def print_paths(self,start_vertex_data,distances,previous):
        print(f" Minimum distance from {start_vertex_data} to every other nodes.")

        for i in range(self.size):
            path = []
            j = i
            while j is not None :
                path.append(self.vertex_data[j])
                j = previous[j]

            str_path = " -> ".join(path)
            str_dist = "inf" if distances[i] == float('inf') else distances[i]

            print(f"{start_vertex_data} to {self.vertex_data[i]} : {str_path} | Distance : {str_dist}")


g = Graph(7)

labels = ['A', 'B', 'C', 'D', 'E', 'F', 'G']

for i , label in enumerate(labels):
    g.add_vertex_data(i,label)

g.add_edge(3, 0, 4)  # D -> A
g.add_edge(3, 4, 2)  # D -> E
g.add_edge(0, 2, 3)  # A -> C
g.add_edge(0, 4, 4)  # A -> E
g.add_edge(4, 2, 4)  # E -> C
g.add_edge(4, 6, 5)  # E -> G
g.add_edge(2, 5, 5)  # C -> F
g.add_edge(2, 1, 2)  # C -> B
g.add_edge(1, 5, 2)  # B -> F
g.add_edge(6, 5, 5)  # G -> F

distances, previous = g.dijkstra('D')
g.print_paths('D', distances, previous)

