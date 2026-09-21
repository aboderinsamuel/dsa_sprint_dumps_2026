//leetcode 286 : walls and gates
#include <vector>
#include <queue>
#include <numeric>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class Solution{
public:
    void islandAndTreasure(vector<vector<int>>& grid){
        if(grid.empty() || grid[0].empty()) return;
        int rows = grid.size();
        int cols = grid[0].size();
        queue<pair<int, int>> q; //the reason for the queue is to perform a breadth-first search (BFS) starting from all the gates (cells with value 0) simultaneously. By using a queue, we can explore all the adjacent cells level by level, ensuring that we find the shortest distance to the nearest gate for each empty room (cells with value INT_MAX).
        for(int r=0; r<rows; r++){
            for(int c=0; c<cols; c++){
                if(grid[r][c] == 0){
                    q.push({r, c});
                }
            }
        }
        while(!q.empty()){
            auto [r, c] = q.front();
            q.pop();
            // Process the current cell
            // Check the four adjacent cells (up, down, left, right)
            vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
            for(auto [dr, dc] : directions){
                int newRow = r + dr;
                int newCol = c + dc;
                // Check if the new cell is within bounds and is an empty room
                if(newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && grid[newRow][newCol] == INT_MAX){
                    grid[newRow][newCol] = grid[r][c] + 1; // Update the distance to the nearest gate
                    q.push({newRow, newCol}); // Add the new cell to the queue for further processing
                }
            }
        }

    }
};

class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        //condition 1 : A tree must have exactly n-1 edges
        if(edges.size() != n-1) return false;

        //build adjacency list from undirected graph
        vector<vector<int>> adj(n);
        for(auto& edge : edges){
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        unordered_set<int> visited;
        queue<int> q;

        q.push(0);
        visited.insert(0);

        while(!q.empty()){
            int node = q.front();
            q.pop();

            for(int neighbor : adj[node]){
                //if neighbor is not visited, mark it and queue it up
                if(!visited.count(neighbor)){
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        //condition 2 : the graph must be fully connected
        return visited.size() == n;
    }
};

class Solution2{
private:
    int find(vector<int>& parent, int x){
        if(parent[x] == x) return x;
        return parent[x] = find(parent, parent[x]);
    }
public:
    int countComponents(int n, vector<vector<int>>& edges){
        vector<int> parent(n);
        int components = n; // Initially, each node is its own component
        iota(parent.begin(), parent.end(), 0); // Initialize each node's parent to itself
        for(int i=0; i<n; i++) parent[i] = i;

        for(auto& edge : edges){
            int root1 = find(parent, edge[0]);
            int root2 = find(parent, edge[1]);
            if(root1 != root2){
                parent[root1] = root2;
                components--;
            }
        }
        return components;

        
    }
};

class Solution {
private:
    int find(vector<int>& parent, int x){
        if(parent[x] == x) return x;
        return parent[x] = find(parent, parent[x]);
    }
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<int> parent(n+1);
        iota(parent.begin(), parent.end(), 0);
        for(auto& edge : edges){
            int rootX = find(parent, edge[0]);
            int rootY = find(parent, edge[1]);
            if(rootX == rootY){
                return edge;
            }
            parent[rootX] = rootY;
        }
        return {};
    }
};
