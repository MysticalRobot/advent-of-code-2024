#include <fstream>
#include <iostream>
#include <array>
#include <queue>
#define N 71
#define BYTES 1024

struct Point { int y, x, steps; };

int main() {
  // create grid to represent memory space
  std::array<std::array<bool, N>, N> grid;
  for (std::array<bool, N>& row : grid) {
    row.fill(true);
  }
  // mark the impact of the first 1024 bytes
  std::ifstream input("input.txt");
  std::string byte;
  int commaIndex;
  for (int i = 0; i != BYTES; ++i) {
    input >> byte;
    commaIndex = byte.find(',');
    grid[std::stoi(byte.substr(commaIndex + 1))][std::stoi(byte.substr(0, commaIndex))] = false;
  }
  input.close();
  // bfs to find the shortest path to the end
  std::queue<Point> q;
  // push and mark starting pos
  grid[0][0] = false;
  q.push(Point{0, 0, 0});
  while (!q.empty()) {
    Point& p = q.front();
    q.pop();
    // output the min number of steps taken to reach the end
    if (p.y == N - 1 && p.x == N - 1) {
      std::cout << "min steps: " << p.steps << '\n';
      break;
    }
    // if not out of bounds or already visited -> visit pos
    if (p.y - 1 != -1 && grid[p.y - 1][p.x]) {
      grid[p.y - 1][p.x] = false;
      q.push(Point{p.y - 1, p.x, p.steps + 1});
    }
    if (p.y + 1 != N && grid[p.y + 1][p.x]) {
      grid[p.y + 1][p.x] = false;
      q.push(Point{p.y + 1, p.x, p.steps + 1});
    }
    if (p.x - 1 != -1 && grid[p.y][p.x - 1]) {
      grid[p.y][p.x - 1] = false;
      q.push(Point{p.y, p.x - 1, p.steps + 1});
    }
    if (p.x + 1 != N && grid[p.y][p.x + 1]) {
      grid[p.y][p.x + 1] = false;
      q.push(Point{p.y, p.x + 1, p.steps + 1});
    }
  }
  return 0;
}