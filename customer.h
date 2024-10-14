#ifndef CUSTOMER_H
#define CUSTOMER_H

struct Customer {
  int id;
  double demand_per_hour;   // 每小时的需求量
  double current_inventory; // 当前库存（小时）
  double min_inventory;     // 最小库存（小时）
  double max_inventory;     // 最大库存（小时）
  double x, y;              // 地理坐标
};

#endif // CUSTOMER_H
