#include "customer.h"
#include "findOptWarehouseLocs.h"
#include "vehicle.h"
#include "warehouse.h"
#include <iostream>
#include <vector>

using namespace std;

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
