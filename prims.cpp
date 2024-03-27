#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
using namespace std;

const char passage = ' ';
const char obstacle = '=';
const int WALL = -1;

class Cell {
public:
    bool visited;
    char type;
    int row, col;

    Cell(int r, int c) : row(r), col(c), visited(false), type(obstacle) {}
};

void generateMaze(int rows, int cols, vector<vector<Cell>>& maze) {
    srand(time(NULL));

    // Initialize all cells as walls
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            maze[i][j].visited = false;
            maze[i][j].type = obstacle;
        }
    }

    // Create a clear path from one side of the maze to the other
    int startX = rand() % (rows - 2) + 1;
    int startY = 0;
    int endX = rand() % (rows - 2) + 1;
    int endY = cols - 1;
    for (int i = min(startX, endX); i <= max(startX, endX); ++i) {
        maze[i][startY].type = passage;
    }

    // Randomized obstacles
    queue<pair<int, int>> frontier;
    frontier.push({startX, startY});
    maze[startX][startY].visited = true;

    while (!frontier.empty()) {
        int x = frontier.front().first;
        int y = frontier.front().second;
        frontier.pop();

        vector<pair<int, int>> neighbors;
        if (x - 1 >= 0) neighbors.push_back({x - 1, y});
        if (x + 1 < rows) neighbors.push_back({x + 1, y});
        if (y - 1 >= 0) neighbors.push_back({x, y - 1});
        if (y + 1 < cols) neighbors.push_back({x, y + 1});

        random_shuffle(neighbors.begin(), neighbors.end());

        for (auto& neighbor : neighbors) {
            int nx = neighbor.first;
            int ny = neighbor.second;
            if (!maze[nx][ny].visited && maze[nx][ny].type == obstacle) {
                maze[nx][ny].visited = true;
                maze[nx][ny].type = (rand() % 2 == 0) ? passage : obstacle;
                frontier.push({nx, ny});
            }
        }
    }
}

vector<vector<char>> mazeToCharVector(const vector<vector<Cell>>& maze) {
    vector<vector<char>> charMaze;
    for (const auto& row : maze) {
        vector<char> charRow;
        for (const auto& cell : row) {
            charRow.push_back(cell.type);
        }
        charMaze.push_back(charRow);
    }
    return charMaze;
}

int main() {
    int rows = 10;
    int cols = 20;

    vector<vector<Cell>> maze(rows, vector<Cell>(cols, Cell(0, 0)));

    generateMaze(rows, cols, maze);

    vector<vector<char>> charMaze = mazeToCharVector(maze);

    for (const auto& row : charMaze) {
        for (const auto& cell : row) {
            cout << cell;
        }
        cout << endl;
    }

    return 0;
}
