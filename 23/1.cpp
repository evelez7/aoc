#include <algorithm>
#include <array>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

std::array<std::string, 9> numbers{"one", "two",   "three", "four", "five",
                                   "six", "seven", "eight", "nine"};

int main(int argc, char **argv) {
  std::ifstream input;
  input.open("./1.txt");
  if (input.is_open()) {
    std::string line;
    int sum = 0;
    while (std::getline(input, line)) {
      char first = '\0';
      char second = '\0';
      for (int i = 0; i < line.length(); i++) {
        char current_char = line.at(i);

        if (std::isdigit(current_char)) {
          if (first == '\0')
            first = current_char;
          else
            second = current_char;
        } else if (std::isalpha(current_char)) {
          std::string potential_number{current_char};
          for (int j = i + 1;
               j < line.length() && potential_number.length() < 5; j++) {
            if (std::isalpha(line.at(j))) {
              potential_number.push_back(line.at(j));
              if (potential_number.length() > 2)
                for (int k = 0; k < numbers.size(); k++) {
                  if (numbers.at(k) == potential_number && first == '\0') {
                    first = '0' + (k + 1);
                    break;
                  } else if (numbers.at(k) == potential_number) {
                    second = '0' + (k + 1);
                    break;
                  }
                }
            } else {
              break;
            }
          }
        }
      }
      if (second == '\0')
        second = first;
      sum += std::stoi(std::string{first, second});
    }
    input.close();
    std::cout << sum << '\n';
    return 0;
  } else {
    return -1;
  }
}
