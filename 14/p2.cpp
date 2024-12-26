#include <fstream>
#include <iostream>
#include <vector>
#include <unistd.h>
using namespace std;

struct Robot{ int y, x, vy, vx; };

void draw(char* grid, int rows, int cols);

int main() {
  ifstream input("input.txt");
  string s;
  int commaIndex;
  // assemble the mystical robots
  vector<Robot> robots;
  while (input >> s) {
    Robot robot;
    commaIndex = s.find(',');
    robot.y = stoi(s.substr(commaIndex + 1)), robot.x = stoi(s.substr(2, commaIndex));
    input >> s;
    commaIndex = s.find(',');
    robot.vy = stoi(s.substr(commaIndex + 1)), robot.vx = stoi(s.substr(2, commaIndex));
    robots.push_back(robot);
  }
  input.close();
  // create a grid to draw the robots' locations
  int rows = 103, cols = 101;
  char grid[rows * cols];
  for (int i = 0; i != rows; ++i) {
    for (int j = 0; j != cols; ++j) {
      grid[i * cols + j] = ' ';
    }
  }
  // skip first 4999 seconds and the initial state;
  for (Robot& robot : robots) {
    robot.y += robot.vy * 4999;
    robot.x += robot.vx * 4999;
    while (robot.y < 0) {
      robot.y += rows;
    } 
    if (robot.y >= rows) {
      robot.y %= rows;
    }
    while (robot.x < 0) {
      robot.x += cols;
    } 
    if (robot.x >= cols) {
      robot.x %= cols;
    }
    grid[robot.y * cols + robot.x] = 'X';
  }
  // move the robots 5000 more times times
  for (int t = 5000; t != 10000; ++t) {
    for (Robot& robot : robots) {
      grid[robot.y * cols + robot.x] = ' ';
      robot.y += robot.vy;
      robot.x += robot.vx;
      if (robot.y < 0) {
        robot.y += rows;
      } else if (robot.y >= rows) {
        robot.y -= rows;
      }
      if (robot.x < 0) {
        robot.x += cols;
      } else if (robot.x >= cols) {
        robot.x -= cols;
      }
      grid[robot.y * cols + robot.x] = 'X';
    }
    draw(grid, rows, cols);  
    cout << "state after " << t <<  " moves\n";
    usleep(250000);
  }
  /*
  After watching 7584 moves, look what the decided to show up:
  X                                                                            X
            X                   X      XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX      X
                                       X                             X    X
        X             X                X                             X
                                       X                             X
                                       X                             X                         X
                                       X              X              X
                                       X             XXX             X
      X                                X            XXXXX            X        X       X
                      X                            XXXXXXX           X                     X X      X
                                       X          XXXXXXXXX          X
               X    X                  X            XXXXX            X
                                X      X           XXXXXXX           X        X
 X                                     X          XXXXXXXXX          X
                                       X         XXXXXXXXXXX         X                              X
                           X     X     X        XXXXXXXXX XXX        X        X
                        X              X          XXXXXXXXX          X
                                       X         XXXXXXXXXXX         X
         X                             X        XXXXXXXXXXXXX        X
            X   X                      X       XXXXXXXXXXXXXXX       X
                                     X X      XXXXXXXXXXXXXXXXX      X
       X                               X        XXXXXXXXXXXXX        X
                                       X       XXXXXXXXXXXXXXX       X
                                       X      XXXXXXXXXXXXXXXXX      X
                                       X     XXXXXXXXXXXXXXXXXXX     X
                                       X    XXXXXXXXXX XXXXXXXXXX    X
                                       X             XXX             X      X
                                       X             XXX             X
                      X                X             XXX             X                X
                                       X                             X
                                       X                             X
                                       X                             X                           X
                                       X                             X
                    X                  XXX XXXX XXXXXXXXXXXXXXXXXXXXXX
                                                                              X
  */
  return 0;
}

// draws grid
void draw(char* grid, int rows, int cols) {
  for (int i = 0; i != rows; ++i) {
    for (int j = 0; j != cols; ++j) {
      cout << grid[i * cols + j];
    }
    cout << endl;
  }
}