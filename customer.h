#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "node.h"
#include <vector>

struct Customer : public Node {
  int id;
  double demand_per_hour;                     // 每小时的需求量
  std::vector<double> inventory_last_visited; // 卸货后的库存（小时）
  std::vector<int> time_last_visited;         // 到达时间（小时)，未卸货
  double min_inventory;                       // 最小库存（小时）
  double max_inventory;                       // 最大库存（小时）

  Customer(int id, double demand_per_hour, double current_inventory,
           int current_time, double min_inventory, double max_inventory,
           double x, double y)
      : id(id), demand_per_hour(demand_per_hour), min_inventory(min_inventory),
        max_inventory(max_inventory), Node(x, y, NodeType::Customer) {
    inventory_last_visited.push_back(current_inventory);
    time_last_visited.push_back(current_time);
  }

  Customer() {}

  void push_visited_record(const int visited_time, const double inventory) {
    inventory_last_visited.push_back(inventory);
    time_last_visited.push_back(visited_time);
  }

  int time_to_min_inventory() const {
    double time_to_min_inventory =
        (inventory_last_visited.back() - min_inventory) / demand_per_hour;
    return static_cast<int>(time_to_min_inventory);
  }

  int time_to_min_inventory_backtrace() const {
    if (inventory_last_visited.size() < 2) {
      return time_to_min_inventory();
    }
    double time_to_min_inventory =
        (inventory_last_visited[inventory_last_visited.size() - 2] -
         min_inventory) /
        demand_per_hour;
    return static_cast<int>(time_to_min_inventory);
  }

  int get_inventory_last_visited() const {
    return inventory_last_visited.back();
  }

  int get_time_last_visited() const { return time_last_visited.back(); }

  double max_requirement(int visited_time) const {
    return max_inventory -
           (inventory_last_visited.back() -
            demand_per_hour * (visited_time - time_last_visited.back()));
  }
};

#endif // CUSTOMER_H
