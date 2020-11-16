#include <bits/stdint-uintn.h>
#include <stdint.h>
#include <vector>

/*
 * 连续的、储存邻接链表的array
 */
struct adj_list_1 {
  std::vector<uint32_t> array;
};

/*
 * array下标 -> 边id、边的删除标志的映射
 */
struct adjPos_to_edgeId_2 {
  std::vector<uint64_t> edgeId_pos;
  std::vector<uint64_t> edgeId;
  std::vector<bool> edge_present;
};

/*
 * node id到array中：
 * 1) 邻接列表起止点(inclusive)
 * 2) 第一个比自己大的node id
 * 3) node id 的 degree
 * 的位置下标
 */
struct nodeId_to_adjPos_3 {
  std::vector<uint32_t> firstPos;
  std::vector<uint32_t> lastPos;
  std::vector<uint32_t> node_degree;
};

/*
 * 1) edge id到其两个node id的映射(assume u < v)
 * 2) edge 对应的support度*
 */
struct edgeId_to_nodeId_4 {
  std::vector<uint32_t> u;
  std::vector<uint32_t> v;
  std::vector<uint32_t> support;
};
