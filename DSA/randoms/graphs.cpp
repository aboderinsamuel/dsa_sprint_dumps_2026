//leetcode 286 : walls and gates
#include <vector>
#include <queue>
#include <numeric>
#include <unordered_set>
#include <unordered_map>
#include <string>
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
//redundant connection
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
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        queue<string> q;
        if(!wordSet.count(endWord)) return 0;
        q.push(beginWord);

        int changes = 1;
        while(!q.empty()){
            int size = q.size();
            for(int i=0; i<size; i++){
                string word = q.front();
                q.pop();
                if(word == endWord) return changes;
                for(int pos = 0; pos<word.size(); pos++){
                    char originalChar = word[pos];
                    for(char c='a'; c<='z'; c++){
                        if(c == originalChar) continue;
                        word[pos] = c;
                        if(wordSet.count(word)){
                            q.push(word);
                            wordSet.erase(word);
                        }
                    }
                    word[pos] = originalChar;
                }
            }
            changes++;
        }
        return 0;
    }
};

//leetcode 126 : word ladder II
//similar solution to first one above:

class Solution {
private:
    void dfs(const string& word,
             const string& beginWord,
             unordered_map<string, vector<string>>& parents,
             vector<string>& path,
             vector<vector<string>>& result) {

        if (word == beginWord) {
            result.push_back(vector<string>(path.rbegin(), path.rend()));
            return;
        }

        for (const string& parent : parents[word]) {
            path.push_back(parent);
            dfs(parent, beginWord, parents, path, result);
            path.pop_back();
        }
    }

public:
    vector<vector<string>> findLadders(string beginWord,
                                       string endWord,
                                       vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        vector<vector<string>> result;

        if (!wordSet.count(endWord))
            return result;

        unordered_map<string, vector<string>> parents;

        queue<string> q;
        q.push(beginWord);

        unordered_set<string> visited;
        visited.insert(beginWord);

        bool found = false;

        while (!q.empty() && !found) {
            int levelSize = q.size();
            unordered_set<string> levelVisited;

            for (int i = 0; i < levelSize; i++) {
                string word = q.front();
                q.pop();
                string originalWord = word;

                for (int pos = 0; pos < word.size(); pos++) {
                    char originalChar = word[pos];

                    for (char c = 'a'; c <= 'z'; c++) {
                        if (c == originalChar) continue;
                        word[pos] = c;

                        if (!wordSet.count(word)) continue;
                        if (visited.count(word)) continue;

                        parents[word].push_back(originalWord);   // CHANGED: child -> parent

                        if (!levelVisited.count(word)) {
                            levelVisited.insert(word);
                            q.push(word);
                        }

                        if (word == endWord) found = true;
                    }
                    word[pos] = originalChar;
                }
            }

            for (const string& w : levelVisited)
                visited.insert(w);
        }

        if (!found) return result;

        vector<string> path = {endWord};                 // CHANGED: start at the end
        dfs(endWord, beginWord, parents, path, result);  // CHANGED: walk backwards
        return result;
    }
};

// Let N = number of words, L = word length, 
// E = number of edges in the graph, P = number of shortest paths, 
// S = length of a shortest path.
// Time: O(N · 26 · L²) for BFS + O(P · S) for DFS
// Space: O(N · L + E · L + P · S)

//leetcode 778 : swim in rising water
class Solution {
public:
vector<pair<int, int>> directions = {{-1,0}, {1,0}, {0,1}, {0,-1}};
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> minTime(n, vector<int>(n, INT_MAX));
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;
        minTime[0][0] = grid[0][0];
        pq.push({grid[0][0], {0,0}});

        while(!pq.empty()){
            auto [time, pos] = pq.top();
            pq.pop();

            int row = pos.first;
            int col = pos.second;
            if(row == n-1 && col == n-1) return time;
            if(time > minTime[row][col]) continue;
            for(auto [dr, dc] : directions){
                int nr = row + dr;
                int nc = col + dc;

                if(nr < 0 || nr >=n || nc < 0 || nc >= n) continue;
                int newTime = max(time, grid[nr][nc]);
                if(newTime < minTime[nr][nc]){
                    minTime[nr][nc] = newTime;
                    pq.push({newTime, {nr, nc}});
                }
            }
        }
        return -1;
    }
};

//leetcodde 1631 : path with minimum effort
class Solution {
public:
    vector<pair<int, int>> directions = {{0,1},{0,-1},{1,0},{-1,0}};
    int minimumEffortPath(vector<vector<int>>& heights) {
        int rows = heights.size();
        int cols = heights[0].size();
        vector<vector<int>> effort(rows, vector<int>(cols, INT_MAX));
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        pq.push({0,0,0});
        effort[0][0] = 0;

        while(!pq.empty()){
            auto current = pq.top();
            pq.pop();

            int currentEffort = current[0];
            int row = current[1];
            int col = current[2];

            if(currentEffort > effort[row][col]) continue;
            if(row == rows - 1 && col == cols-1) return currentEffort;
            for(auto [dr, dc] : directions){
                int newRow = row + dr;
                int newCol = col + dc;
                if(newCol < 0 || newCol >= cols || newRow < 0 || newRow >= rows) continue;
                int jump = abs(heights[row][col] - heights[newRow][newCol]) ;
                int newEffort = max(jump, currentEffort);
                if(newEffort < effort[newRow][newCol]){
                    effort[newRow][newCol] = newEffort;
                    pq.push({newEffort, newRow, newCol});
                }
            }
        }
        return 0;
        
    }
};
