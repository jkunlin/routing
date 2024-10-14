#include "customer.h"
#include "kmeans.h"
#include "utils.h"
#include "warehouse.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void findOptWarehouseLocs(
    const std::vector<WarehouseCandidate> &warehouse_candidates,
    const std::vector<Customer> &customers, const int n_warehouse) {

  // 使用 K-Means 聚类将客户分成 n_warehouse 个簇
  std::vector<int> assignments;
  KMeansClustering(customers, n_warehouse, assignments);

  // 存储每个簇中的客户
  std::vector<std::vector<Customer>> clusters(n_warehouse);
  for (size_t i = 0; i < customers.size(); ++i) {
    int cluster_id = assignments[i];
    clusters[cluster_id].push_back(customers[i]);
  }

  // 为每个簇选择最近的仓库候选地点作为仓库位置
  std::vector<WarehouseCandidate> selected_warehouses;
  for (int i = 0; i < n_warehouse; ++i) {
    // 计算簇的质心
    double centroid_x, centroid_y;
    ComputeCentroid(clusters[i], centroid_x, centroid_y);

    // 在仓库候选地点中找到距离质心最近的仓库
    double min_dist = std::numeric_limits<double>::max();
    WarehouseCandidate best_warehouse;
    for (const auto &warehouse : warehouse_candidates) {
      double dist = Distance(centroid_x, centroid_y, warehouse.x, warehouse.y);
      if (dist < min_dist) {
        min_dist = dist;
        best_warehouse = warehouse;
      }
    }
    selected_warehouses.push_back(best_warehouse);
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

int main() {
  // 数据初始化

  // 客户列表
  std::vector<Customer> customers = {
      {0, 10.0, 50.0, 150.0, 20.0, 30.0}, {1, 15.0, 70.0, 200.0, 50.0, 60.0},
      {2, 12.0, 60.0, 180.0, 80.0, 20.0}, {3, 18.0, 80.0, 220.0, 40.0, 90.0},
      {4, 14.0, 65.0, 190.0, 60.0, 10.0}, {5, 16.0, 75.0, 210.0, 30.0, 70.0},
      // ... 可以添加更多客户
  };

  // 潜在仓库地点
  std::vector<WarehouseCandidate> warehouse_candidates = {
      {0, 25.0, 35.0}, {1, 55.0, 65.0}, {2, 70.0, 25.0},
      {3, 45.0, 80.0}, {4, 65.0, 15.0}, {5, 35.0, 75.0},
      // ... 可以添加更多仓库候选点
  };

  // 需要选定的仓库数量
  int n_warehouse = 2;

  // 调用函数
  findOptWarehouseLocs(warehouse_candidates, customers, n_warehouse);

  return 0;
}
