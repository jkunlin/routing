#ifndef VEHICLE_H
#define VEHICLE_H

#include "customer.h"
#include "node.h"
#include "warehouse.h"
#include <string>
#include <vector>
enum class VehicleType { A, B };

/*class Vehicle {*/
/*private:*/
/*  std::string name;*/
/*  double capacity;*/
/*  double speed;*/
/*  double cost_per_km;*/
/*  VehicleType type;*/
/*};*/

struct Vehicle {
  std::string name;
  VehicleType type;
  double capacity;
  double cur_load;
  Node *cur_node = nullptr;
  int cur_time;
  int load_time;            // 装卸货时间（小时）
  int remain_battery = 100; // 100%

  std::vector<Node *> visited_nodes;

  /*int set_out_time;*/
  /*int arrivate_time;*/
  /*double cost;*/
  /*int cur_time;*/
  /*int cur_node;*/
  /*int wait_time;*/
  /*int remain_driving_range;*/
  /*int end_nd;*/
  /**/
  /*int chg_cnt;*/
  /**/
  /*double sum_delivery_weight, sum_delivery_volume;*/
  /*double load_v, load_w, max_load_w, max_load_v;*/

  /*Vehicle(short int t) : type(t) {*/
  /*  cost = 0;*/
  /*  cur_time = set_out_time = 8 * 60;*/
  /*  cur_node = 0;*/
  /*  remain_driving_range = vehicle_type[type].driving_range;*/
  /*  wait_time = 0;*/
  /*  chg_cnt = 0;*/
  /**/
  /*  sum_delivery_weight = 0;*/
  /*  sum_delivery_volume = 0;*/
  /*  max_load_w = max_load_v = 0;*/
  /*  load_v = load_w = 0;*/
  /*  end_nd = -1;*/
  /*  visited_nodes.reserve(20);*/
  /*}*/

  /*void init() {*/
  /*  cost = 0;*/
  /*  cur_time = set_out_time = 8 * 60;*/
  /*  cur_node = 0;*/
  /*  remain_driving_range = vehicle_type[type].driving_range;*/
  /*  wait_time = 0;*/
  /*  chg_cnt = 0;*/
  /**/
  /*  sum_delivery_weight = 0;*/
  /*  sum_delivery_volume = 0;*/
  /*  max_load_w = max_load_v = 0;*/
  /*  load_v = load_w = 0;*/
  /*  end_nd = -1;*/
  /**/
  /*  visited_nodes.clear();*/
  /*}*/
  /**/
  /*void init(short int t) {*/
  /*  type = t;*/
  /*  cost = 0;*/
  /*  cur_time = set_out_time = 8 * 60;*/
  /*  cur_node = 0;*/
  /*  remain_driving_range = vehicle_type[type].driving_range;*/
  /*  wait_time = 0;*/
  /*  chg_cnt = 0;*/
  /**/
  /*  sum_delivery_weight = 0;*/
  /*  sum_delivery_volume = 0;*/
  /*  max_load_w = max_load_v = 0;*/
  /*  load_v = load_w = 0;*/
  /*  end_nd = -1;*/
  /*  visited_nodes.clear();*/
  /*}*/

  bool dist_time_reachable(const Node *node) const;

  bool capacity_reachable(const Customer *customer) const;

  void to_node(Customer *nd);

  void to_warehouse_none(Warehouse *warehouse);

  void to_warehouse_load(Warehouse *warehouse);

  void to_warehouse_charge(Warehouse *warehouse);

  double sum_dist(Warehouse *warehouse) const;
};

/*Vehicle g_tmp_veh1(IVECO), g_tmp_veh2(IVECO);*/
/*Vehicle g_tmp_veh3(IVECO), g_tmp_veh4(IVECO);*/

#endif // VEHICLE_H
