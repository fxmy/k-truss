#include <stdint.h>
#include <vector>

//连续的、储存邻接链表的array
struct Adj_list_1 {
  std::vector<uint32_t> array;
};

// array下标 -> 边id、边的删除标志的映射
struct AdjPos_to_edgeId_2 {
  std::vector<uint64_t> edgeId; //仅存储“正向边”
  std::vector<bool> edge_present;
};

/* node id到array中：
1) 邻接列表起止点(左闭右开)
2) 第一个比自己大的node id
3) node id 的 degree
的位置下标*/
struct NodeId_to_adjPos_3 {
  std::vector<uint32_t> firstPos;
  std::vector<uint32_t> lastPos;
  std::vector<uint32_t> firstBiggerPos;
  std::vector<uint32_t> node_degree;
  uint32_t v_lst_rnd = 0;
};

/* 1) edge id到其两个node id的映射
   2) edge 对应的support度*/
struct EdgeId_to_nodeId_4 {
  std::vector<uint32_t> n_little;
  std::vector<uint32_t> n_bigger;
  std::vector<uint32_t> support;
};

struct Graph {
  uint32_t node_num = 0;
  uint64_t edge_num = 0; //仅统计正向边

  struct Adj_list_1 adj_list_1;
  struct AdjPos_to_edgeId_2 adjPos_to_edgeId_2;
  struct NodeId_to_adjPos_3 nodeId_to_adjPos_3;
  struct EdgeId_to_nodeId_4 edgeId_to_nodeId_4;
};

void build_graph(Graph &, uint32_t, uint32_t);
void build_adj_list_1(Adj_list_1 &, uint32_t, uint32_t);
void build_adjPos_to_edgeId_2(Graph &, uint32_t, uint32_t);
void build_nodeId_to_adjPos_3(NodeId_to_adjPos_3 &, uint32_t, uint32_t,
                              const uint64_t, uint32_t &);
void build_edgeId_to_nodeId_4(EdgeId_to_nodeId_4 &, uint32_t, uint32_t,
                              const uint64_t, uint64_t &);

void print_graph(Graph &);

void build_node_degree(Graph &);
void build_edge_support(Graph &);
