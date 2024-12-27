#include <fstream>
#include <iostream>
#include <array>
#include <queue>
#define N 71
#define BYTES 3450

struct Point { int y, x; };

void setGrid(std::array<std::array<bool, N>, N>& grid, std::array<Point, BYTES>& bytes, int fallenBytes);
bool canFindPath(std::array<std::array<bool, N>, N>& grid);

int main() {
  // create grid to represent memory space
  std::array<std::array<bool, N>, N> grid;
  // gather the positions of all the bytes
  std::ifstream input("input.txt");
  std::string byte;
  std::array<Point, BYTES> bytes;
  int commaIndex;
  for (int i = 0; i != BYTES; ++i) {
    input >> byte;
    commaIndex = byte.find(',');
    bytes[i] = Point{std::stoi(byte.substr(commaIndex + 1)), std::stoi(byte.substr(0, commaIndex))};
  }
  input.close();
  // starting after the largest known safe number of bytes (1024),
  // incrementally drop bytes till the squad is unable to the end
  for (int i = 12; i != BYTES; ++i) {
    setGrid(grid, bytes, i);
    if (!canFindPath(grid)) {
      // identify the escape blocking byte
      Point& problemByte = bytes[i - 1];
      // had to flip ts :((((( (i don't mean typescript)
      std::cout << problemByte.x << ',' << problemByte.y << '\n';
      break;
    }
  }
  return 0;
}

void setGrid(std::array<std::array<bool, N>, N>& grid, std::array<Point, BYTES>& bytes, int fallenBytes) {
  // fill the grid with true (meaning unvisited and unblocked)
  for (std::array<bool, N>& row : grid) {
    row.fill(true);
  }
  // drop the bytes!
  for (int i = 0; i != fallenBytes; ++i) {
    Point& byte = bytes[i];
    grid[byte.y][byte.x] = false;
  }
}

bool canFindPath(std::array<std::array<bool, N>, N>& grid) {
  // bfs to find if a path to the end exists
  std::queue<Point> q;
  // push and mark starting pos
  grid[0][0] = false;
  q.push(Point{0, 0});
  while (!q.empty()) {
    Point& p = q.front();
    q.pop();
    // yay! you can reach the end
    if (p.y == N - 1 && p.x == N - 1) {
      return true;
    }
    // if not out of bounds or already visited -> visit pos
    if (p.y - 1 != -1 && grid[p.y - 1][p.x]) {
      grid[p.y - 1][p.x] = false;
      q.push(Point{p.y - 1, p.x});
    }
    if (p.y + 1 != N && grid[p.y + 1][p.x]) {
      grid[p.y + 1][p.x] = false;
      q.push(Point{p.y + 1, p.x});
    }
    if (p.x - 1 != -1 && grid[p.y][p.x - 1]) {
      grid[p.y][p.x - 1] = false;
      q.push(Point{p.y, p.x - 1});
    }
    if (p.x + 1 != N && grid[p.y][p.x + 1]) {
      grid[p.y][p.x + 1] = false;
      q.push(Point{p.y, p.x + 1});
    }
  }
  // tragic... no way out for you bud
  return false;
}