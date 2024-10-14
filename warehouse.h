#ifndef WAREHOUSE_H
#define WAREHOUSE_H

struct WarehouseCandidate {
  int id;
  double capacity; // 仓库容量（单位：物资量）
  double x, y;     // 地理坐标
};

#endif // WAREHOUSE_H
