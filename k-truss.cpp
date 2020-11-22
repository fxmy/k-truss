#include "graph.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string.h>
#include <string>
#include <vector>

#define NODE_RESERVE 2000000 //2M
#define EDGE_RESERVE 20000000 //20M

Graph ggg;

void print_usage(const char *name);

int main(int argc, char *argv[]) {
  using std::string;

  if (3 != argc || 0 != strcmp("-f", argv[1])) {
    print_usage(argv[0]);
    std::cout << argc << std::endl;
    return -1;
  }

  //reserve capacity for vectors in ggg
  ggg.adj_list_1.array.reserve(EDGE_RESERVE * 2);
  ggg.adjPos_to_edgeId_2.edgeId.reserve(EDGE_RESERVE * 2);
    // edge_present 最后进行一次性初始化(post_build_graph)
  ggg.nodeId_to_adjPos_3.firstPos.reserve(NODE_RESERVE);
  ggg.nodeId_to_adjPos_3.lastPos.reserve(NODE_RESERVE);
  ggg.nodeId_to_adjPos_3.firstBiggerPos.reserve(NODE_RESERVE);
    //node_degree  最后进行一次性初始化(post_build_graph)
  ggg.edgeId_to_nodeId_4.n_bigger.reserve(EDGE_RESERVE);
  ggg.edgeId_to_nodeId_4.n_little.reserve(EDGE_RESERVE);
    // edge_support 最后进行一次性初始化(post_build_graph)

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
  post_build_graph(ggg);

  std::cout << '\n';
  print_graph(ggg);

  return 0;
}

void print_usage(const char *name) {
  std::cout << "Usage: " << name << " -f <FILENAME>" << std::endl;
}
