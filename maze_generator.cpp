#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};

struct Wall {
    std::pair<int, int> neighbor1, neighbor2;
    int direction;
};

struct DisjointSetUnion {  
    // DSU data structure.
    // enables us to merge two sets and check whether an element belongs to a set in O(alpha(N))
    // Uses path compression and small to large heuristic

    std::vector<int> parent;

    void initialize(int N) {
        parent = std::vector<int>(N, -1);
    }

    int find(int x){
        return parent[x] < 0 ? x : parent[x] = find(parent[x]);
    }

    bool unite(int x, int y){
        x = find(x), y = find(y);
        if(x == y) return 0;
        if(parent[x] > parent[y]) {
            std::swap(x, y);
        }
        parent[x] += parent[y];
        parent[y] = x;
        return 1;
    }
};

int main() {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    int height, width;
    std::cin >> height >> width;

    // generates a 2*height-1 X 2*width-1 maze.

    std::vector<Wall> walls;

    // for each pair of cells, I establish the wall which "disconnects" them
    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            for(int k = 0; k < 4; ++k) {
                if(0 <= i+dx[k] && i+dx[k] < height && 0 <= j+dy[k] && j+dy[k] < width) {
                    walls.push_back({{i, j}, {i+dx[k], j+dy[k]}, k});
                }
            }
        }
    }

    // Randomized Kruskals algorithms
    // at each step, we choose a wall randomly.
    // we then check whether the two cells disconnected by this wall are already connected.
    // if this is not the case, we connect them, and erase this wall.
    // eventually, we will be left with only one set of connected cells, and some walls will remain "alive".
    // this set of walls defines our maze.
    // Note: for convenience, we map each cell (x, y) to the number (width*x+y)
    // the vector alive states whether a wall is not erased i.e. remains in the final maze
    DisjointSetUnion DSU;
    DSU.initialize(width*height+width);
    std::vector<bool> alive(int(walls.size()), 1);
    std::shuffle(begin(walls), end(walls), rng);

    for(int i = 0; i < int(walls.size()); ++i) {
        std::pair<int, int> nei1 = walls[i].neighbor1;
        std::pair<int, int> nei2 = walls[i].neighbor2;
        int valNei1 = width * nei1.first + nei1.second;
        int valNei2 = width * nei2.first + nei2.second;

        if(DSU.unite(valNei1, valNei2)) {
            alive[i] = 0;
        }
    }

    // the maze is represented with a char matrix.
    // we double the height and weight to account for the walls between cells.
    std::vector<std::vector<char>> maze(2*height, std::vector<char>(2*width, '#'));
    
    for(int i = 0; i < int(walls.size()); ++i) {
        std::pair<int, int> nei1 = walls[i].neighbor1;
        std::pair<int, int> nei2 = walls[i].neighbor2;
        int dir = walls[i].direction;
        maze[2*nei1.first][2*nei1.second] = '.';
        maze[2*nei2.first][2*nei2.second] = '.';
        if(!alive[i]) {
            if(dir == 0) {
                maze[2*nei1.first+1][2*nei1.second] = '.';
            } else if(dir == 1) {
                maze[2*nei1.first-1][2*nei1.second] = '.';
            } else if(dir == 2) {
                maze[2*nei1.first][2*nei1.second+1] = '.';
            } else {
                maze[2*nei1.first][2*nei1.second-1] = '.';
            }
        }
    }

    for(int i = 0; i < 2*height-1; ++i) {
        for(int j = 0; j < 2*width-1; ++j) {
            std::cout << maze[i][j];
        }
        std::cout << std::endl;
    }
}
