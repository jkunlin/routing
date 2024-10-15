#include "vehicle.h"
#include "utils.h"
#include <cassert>

bool Vehicle::capacity_reachable(const Customer *customer) const {
  int arrivate_time = cur_time + calculateTravelTime(cur_node, customer, type);
  if (customer->max_requirement(arrivate_time) <= capacity - cur_load)
    return true;
  else
    return false;
}

bool Vehicle::dist_time_reachable(const Node *node) const {
  int arrivate_time = cur_time + calculateTravelTime(cur_node, node, type);

  // time unreachable
  if (node->type == NodeType::Customer) {
    if (arrivate_time >
        (static_cast<const Customer *>(node))->time_to_min_inventory()) {
      return false;
    }
  }
  // battery unreachable
  if (remain_battery < calculateBatteryCost(cur_node, node, type)) {
    return false;
  }
  return true;
}

void Vehicle::to_node(Customer *customer) {
  assert(dist_time_reachable(customer));
  assert(capacity_reachable(static_cast<const Customer *>(customer)));
  int arrivate_time = cur_time + calculateTravelTime(cur_node, customer, type);
  double requirement =
      static_cast<const Customer *>(customer)->max_requirement(arrivate_time);
  cur_load += requirement;
  cur_time += arrivate_time + load_time;
  remain_battery -= calculateBatteryCost(cur_node, customer, type);
  customer->push_visited_record(arrivate_time, requirement);
  cur_node = customer;

  visited_nodes.push_back(customer);
}

void Vehicle::to_warehouse_none(Warehouse *warehouse) {
  assert(dist_time_reachable(warehouse));
  int arrivate_time = cur_time + calculateTravelTime(cur_node, warehouse, type);
  remain_battery -= calculateBatteryCost(cur_node, warehouse, type);
  cur_time += arrivate_time;
  cur_node = warehouse;
  visited_nodes.push_back(warehouse);
}

void Vehicle::to_warehouse_load(Warehouse *warehouse) {
  assert(dist_time_reachable(warehouse));
  int arrivate_time = cur_time + calculateTravelTime(cur_node, warehouse, type);
  remain_battery -= calculateBatteryCost(cur_node, warehouse, type);
  cur_load = 0;
  cur_time += arrivate_time + load_time;
  cur_node = warehouse;
  visited_nodes.push_back(warehouse);
}

void Vehicle::to_warehouse_charge(Warehouse *warehouse) {
  assert(dist_time_reachable(warehouse));
  int arrivate_time = cur_time + calculateTravelTime(cur_node, warehouse, type);
  remain_battery = 100;
  cur_time += arrivate_time + calculateFullChagerTime(*this);
  cur_node = warehouse;
  visited_nodes.push_back(warehouse);
}

double Vehicle::sum_dist(Warehouse *warehouse) const {
  double sum = 0;
  Node *last_node = warehouse;
  for (auto nd : visited_nodes) {
    sum += calculateTravelTime(last_node, nd, type);
    last_node = nd;
  }
  return sum;
}
