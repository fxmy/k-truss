#include "graph.h"
#include <algorithm>
#include <bits/stdint-uintn.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string.h>
#include <string>
#include <vector>

Graph ggg;

void print_usage(const char *name);

int main(int argc, char *argv[]) {
  using std::string;

  if (3 != argc || 0 != strcmp("-f", argv[1])) {
    print_usage(argv[0]);
    std::cout << argc << std::endl;
    return -1;
  }
  // if (strcmp("-f", argv[1])) {
  //  print_usage(argv[0]);
  //  std::cout << "!!!" << std::endl;
  //  return -2;
  //}

  std::ifstream inFile(argv[2]);
  string str;
  uint32_t line_number = 0;
  while (std::getline(inFile, str)) {
    ++line_number;
    std::istringstream iss(str);

    std::vector<string> uvs;
    std::copy(std::istream_iterator<string>(iss),
              std::istream_iterator<string>(), std::back_inserter(uvs));

    uint32_t node_u = static_cast<uint32_t>(std::stoul(uvs[0]));
    uint32_t node_v = static_cast<uint32_t>(std::stoul(uvs[1]));

    //std::cout << "processing:" << node_u << ", " << node_v << "  #"
    //          << line_number << '\n';

    build_graph(ggg, node_u, node_v);
  }

  std::cout << '\n';
  print_graph(ggg);

  return 0;
}

void print_usage(const char *name) {
  std::cout << "Usage: " << name << " -f <FILENAME>" << std::endl;
}
