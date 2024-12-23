#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

int main() {
  // vector for each list (later heapified)
  vector <int> heap1, heap2;
  int num1, num2;
  
  // open input file
  ifstream indata;
  indata.open("input.txt");
  if (!indata) {
    cerr << "Error: file could not be opened" << endl;
    exit(1);
  }
  // push each input number to its respective vector
  while (1) {
    indata >> num1;
    indata >> num2;
    // had to do this because I ended up adding the 
    // numbers on the last line of the input twice    
    if (!indata.eof()) {
      heap1.push_back(num1);
      heap2.push_back(num2);
    } else {
      break;
    }
  }
  // close the file and check if every input was received
  indata.close();
  cout << "End-of-file reached.." << endl;
  cout << "Size of heap1 = " << heap1.size();
  cout << ", heap2 = " << heap2.size() << endl;

  unordered_map<int, int> map;
  int similarityScore = 0;
  // count the occurences of all the numbers in heap2
  for (int i : heap2) {
    if (map.find(i) == map.end()) {
      map[i] = 1;
    } else {
      map.at(i) += 1;
    }
  }
  // find the sum of each number in heap1 multiplied
  // by the number of its occurences in heap2
  for (int i : heap1) {
    if (map.find(i) != map.end()) {
      similarityScore += map.at(i) * i;
    }
  }
  // output the resullt
  cout << "Similarity Score is " << similarityScore << endl;

  int totalDistance = 0;
  // heapify both the vectors
  make_heap(heap1.begin(), heap1.end());
  make_heap(heap2.begin(), heap2.end());
  // compute the sum of the differenes between the
  // ith largest numbers of each heap
  while (!heap1.empty()) {
    pop_heap(heap1.begin(), heap1.end());
    pop_heap(heap2.begin(), heap2.end());
    totalDistance += abs(heap1.back() - heap2.back());
    heap1.pop_back();
    heap2.pop_back();
  }
  // output the result
  cout << "Total is " << totalDistance << endl;
  return 0;
}
