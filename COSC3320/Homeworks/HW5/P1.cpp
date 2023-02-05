#include <iostream>
#include <stdlib.h>
#include <vector>

void dfs(int v, int dest, std::vector<std::pair<int,int>> adj[], bool visited[], int current, int &maxDistance) {
    if(v == dest) {
        if(maxDistance == -1 || (maxDistance < current && maxDistance != -1)) {
            maxDistance = current;
        }
        return;
    }

    visited[v] = true;
    for(auto it : adj[v]) {
        if(visited[it.first] == false) {
            dfs(it.first, dest, adj, visited, current + it.second, maxDistance);
        }
    }
    visited[v] = false;
}

int main() {
    int n,m;
    std::cin>>n>>m;
    int begNode, endNode;
    std::cin>>begNode>>endNode;
    std::vector<std::pair<int,int>> adj[n];
    
    for(int i=0;i<m;i++){
        int u,v,w;
        std::cin>>u>>v>>w;
        adj[u].push_back(std::make_pair(v,w));
    }
    
    int maxDistance = -1 ;
    bool visited[n] = {false};
    dfs(begNode, endNode, adj, visited, 0, maxDistance);
    std::cout<<maxDistance;

    return 0;
}