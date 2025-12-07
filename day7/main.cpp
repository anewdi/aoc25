#include <fstream>
#include <iostream>
#include <vector>

class Solution {
public:
  int one(std::ifstream &in) {
    std::string inputstring;
    std::getline(in, inputstring);

    std::vector<int> prev;
    for (int i = 0, u = inputstring.length(); i < u; ++i) {
      prev.push_back(inputstring[i] == 'S');
    }

    int count = 0;
    while (std::getline(in, inputstring)) {
      if (inputstring[0] == '^' && prev[0]) {
        count++;
        prev[0] = 0;
        prev[1] = 1;
      }
      for (int i = 1, u = inputstring.length() - 1; i < u; ++i) {
        if (inputstring[i] == '^' && prev[i]) {
          count++;
          prev[i - 1] = 1;
          prev[i] = 0;
          prev[i + 1] = 1;
        }
      }
      if (inputstring.back() == '^' && prev.back()) {
        count++;
        prev.back() = 0;
        prev[prev.size() - 2] = 1;
      }
    }

    in.clear();
    in.seekg(0);
    return count;
  }
  long two(std::ifstream &in) {
    std::string inputstring;
    std::getline(in, inputstring);

    std::vector<long> prev;
    for (int i = 0, u = inputstring.length(); i < u; ++i) {
      prev.push_back(inputstring[i] == 'S');
    }

    while (std::getline(in, inputstring)) {
      if (inputstring[0] == '^' && prev[0]) {
        prev[1] += prev[0];
        prev[0] = 0;
      }
      for (int i = 1, u = inputstring.length() - 1; i < u; ++i) {
        if (inputstring[i] == '^' && prev[i]) {
          prev[i - 1] += prev[i];
          prev[i + 1] += prev[i];
          prev[i] = 0;
        }
      }
      if (inputstring.back() == '^' && prev.back()) {
        prev[prev.size() - 2] += prev.back();
        prev.back() = 0;
      }
    }

    long sum = 0;
    for (auto num : prev) {
      sum += num;
    }

    in.clear();
    in.seekg(0);
    return sum;
  }
};

int main() {
  Solution s;
  std::ifstream inFile("./input.txt");
  std::cout << s.one(inFile) << std::endl;
  std::cout << s.two(inFile) << std::endl;
  return 0;
}
