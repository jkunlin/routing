#include "findOptWarehouseLocs.h"
#include "kmeans.h"
#include "utils.h"
#include "vehicle.h"
#include <iostream>
#include <limits>
#include <vector>

const int VEHICLE_SPEED = 50;
void findOptWarehouseLocs(const std::vector<Warehouse> &warehouse_candidates,
                          const std::vector<Customer> &customers,
                          const int n_warehouse) {

  // 使用 K-Means 聚类将客户分成 n_warehouse 个簇
  std::vector<int> assignments;
  KMeansClustering(customers, n_warehouse, assignments);

  // 存储每个簇中的客户
  std::vector<std::vector<Customer>> clusters(n_warehouse);
  for (size_t i = 0; i < customers.size(); ++i) {
    int cluster_id = assignments[i];
    clusters[cluster_id].push_back(customers[i]);
  }

  // 为每个簇选择满足时间要求的最佳仓库候选地点作为仓库位置
  std::vector<Warehouse> selected_warehouses;
  for (int i = 0; i < n_warehouse; ++i) {
    // 计算簇的质心
    double centroid_x, centroid_y;
    ComputeCentroid(clusters[i], centroid_x, centroid_y);

    // 在仓库候选地点中找到满足时间要求的最佳仓库
    double min_max_time = std::numeric_limits<double>::max();
    Warehouse best_warehouse;
    bool found = false;
    // FIXME: warehouse可能之前已经被选中
    for (const auto &warehouse : warehouse_candidates) {
      double max_time = 0.0;
      bool feasible = true;
      for (const auto &customer : clusters[i]) {
        // 计算从仓库到客户的配送时间（假设固定速度）
        double travel_time = calculateTravelTime(
            warehouse.x, warehouse.y, customer.x, customer.y, VehicleType::A);

        // 计算客户的剩余可用时间
        double T_remain = customer.time_to_min_inventory();
        if (travel_time > T_remain) {
          feasible = false;
          break; // 当前仓库不满足该客户的时间要求
        }

        if (travel_time > max_time) {
          max_time = travel_time;
        }
      }

      if (feasible && max_time < min_max_time) {
        min_max_time = max_time;
        best_warehouse = warehouse;
        found = true;
      }
    }

    if (found) {
      selected_warehouses.push_back(best_warehouse);
    } else {
      // 如果没有仓库满足时间要求，选择最近的仓库
      double min_total_time = std::numeric_limits<double>::max();
      for (const auto &warehouse : warehouse_candidates) {
        double total_time = 0.0;
        for (const auto &customer : clusters[i]) {
          double travel_time =
              Distance(warehouse.x, warehouse.y, customer.x, customer.y) /
              VEHICLE_SPEED;
          total_time += travel_time;
        }
        if (total_time < min_total_time) {
          min_total_time = total_time;
          best_warehouse = warehouse;
        }
      }
      selected_warehouses.push_back(best_warehouse);
    }
  }

  // 输出结果
  std::cout << "选定的仓库位置：" << std::endl;
  for (const auto &warehouse : selected_warehouses) {
    std::cout << "  仓库 " << warehouse.id << " at (" << warehouse.x << ", "
              << warehouse.y << ")" << std::endl;
  }

  // 输出客户分配
  std::cout << "客户分配：" << std::endl;
  for (int i = 0; i < n_warehouse; ++i) {
    for (const auto &customer : clusters[i]) {
      std::cout << "  客户 " << customer.id << " 分配给仓库 "
                << selected_warehouses[i].id << std::endl;
    }
  }
}
