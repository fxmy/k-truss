#include "graph.h"
#include <algorithm>
#include <iostream>
#include <vector>

void build_graph(Graph &g, uint32_t u, uint32_t v) {

  build_adj_list_1(g.adj_list_1, u, v);
  build_adjPos_to_edgeId_2(g, u, v);
  build_nodeId_to_adjPos_3(g.nodeId_to_adjPos_3, u, v,
                           g.adj_list_1.array.size(), g.node_num);
  build_edgeId_to_nodeId_4(g.edgeId_to_nodeId_4, u, v,
                           g.adj_list_1.array.size(), g.edge_num);

  //TODO: build_node_degree()
  //TODO: build_node_degree()
}

void build_adj_list_1(Adj_list_1 &adj, uint32_t u, uint32_t v) {
  adj.array.push_back(u);
}

void build_adjPos_to_edgeId_2(Graph &g, uint32_t u, uint32_t v) {
  if (u > v) {
    //仅保留u列比v列大的情况（如果是“正向边”，则直接压入edgeId）
    // edge_num 即为当前的edgeId
    g.adjPos_to_edgeId_2.edge_present.push_back(true);
    g.adjPos_to_edgeId_2.edgeId.push_back(g.edge_num);
    // g.edge_num++;
  } else {
    //“反向边”的情况，查找对应“正向边”的edgeId，然后压入edgeId（u < v）
    // 1.通过_3查找u对应的第一个比u大的邻居的array下标
    uint32_t array_i =
        g.nodeId_to_adjPos_3
            .firstBiggerPos[u - 1]; // zero indexed

    while (g.adj_list_1.array[array_i] != v) {
      array_i++;
    }
    // 2.根据array_i，通过_2查找对应的edgeId
    uint64_t e = g.adjPos_to_edgeId_2.edgeId[array_i];
    // 3.压入_2中edgeId的内容(push_back)
    g.adjPos_to_edgeId_2.edgeId.push_back(e);
    // 4.反向边的情况，并不压入新的edge_present
  }
}

void build_nodeId_to_adjPos_3(NodeId_to_adjPos_3 &n_3, uint32_t u, uint32_t v,
                              const uint64_t adj_size, uint32_t &node_num) {
  // 处理数据集中顶点编号可能不连续的情况，_3中按需压入不存在的nodeId
  uint32_t nodeId_gap = v - n_3.v_lst_rnd;

  if (0 != nodeId_gap) {
    // v发生了变化，意味着正在处理一个新的v
    ++node_num;

    for (uint32_t i = 0; i < nodeId_gap; ++i) {
      //样例数据中的nodeId有可能不连续
      //需要将不存在的nodeId以及存在的nodeId都压入到vector
      if (nodeId_gap - i > 1) {
        // 1.nodeId不存在的情况下，firstPos、lastPos、firstBiggerPos全部压入"-1"
        // 1.node_degree压入"0"
        n_3.firstPos.push_back(-1);
        n_3.firstBiggerPos.push_back(-1);
        n_3.lastPos.push_back(-1);
        n_3.node_degree.push_back(0);
      } else {
        // 2.正在处理gap之后的实际存在的nodeId，如下处理
        //  1)压入firstPos
        n_3.firstPos.push_back(adj_size - 1);
        //  2)压入firstBiggerPos （如果u < v，压入-1， 否则压入adj_size - 1）
        if (u < v) {
          n_3.firstBiggerPos.push_back(-1);
        } else {
          n_3.firstBiggerPos.push_back(adj_size - 1);
        }
        //  3)压入lastPos
        n_3.lastPos.push_back(adj_size); // 应该是adj_size
        //  4)TODO 压入node_degree（压入0，之后再统一计算更新）
        n_3.node_degree.push_back(0);
      }
    }

  } else {
    // v没有发生变化，我们正在处理同一个v的不同的u
    //  1.如果firstBiggerPos为-1，且u > v，更新firstBiggerPos
    if (u > v && -1 == n_3.firstBiggerPos.back()) {
      n_3.firstBiggerPos.back() = adj_size - 1;
    }
    //  2.更新lastPos
    n_3.lastPos.back() = adj_size; // 应该是adj_size
  }

  //最后，更新v_lst_rnd
  n_3.v_lst_rnd = v;
}

void build_edgeId_to_nodeId_4(EdgeId_to_nodeId_4 &e_4, uint32_t u, uint32_t v,
                              const uint64_t adj_size, uint64_t &edge_num) {
  //仅处理正向边，edge_num 即为当前的edgeId
  if (u > v) {
    // 1.压入n_little, n_bigger
    e_4.n_bigger.push_back(u);
    e_4.n_little.push_back(v);
    // 2.TODO 压入support，之后再统一计算更新
    e_4.support.push_back(0);

    ++edge_num;
  }
}

template <typename T> void print_vector(const std::vector<T> &v) {
  for (auto i = v.begin(); i != v.end(); ++i) {
    std::cout << *i << ' ';
  }
}
void print_graph(Graph &g) {
  using std::cout;
  using std::endl;
  cout << "node_num: " << g.node_num << endl;
  cout << "edge_num: " << g.edge_num << endl << endl;

  cout << "_1.array:" << endl;
  print_vector(g.adj_list_1.array);
  cout << endl << endl;

  cout << "_2.edgeId:" << endl;
  print_vector(g.adjPos_to_edgeId_2.edgeId);
  cout << endl;
  cout << "_2.edge_present:" << endl;
  print_vector(g.adjPos_to_edgeId_2.edge_present);
  cout << endl << endl;

  cout << "_3: firstPos" << endl;
  print_vector(g.nodeId_to_adjPos_3.firstPos);
  cout << endl;
  cout << "_3: lastPos" << endl;
  print_vector(g.nodeId_to_adjPos_3.lastPos);
  cout << endl;
  cout << "_3: firstBiggerPos" << endl;
  print_vector(g.nodeId_to_adjPos_3.firstBiggerPos);
  cout << endl;
  cout << "_3: node_degree" << endl;
  print_vector(g.nodeId_to_adjPos_3.node_degree);
  cout << endl << endl;

  cout << "_4: n_little" << endl;
  print_vector(g.edgeId_to_nodeId_4.n_little);
  cout << endl;
  cout << "_4: n_bigger" << endl;
  print_vector(g.edgeId_to_nodeId_4.n_bigger);
  cout << endl;
  cout << "_4: edge_support" << endl;
  print_vector(g.edgeId_to_nodeId_4.support);
  cout << endl << endl;
}
