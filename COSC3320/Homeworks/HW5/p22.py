from collections import defaultdict
 
class Graph:
    def __init__(self,vertices):
        self.V = vertices
        self.graph = defaultdict(list)

    def addEdge(self,u,v,w):
        self.graph[u].append((v,w))
 
    def topologicalSortUtil(self,v,visited,stack):
        visited[v] = True
        if v in self.graph.keys():
            for node,weight in self.graph[v]:
                if visited[node] == False:
                    self.topologicalSortUtil(node,visited,stack)
        stack.append(v)

    def shortestPath(self, s, d):
        visited = [False]*self.V
        stack =[]
        for i in range(self.V):
            if visited[i] == False:
                self.topologicalSortUtil(s,visited,stack)

        dist = [-1] * (self.V)
        dist[s] = 0
        while stack:
            i = stack.pop()
            for node,weight in self.graph[i]:
                if dist[node] < dist[i] + weight:
                    dist[node] = dist[i] + weight

        print("%d" %dist[d])
 
 
numVertex, numEdges = input().split()
begV, endV = input().split()
numVertex, numEdges, begV, endV = int(numVertex), int(numEdges), int(begV), int(endV)
g = Graph(numVertex)
adj = [[] for i in range(numVertex)]
for i in range(numEdges):
    currV, destV, weight = input().split()
    currV, destV, weight = int(currV), int(destV), int(weight)
    g.addEdge(currV, destV, weight)

g.shortestPath(begV, endV)