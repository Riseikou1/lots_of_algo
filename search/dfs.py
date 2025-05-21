class Node :
    def __init__(self,data):
        self.data = data

class graph :
    def __init__(self,size):
        self.nodes = []
        self.matrix = [[0]*size for _ in range(size)]
    
    def addNode(self,node):
        self.nodes.append(node)
    def addEdge(self,src,dst):
        self.matrix[src][dst] = 1
    def checkEdge(self,src,dst):
        return self.matrix[src][dst]
    
    def print(self) :
        print(" ",end="")
        for node in self.nodes :
            print(node.data,end=" ")
        print()
        for i in range(len(self.matrix)):
            print(self.nodes[i].data,end=" ")
            for j in range(len(self.matrix[i])) :
                print(self.matrix[i][j],end=" ")
            print()
        print()

    def depthSearch(self,src) :
        visited = [False]*len(self.matrix)
        self.depthHelper(src,visited)
    def depthHelper(self,src, visited):
        if visited[src] :
            return
        visited[src] = True
        print(f"{self.nodes[src].data} = visited.")
        for i in range(len(self.matrix[src])) :
            if self.matrix[src][i] == 1 :
                self.depthHelper(i,visited)
                
# Main program
if __name__ == "__main__":
    graph = graph(5)
    graph.addNode(Node('A'))
    graph.addNode(Node('B'))
    graph.addNode(Node('C'))
    graph.addNode(Node('D'))
    graph.addNode(Node('E'))

    graph.addEdge(0, 1)
    graph.addEdge(1, 2)
    graph.addEdge(1, 4)
    graph.addEdge(2, 3)
    graph.addEdge(2, 4)
    graph.addEdge(4, 0)
    graph.addEdge(4, 2)

    graph.print()
    graph.depthSearch(4)