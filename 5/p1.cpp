#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <sstream>

using namespace std;

/*
 * Some thoughts:
 * - im assuming the page ordering rules dont
 *   include impossible ones like 12|11 and 11|12
 *   - but i guess if that was the case it would be
 *     caught by my algorithm anyways
 * - all the ordering rules are 5 char long
 *   - two char for each page number + 1 char spacer
 * - the number of page numbers in each update is odd
 *   - so the middle page number is the n//2th number
 * - to verify each update:
 *   - for each page number in the update:
 *     - i need to check the page numbers before it
 *       to ensure that the current page number was
 *       not meant to come before it
 * - to store the ordering rules, I will have an
 *   unordered_map that maps page numbers to the
 *   page numbers it must come before, which are 
 *   stored in an unordered_set
 *   - i was considering an adjacency list but i
 *     wanted to reduce lookup times 
 */

int main() {
  ifstream input("input5.txt");
  if (!input.is_open()) {
    cout << "could not open file\n";
    return 1;
  }

  unordered_map<int, int[5]> rules;

  bool firstVal;
  string line, val;
  while (getline(input, line)) {
    stringstream ss(line);
    firstVal = false;
    string val;
    while (getline(rule, val, "|")) {
      if (firstVal) {
        
      }
    } 
  }
}
