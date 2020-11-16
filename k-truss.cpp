#include <bits/stdint-uintn.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>

void print_usage(const char *name);

int main(int argc, char *argv[]) {
  using std::string;

  if (3 != argc || 0 != strcmp("-f", argv[1])) {
    print_usage(argv[0]);
    std::cout << argc << std::endl;
    return -1;
  }
  //if (strcmp("-f", argv[1])) {
  //  print_usage(argv[0]);
  //  std::cout << "!!!" << std::endl;
  //  return -2;
  //}

  std::ifstream inFile(argv[2]);
  string str;
  while (std::getline(inFile, str)) {
    std::istringstream iss(str);

    std::vector<string> uvs;
    std::copy(std::istream_iterator<string>(iss),
        std::istream_iterator<string>(),
        std::back_inserter(uvs));

    uint32_t node_a = static_cast<uint32_t>(std::stoul(uvs[0]));
    uint32_t node_b = static_cast<uint32_t>(std::stoul(uvs[1]));

    std::cout << uvs[0] << ", " << uvs[1] << std::endl;
    std::cout << node_a << "  " << node_b << std::endl;

  }

  return 0;
}

void print_usage(const char *name) {
  std::cout << "Usage: " << name << " -f <FILENAME>" << std::endl;
}
