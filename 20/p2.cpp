#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cmath>

struct Point { int y, x; };

int mostTimeSavable(std::vector<std::vector<char>>& grid, std::vector<std::vector<int>>& times, int y, int x);
void resetGrid(std::vector<std::vector<char>>& grid, std::vector<std::vector<char>>& backupGrid, int y, int x);

int main() {
  std::ifstream input("input.txt");
  std::string s;
  // holds entire input
  std::vector<std::vector<char>> grid;
  // holds times taken to reach each position
  std::vector<std::vector<int>> times;
  // holds each point on the racetrack (everything except '#')
  std::vector<Point> racetrack;
  int startY, startX;
  for (int i = 0; getline(input, s); ++i) {
    grid.push_back(std::vector<char>());
    times.push_back(std::vector<int>());
    for (int j = 0; j != s.size(); ++j) {
      grid[i].push_back(s[j]);
      // -1 time -> no path can reach (i, j) quicker
      if (s[j] == '#') {
        times[i].push_back(-1);
        continue;
      }  
      // find the start pos
      if (s[j] == 'S') {
        startY = i, startX = j;
      }
      // big number -> guaranteed that (i, j) can be reached quicker
      times[i].push_back(INT_MAX);
      racetrack.push_back(Point{i, j});
    }
  }
  // bfs to find the times to reach each point on the racetrack
  Point p = Point{startY, startX};
  int time = 0;
  times[startY][startX] = time;
  while (grid[p.y][p.x] != 'E') {
    // only one path so only need to consider one direction
    if (times[p.y - 1][p.x] > time) {
      --p.y;
    } else if (times[p.y + 1][p.x] > time) {
      ++p.y;
    } else if (times[p.y][p.x - 1] > time) {
      --p.x;
    } else { // times[p.y][p.x + 1] > time
      ++p.x;
    }
    // time to reach next spot = 1 + time to reach current spot
    times[p.y][p.x] = ++time;
  }
  // to mark visited spots and allow for easy resets for bfs
  std::vector<std::vector<char>> backupGrid = grid;
  // consider cheating in each direction for every point
  int mst;
  for (Point& p : racetrack) { // shoutout lexical scope
    if (grid[p.y - 1][p.x] == '#') {
      mst = mostTimeSavable(grid, times, p.y - 1, p.x) - times[p.y][p.x] - 1;
      if (mst > 0) {
        times[p.y - 1][p.x] = fmin(times[p.y - 1][p.x], -1 * mst);
      }
      resetGrid(grid, backupGrid, p.y - 1, p.x);
    }
    if (grid[p.y + 1][p.x] == '#') {
      mst = mostTimeSavable(grid, times, p.y + 1, p.x) - times[p.y][p.x] - 1;
      if (mst > 0) {
        times[p.y + 1][p.x] = fmin(times[p.y + 1][p.x], -1 * mst);
      }
      resetGrid(grid, backupGrid, p.y + 1, p.x);
    }
    if (grid[p.y][p.x - 1] == '#') {
      mst = mostTimeSavable(grid, times, p.y, p.x - 1) - times[p.y][p.x] - 1;
      if (mst > 0) {
        times[p.y][p.x - 1] = fmin(times[p.y][p.x - 1], -1 * mst);
      }
      resetGrid(grid, backupGrid, p.y, p.x - 1);
    }
    if (grid[p.y][p.x + 1] == '#') {
      mst = mostTimeSavable(grid, times, p.y, p.x + 1) - times[p.y][p.x] - 1;
      if (mst > 0) {
        times[p.y][p.x + 1] = fmin(times[p.y][p.x + 1], -1 * mst);
      }
      resetGrid(grid, backupGrid, p.y, p.x + 1);
    }
  }
  // number of cheats that save at least 100 picoseconds
  int n = 0;
  for (int i = 0; i != grid.size(); ++i) {
    for (int j = 0; j != grid[0].size(); ++j) {
      if (grid[i][j] == '#' && abs(times[i][j]) >= 100) {
        ++n;
      }
    }
  }
  // rahhhhh
  std::cout << "i use " << n << " cheats on fortnite" << '\n';
  return 0;
}

int mostTimeSavable(std::vector<std::vector<char>>& grid, std::vector<std::vector<int>>& times, int y, int x) {
  int most = 0;
  std::queue<Point> q;
  q.push(Point{y, x});
  grid[y][x] = '-';
  for (int i = 0; i != 19; ++i) {
    int levelSize = q.size();
    while (levelSize != 0) {
      Point &p = q.front();
      q.pop();
      --levelSize;
      if (p.y - 1 != -1 && grid[p.y - 1][p.x] != '-') {
        most = fmax(most, times[p.y - 1][p.x] - i - 1);
        q.push(Point{p.y - 1, p.x});
        grid[p.y - 1][p.x] = '-';
      }
      if (p.y + 1 != grid.size() && grid[p.y + 1][p.x] != '-') {
        most = fmax(most, times[p.y + 1][p.x] - i - 1);
        q.push(Point{p.y + 1, p.x});
        grid[p.y + 1][p.x] = '-';
      }
      if (p.x - 1 != -1 && grid[p.y][p.x - 1] != '-') {
        most = fmax(most, times[p.y][p.x - 1] - i - 1);
        q.push(Point{p.y, p.x - 1});
        grid[p.y][p.x - 1] = '-';
      }
      if (p.x + 1 != grid[0].size() && grid[p.y][p.x + 1] != '-') {
        most = fmax(most, times[p.y][p.x + 1] - i - 1);
        q.push(Point{p.y, p.x + 1});
        grid[p.y][p.x + 1] = '-';
      }
    }
  }
  return most;
}

void resetGrid(std::vector<std::vector<char>>& grid, std::vector<std::vector<char>>& backupGrid, int y, int x) {
  int yLimit = fmin(grid.size(), y + 20), xLimit = fmin(grid[0].size(), x + 20);
  for (int i = fmax(0, y - 20); i != yLimit; ++i) {
    for (int j = fmax(0, x - 20); j != xLimit; ++j) {
      grid[i][j] = backupGrid[i][j];
    }
  }
  /*
  for (int i = 0; i != grid.size(); ++i) {
    for (int j = 0; j != grid[0].size(); ++j) {
      std::cout << grid[i][j];
    }
    std::cout << '\n';
  }
  std::cout << '\n';
  */
}