#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct Robot{ int y, x, vy, vx; };

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
  int rows = 103, cols = 101;
  // move the robots 100 times
  for (Robot& robot : robots) {
      robot.y += robot.vy * 100;
      robot.x += robot.vx * 100;
  }
  int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
  for (Robot& robot : robots) {
    // put the robots back onto the map
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
    // update the count of the quadrant they lie in
    if (robot.y < rows / 2) {
      if (robot.x < cols / 2) {
        ++q2;  
      } else if (robot.x != cols / 2) {
        ++q1;
      }
    } else if (robot.y != rows / 2) {
      if (robot.x < cols / 2) {
        ++q3;  
      } else if (robot.x != cols / 2) {
        ++q4;
      }
    }
  }
  // AMP rizz contest
  int safetyFactor = q1 * q2 * q3 * q4;
  cout << "kai cenat = " << safetyFactor << endl;
  return 0;
}