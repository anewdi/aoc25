#include <fstream>
#include <iostream>
#include <vector>

class Solution {
public:
  long one(std::ifstream &in) {
    std::vector<std::vector<int>> lines;

    std::string inputString;
    while (std::getline(in, inputString)) {
      if (inputString[0] == '*' || inputString[0] == '+') {
        break;
      }

      std::vector<int> line;
      int num = 0;
      for (auto c : inputString) {
        if (c == ' ') {
          if (num) {
            line.push_back(num);
            num = 0;
          }
          continue;
        }
        num *= 10;
        num += c - '0';
      }

      if (num) {
        line.push_back(num);
      }

      lines.push_back(line);
    }

    long sum = 0;
    int column = 0;
    for (auto c : inputString) {
      if (c == ' ') {
        continue;
      }

      if (c == '*') {
        long tempSum = 1;
        for (auto line : lines) {
          tempSum *= line[column];
        }
        sum += tempSum;
      } else {
        for (auto line : lines) {
          sum += line[column];
        }
      }

      column++;
    }

    in.clear();
    in.seekg(0);

    return sum;
  }

  long two(std::ifstream &in) {
    std::vector<std::string> lines;

    std::string inputString;
    while (std::getline(in, inputString)) {
      lines.push_back(inputString);
    }

    std::string operators = lines[lines.size() - 1];
    lines.pop_back();

    long sum = 0;
    bool mul = 0;
    long tempSum = 0;

    for (int i = 0, u = operators.length(); i < u; ++i) {
      if (operators[i] != ' ') {
        sum += tempSum;
        mul = operators[i] == '*';
        tempSum = mul;
      }

      int num = 0;
      for (auto line : lines) {
        if (line[i] != ' ') {
          num *= 10;
          num += line[i] - '0';
        }
      }
      if (num) {
        tempSum = mul ? tempSum * num : tempSum + num;
      }
    }
    sum += tempSum;

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
