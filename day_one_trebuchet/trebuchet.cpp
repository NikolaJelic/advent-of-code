#include <cstddef>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
int main(int argc, char *argv[]) {
  if (!argc) {
    return 1;
  }
  std::string input_filename = argv[1];
  std::vector<int> results{};

  std::ifstream input(input_filename);
  if (!input.is_open()) {
    std::cerr << "Failed to open " << input_filename << std::endl;
  } else {
    std::string line{};
    std::string num_str{};
    while (std::getline(input, line)) {
      int length = line.length();
      if (length > 0) {
        // Another implementation would be to find the positions using
        // find_first and find_last and compare it to an array of digits
        int front = 0;
        int back = length - 1;
        while (!std::isdigit(line.at(front))) {
          front = front < length - 1 ? front + 1 : length - 1;
        }
        while (!std::isdigit(line.at(back))) {
          back = back == 0 ? 0 : back - 1;
        }
        num_str = std::string(1, line.at(front));
        num_str += line.at(back);
        results.push_back(std::stoi(num_str));
      }
    }
  }
  std::size_t sum{};
  for (int i : results) {
    sum += i;
  }
  std::cout << sum;
  return 0;
}
