#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> lines;
std::vector<int> nums;

int construct_num(int i, int j);

int determine_nums(int i, int j) {
  if ((i >= 0 && i < lines.size()) && (j >= 0 && j < lines.at(i).length()) &&
      std::isdigit(lines.at(i).at(j))) {
    return construct_num(i, j);
  }
  return -1;
}

int construct_num(int i, int j) {
  std::string current_line = lines.at(i);
  std::string num;
  char c = current_line.at(j);
  int start, end;
  int x = j;
  for (; x >= 0; --x) {
    if (x == -1 || !std::isdigit(current_line.at(x))) {
      break;
    }
  }
  start = x + 1;

  x = j;
  for (; x <= current_line.length(); ++x) {
    if (x >= current_line.length() || !std::isdigit(current_line.at(x))) {
      break;
    }
  }
  end = x - 1;

  for (int x = start; x < end + 1; ++x) {
    num.push_back(current_line.at(x));
  }
  if (num.length() == 0)
    std::cout << "num length is 0\n";
  nums.push_back(std::stoi(num));

  std::string new_line = current_line;
  for (int x = start; x <= end; ++x)
    new_line.at(x) = '.';
  lines.at(i) = new_line;
  return std::stoi(num);
}

int main() {
  std::ifstream file("./3.txt");
  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }

  int sum_gear = 0;
  for (int i = 0; i < lines.size(); ++i) {
    line = lines.at(i);
    int parts, parts_ratio;
    for (int j = 0; j < line.length(); ++j) {
      char current_char = line.at(j);
      parts = 0;
      parts_ratio = 1;
      for (int x = -1; x < 2; ++x) {
        for (int y = -1; y < 2; ++y) {
          if (current_char != '.' && !isdigit(current_char)) {
            auto part = determine_nums(i + x, j + y);
            if (current_char == '*' && part >= 0 && parts < 2) {
              ++parts;
              parts_ratio *= part;
            }
          }
        }
      }
      if (parts == 2) {
        sum_gear += parts_ratio;
      }
    }
  }

  int sum = 0;
  for (int num : nums)
    sum += num;
  std::cout << sum << '\n';
  std::cout << sum_gear << '\n';

  return 0;
}
