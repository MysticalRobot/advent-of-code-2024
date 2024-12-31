#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

long countSetsOfThreeWithT(std::vector<std::string>& set, int i, int size, bool containsT);

int main() {
  std::ifstream input("input.txt");
  std::string edge;
  std::unordered_map<std::string, std::vector<std::string>> connections;
  while (input >> edge) {
    std::string a = edge.substr(0, 2), b = edge.substr(3);
    const auto& aIt = connections.find(a), bIt = connections.find(b);
    if (aIt == connections.end() && bIt == connections.end()) {
      connections[a] = std::vector<std::string>{a, b};
    } else if (aIt != connections.end() && bIt != connections.end()) {
      connections[a].push_back(b);
      /*
      std::vector<std::string>& smaller = connections[a].size() < connections[b].size() ? connections[a] : connections[b];
      std::vector<std::string>& larger = connections[a].size() < connections[b].size() ? connections[b] : connections[a];
      while (!smaller.empty()) {
        larger.push_back(smaller.back());
        smaller.pop_back();
      }
      */
    } else if (aIt != connections.end()) {
      connections[a].push_back(b);
    } else { // bIt != connections.end()
      connections[b].push_back(a);
    }
  }
  long containT = 0;
  for (auto& pair : connections) { 
    containT += countSetsOfThreeWithT(pair.second, 0, 0, false);
  }
  std::cout << containT << '\n';
  return 0;
}

long countSetsOfThreeWithT(std::vector<std::string>& set, int i, int size, bool containsT) {
  if (size == 3) {
      return containsT;
  } else if (i == set.size()) {
    return 0;
  }
  long skipResult = countSetsOfThreeWithT(set, i + 1, size, containsT); 
  if (set[i][0] != 't') {
    return skipResult + countSetsOfThreeWithT(set, i + 1, size + 1, containsT); 
  }
  return skipResult + countSetsOfThreeWithT(set, i + 1, size + 1, true); 
}