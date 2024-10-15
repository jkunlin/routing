#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "node.h"

struct Warehouse : public Node {
  int id;
  double capacity; // 仓库容量（单位：物资量）
  Warehouse(int id, double capacity, double x, double y)
      : Node(x, y, NodeType::WareHouse), id(id), capacity(capacity) {}
  Warehouse() : Node() {}
};

#endif // WAREHOUSE_H
