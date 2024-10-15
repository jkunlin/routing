#ifndef CONSTRUCT_H_RZMUTMOP
#define CONSTRUCT_H_RZMUTMOP

#include "customer.h"
#include "node.h"
#include "utils.h"
#include "vehicle.h"
#include "warehouse.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <set>
#include <vector>

class Construct {
public:
  // 参数设置
  int param_int_1 = 4;
  double param_double_4 = 0.6;

  // 结果存储
  std::vector<Vehicle> result;

  // 构造函数
  Construct() {
    // 初始化操作（如果需要）
  }

  // 添加未访问的节点
  void unvisit_node_push(Node *nd) {
    index_unvisit_node[nd] = unvisit_node.size();
    unvisit_node.push_back(nd);
  }

  // 移除未访问的节点
  void unvisit_node_pop(const int nd) {
    int index = index_unvisit_node[nd];
    index_unvisit_node[unvisit_node.back()] = index;
    index_unvisit_node[nd] = -1;
    unvisit_node[index] = unvisit_node.back();
    unvisit_node.pop_back();
  }

  // 创建新的车辆路径（保证容量约束已满足）
  void new_vehicle(Vehicle &veh, const std::vector<Node *> &node_seq) {
    for (auto nd : node_seq) {
      if (nd->type != NodeType::Customer) {
        continue;
      }
      Customer *customer = static_cast<Customer *>(nd);
      if (veh.dist_time_reachable(customer)) {
        veh.to_node(customer);
      } else {
        veh.to_warehouse_charge(warehouse);
        veh.to_node(customer);
      }
    }
    if (veh.dist_time_reachable(warehouse)) {
      veh.to_warehouse_none(warehouse);
    }
  }

  // 尝试在节点序列中插入新的节点，构建新的车辆路径
  bool new_vehicle(Vehicle &veh, const std::vector<Node *> &node_seq,
                   Customer *customer_insert, const size_t index) {
    // 非严格的初步过滤，目的是提高速度；
    // 检查时间窗约束，避免违反客户的最晚服务时间
    int visited_time = 0;
    for (size_t i = index; i-- > 0;) {
      const Node *node_before = node_seq[i];
      if (node_before->type == NodeType::Customer) {
        const Customer *customer_before =
            static_cast<const Customer *>(node_before);
        int travel_time =
            calculateTravelTime(customer_before, customer_insert, veh.type);
        visited_time = customer_before->get_time_last_visited() +
                       veh.load_time + travel_time;
        if (visited_time > customer_insert->time_to_min_inventory()) {
          return false;
        }
        break;
      }
    }

    for (size_t i = index; i < node_seq.size(); ++i) {
      const Node *node_after = node_seq[i];
      if (node_after->type == NodeType::Customer) {
        const Customer *customer_after =
            static_cast<const Customer *>(node_after);
        int travel_time =
            calculateTravelTime(customer_insert, customer_after, veh.type);
        if (visited_time + travel_time + veh.load_time >
            customer_after->time_to_min_inventory_backtrace()) {
          return false;
        }
        break;
      }
    }

    // 构建新的节点序列并检查容量和距离约束
    for (size_t i = 0, j = 0; i < node_seq.size() + 1; ++i) {
      Node *nd;
      if (i == index) {
        nd = static_cast<Customer *>(customer_insert);
      } else {
        nd = node_seq[j++];
      }

      if (nd->type != NodeType::Customer) {
        continue;
      }

      Customer *customer = static_cast<Customer *>(nd);
      if (veh.dist_time_reachable(customer)) {
        if (!veh.capacity_reachable(customer)) {
          // 先回仓库补货
          if (!veh.dist_time_reachable(warehouse)) {
            return false;
          }
          veh.to_warehouse_load(warehouse);

          // 充电
          if (!veh.dist_time_reachable(customer)) {
            veh.to_warehouse_charge(warehouse);
          }

          assert(veh.capacity_reachable(customer));
          // 检查充电后能不能在customer库存耗尽前过去
          if (veh.dist_time_reachable(customer)) {
            veh.to_node(customer);
          } else {
            return false;
          }
        } else { // 直接去customer
          veh.to_node(customer);
        }
      } else {
        // 先回仓库充电
        if (!veh.dist_time_reachable(warehouse)) {
          return false;
        }
        veh.to_warehouse_charge(warehouse);

        if (!veh.capacity_reachable(customer)) {
          veh.to_warehouse_load(warehouse);
        }

        assert(veh.capacity_reachable(customer));
        if (veh.dist_time_reachable(customer)) {
          veh.to_node(customer);
        } else {
          return false;
        }
      }
    }

    // 返回车场
    if (veh.dist_time_reachable(warehouse)) {
      veh.to_warehouse_none(warehouse);
    } else {
      return false;
    }
    return true;
  }

  // 计算插入节点后的车辆成本
  bool cal_veh_cost(const std::vector<Node *> &node_seq,
                    Customer *customer_insert, const size_t index,
                    const short int veh_type, double &cost) {
    Vehicle veh;
    if (new_vehicle(veh, node_seq, customer_insert, index) == false) {
      return false;
    }

    double gamma = 2, alpha = 0;
    cost = veh.sum_dist(warehouse) -
           gamma * (calculateTravelTime(warehouse, customer_insert, veh.type) +
                    calculateTravelTime(customer_insert, warehouse, veh.type));
    return true;
  }

  // 构造节点序列
  void contruct_node_seq(std::vector<Node *> &node_seq,
                         const short int veh_type) {
    node_seq.clear();
    while (!unvisit_node.empty()) {
      Node *best_nd;
      size_t best_index;
      double min_cost;
      bool has_valid_node = false;

      for (size_t i = 0; i < unvisit_node.size(); ++i) {
        Node *nd = unvisit_node[i];
        for (size_t j = 0; j <= node_seq.size(); ++j) {
          double cost;
          if (cal_veh_cost(node_seq, static_cast<Customer *>(nd), j, veh_type,
                           cost)) {
            if (!has_valid_node || cost < min_cost) {
              best_nd = nd;
              best_index = j;
              min_cost = cost;
              has_valid_node = true;
            }
          }
        }
      }

      if (has_valid_node) {
        unvisit_node_pop(best_nd);
        node_seq.push_back(0);
        for (size_t i = node_seq.size(); i-- > best_index + 1;) {
          node_seq[i] = node_seq[i - 1];
        }
        node_seq[best_index] = best_nd;
      } else {
        for (auto nd : node_seq) {
          unvisit_node_push(nd);
        }
        return;
      }
    }

    for (auto nd : node_seq) {
      unvisit_node_push(nd);
    }
  }

  // 主函数，构建所有车辆的路径
  void constructAll(std::set<Node *> &all_customers) {
    const int client_count = client_to - client_from + 1;
    unvisit_node = all_customers;

    std::vector<Node *> node_seq_IVECO;
    while (!unvisit_node.empty()) {
      Vehicle veh_IVECO;

      // 构建 IVECO 车辆的节点序列
      contruct_node_seq(node_seq_IVECO, IVECO);
      if (!node_seq_IVECO.empty()) {
        new_vehicle(veh_IVECO, node_seq_IVECO);
      }

      // 选择成本较低的车辆类型
      result.push_back(veh_IVECO);
      for (auto nd : node_seq_IVECO) {
        unvisit_node.erase(nd);
      }
    }
  }

private:
  // 私有成员变量
  std::set<Node *> unvisit_node;

  // 以下变量需要在类中定义或在构造函数中传入
  // 例如：
  std::vector<Node> input_node;
  std::vector<std::vector<int>> dist_matrix;
  std::vector<std::vector<int>> time_matrix;
  std::vector<VehicleType> vehicle_type;

  // 还包括：
  double unvisit_delivery_w, unvisit_delivery_v;
  double unvisit_pickup_w, unvisit_pickup_v;
  int client_to, client_from;

  Warehouse *warehouse;
  // 以及其他在代码中使用到的全局变量

  // 根据实际情况，需要在类中添加对应的成员变量或方法，以确保代码的正确性
};

#endif /* end of include guard: CONSTRUCT_H_RZMUTMOP */
