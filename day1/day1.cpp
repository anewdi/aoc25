#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

class solution {
public:
  int rot0s(std::ifstream &file) {
    std::string line;
    int rot = 50;
    int zeros = 0;
    int endZeros = 0;
    bool wasZero = false;

    while (std::getline(file, line)) {
      wasZero = !rot;
      endZeros += !rot;

      int direction = (line.at(0) == 'R') ? 1 : -1;

      int len = line.size() - 1;
      for (int i = 0; i < len; ++i) {
        rot += (line.at(len - i) - '0') * std::pow(10, i) * direction;
      }

      if (rot == 0) {
        zeros++;
        continue;
      }

      int quotient = std::abs(rot / 100) + (rot < 0 && !wasZero);
      rot %= 100;

      if (rot < 0) {
        rot += 100;
      }

      zeros += quotient;
    }

    return zeros;
  }
};

int main() {
  solution a;
  std::ifstream turnsFile("input.txt");
  std::cout << a.rot0s(turnsFile) << std::endl;
  return 0;
}
