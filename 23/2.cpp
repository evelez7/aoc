#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::array<int, 3> config = {12, 13, 14}; // rgb

std::string &eliminate_whitespace(std::string &x) {
  if (x.at(0) == ' ') {
    return x.erase(0, 1);
  }
  return x;
}

int main(int argc, char **argv) {
  std::ifstream input("./2.txt");
  if (input.is_open()) {
    std::string line;
    int sum = 0;
    int sum_power = 0;
    while (std::getline(input, line)) {
      bool possible = true;
      auto colonPos = line.find(":");
      // now we just have the rounds of rgb
      std::string data = line.substr(colonPos + 2, line.size());
      std::string id_reverse;
      std::string id_str = line.substr(0, colonPos);
      for (int i = colonPos - 1;; --i) {
        // construct the id
        if (std::isdigit(id_str.at(i))) {
          id_reverse.push_back(id_str.at(i));
        } else {
          break;
        }
      }
      std::string id(id_reverse.rbegin(), id_reverse.rend());

      std::string round;
      std::stringstream data_ss(data);
      // now we have the individual rounds
      int red = 1, green = 1, blue = 1;
      while (std::getline(data_ss, round, ';')) {
        std::string color_pair;
        std::stringstream round_ss(round);
        while (std::getline(round_ss, color_pair, ',')) {
          eliminate_whitespace(color_pair);
          // now we have the individual colors
          size_t pos;
          int color_quant =
              std::stoi(color_pair.substr(0, pos = color_pair.find(" ")));

          std::string color_name = color_pair.substr(pos, color_pair.length());
          color_name = eliminate_whitespace(color_name);

          if (color_name == "red") {
            if (color_quant > red) {
              red = color_quant;
            }
          } else if (color_name == "green") {
            if (color_quant > green) {
              green = color_quant;
            }
          } else if (color_name == "blue") {
            if (color_quant > blue) {
              blue = color_quant;
            }
          }

          // if ((color_name == "red" && color_quant > config[0]) ||
          //     (color_name == "green" && color_quant > config[1]) ||
          //     (color_name == "blue" && color_quant > config[2])) {
          //   possible = false;
          //   break;
          // }
        }

        // if (!possible)
        //   break;
      }

      sum_power += red * green * blue;
      if (possible)
        sum += std::stoi(id);
    }
    std::cout << sum << '\n';
    std::cout << sum_power << '\n';
  }
  return 0;
}
