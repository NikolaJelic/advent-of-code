#include <cassert>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

static const std::unordered_map<std::string, int> digit_map = {
    {"zero", '0'}, {"one", '1'}, {"two", '2'},   {"three", '3'}, {"four", '4'},
    {"five", '5'}, {"six", '6'}, {"seven", '7'}, {"eight", '8'}, {"nine", '9'},
    {"1", '1'},    {"2", '2'},   {"3", '3'},     {"4", '4'},     {"5", '5'},
    {"6", '6'},    {"7", '7'},   {"8", '8'},     {"9", '9'}};

int extract_numbers(std::string input) {
  assert(input.length() > 0);
  int ret{};
  int pos{};
  int first_pos = input.length();
  int last_pos{};
  int length_first{};
  int length_last{};
  std::string num_str{};

  for (auto const& [key, value] : digit_map) {
    pos = input.find(key);
    if (pos != std::string::npos && pos <= first_pos) {
      first_pos = pos;
      length_first = key.length();
    }
    pos = input.rfind(key);
    if (pos != std::string::npos && pos >= last_pos) {
      last_pos = pos;
      length_last = key.length();
    }
  }

  std::string first = input.substr(first_pos, length_first);
  std::string last = input.substr(last_pos, length_last);

  auto f_it = digit_map.find(first);
  auto l_it = digit_map.find(last);
  char first_digit{};
  char last_digit{};
  if (f_it != digit_map.end() && l_it != digit_map.end()) {
    first_digit = f_it->second;
    last_digit = l_it->second;
    num_str = std::string(1, first_digit);
    num_str += last_digit;
    ret = std::stoi(num_str);
  } else {
    std::cout << "PROBLEM: " << input << '\n';
  }

  return ret;
}

int main(int argc, char* argv[]) {
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
        results.push_back(extract_numbers(line));
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
