class Graph(dict):
    def __init__(self, vertexList, edgeList, isDirected=False):
        for v in vertexList:
            self[v] = set()
        for e in edgeList:
            if isDirected == False:
                self.addEdgeUndirected(e)
            else:
                self.addEdgeDirected(e)

    def addVertex(self, vertex):
        self[vertex] = set()

    def addEdgeUndirected(self, edge):
        # Edge is a tuple of two vertices
        self[edge[0]].add(edge[1])
        self[edge[1]].add(edge[0])

    def addEdgeDirected(self, edge):
        # Edge is a tuple of two vertices
        self[edge[0]].add(edge[1])



# vertices = ['A', 'B', 'C', 'D', 'E']
# for undirected Graph
# edges = [('A', 'B'), ('A', 'E'), ('B', 'C'), ('B', 'D'), ('B', 'E'), ('C', 'D'), ('D', 'E')]
# graph = Graph(vertices, edges, False)
# print(graph['A'])
# print(graph['B'])
# print(graph['C'])
# print(graph['D'])
# print(graph['E'])

# for directed Graph
verticesX = ['A', 'B', 'C', 'D', 'E', 'F']
edgesX = [('A', 'B'),('A', 'D'), ('B', 'E'),('D', 'B'),('C', 'E'),('C', 'F'), ('E', 'D'),('F', 'F')]
graph = Graph(verticesX, edgesX, True)
print(graph['A'])
print(graph['B'])
print(graph['C'])
print(graph['D'])
print(graph['E'])
print(graph['F'])
