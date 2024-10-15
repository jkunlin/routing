#ifndef INCLUDE_ARMY_NODE_H_
#define INCLUDE_ARMY_NODE_H_

#include <string>

enum class NodeType { Customer, WareHouse };
struct Node {
  std::string name;
  double x, y; // 地理坐标
  NodeType type;
  Node(double x, double y, NodeType type) : x(x), y(y), type(type) {};
  Node() {};
};

#endif // INCLUDE_ARMY_NODE_H_
