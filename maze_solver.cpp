#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

int bfs(std::vector<std::string>& maze, std::vector<char>& path) {
    int n = maze.size(), m = maze[0].size();
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, 0));
    std::vector<std::vector<int>> distance(n, std::vector<int>(m, 0));
    std::vector<std::vector<std::pair<int, int>>> previous(n, std::vector<std::pair<int, int>>(m, {-1, -1}));
    std::queue<std::pair<int, int>> nodes;

    nodes.push({0, 0});
    visited[0][0] = true;

    while(!nodes.empty()) {
        std::pair<int, int> curNode = nodes.front();
        nodes.pop();
        for(int k = 0; k < 4; ++k) {
            int nxtNodeX = curNode.first + dx[k];
            int nxtNodeY = curNode.second + dy[k]; 
            if(0 <= nxtNodeX && nxtNodeX < n && 0 <= nxtNodeY && nxtNodeY < m && !visited[nxtNodeX][nxtNodeY] && maze[nxtNodeX][nxtNodeY] == '.') {
                visited[nxtNodeX][nxtNodeY] = 1;
                distance[nxtNodeX][nxtNodeY] = distance[curNode.first][curNode.second]+1;
                previous[nxtNodeX][nxtNodeY] = {curNode.first, curNode.second};
                nodes.push({nxtNodeX, nxtNodeY});
            }
        }
    }

    if(!visited[n-1][m-1]) {
        return -1;
    }

    std::pair<int, int> curNode = {n-1, m-1};
    while(previous[curNode.first][curNode.second].first > -1) {
        std::pair<int, int> prevNode = previous[curNode.first][curNode.second];
        if(prevNode.first == curNode.first) {
            if(prevNode.second < curNode.second) {
                path.push_back('R');
            } else {
                path.push_back('L');
            }
        } else {
            if(prevNode.first < curNode.first) {
                path.push_back('D');
            } else {
                path.push_back('U');
            }
        }
        curNode = prevNode;
    }
    return distance[n-1][m-1];
}

int main() {
    // returns the shortest path in a maze from cell(1, 1) to cell (n, m).
    // uses bfs.
    // also gives the path which achieves the shortest length.
    // works in O(n*m)
    int n, m; 
    std::cin >> n >> m;
    std::vector<std::string> maze(n);
    for(int i = 0; i < n; ++i) {
        std::cin >> maze[i];
    }
    std::vector<char> path;
    std::cout << bfs(maze, path) << std::endl;
    std::reverse(begin(path), end(path));
    for(int i = 0; i < int(path.size()); ++i) {
        if(i > 0) std::cout << " ";
        std::cout << path[i];
    }
}