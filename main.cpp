#include "customer.h"
#include "findOptWarehouseLocs.h"
#include "warehouse.h"
#include <vector>

using std::vector;

using namespace std;

int main() {
  // 数据初始化

  // 客户列表
  vector<Customer> customers = {
      Customer(0, 10.0, 50.0, 20.0, 150.0, 20.0, 30.0),
      Customer(1, 15.0, 70.0, 30.0, 200.0, 50.0, 60.0),
      Customer(2, 12.0, 60.0, 25.0, 180.0, 80.0, 20.0),
      Customer(3, 18.0, 80.0, 35.0, 220.0, 40.0, 90.0),
      Customer(4, 14.0, 65.0, 28.0, 190.0, 60.0, 10.0),
      Customer(5, 16.0, 75.0, 32.0, 210.0, 30.0, 70.0),
      // ... 可以添加更多客户
  };

  // 潜在仓库地点
  vector<Warehouse> warehouse_candidates = {
      Warehouse(0, 1000.0, 25.0, 35.0), Warehouse(1, 1200.0, 55.0, 65.0),
      Warehouse(2, 1500.0, 70.0, 25.0), Warehouse(3, 1100.0, 45.0, 80.0),
      Warehouse(4, 1300.0, 65.0, 15.0), Warehouse(5, 1000.0, 35.0, 75.0),
      // ... 可以添加更多仓库候选点
  };

  // 需要选定的仓库数量
  int n_warehouse = 2;

  // 调用函数
  findOptWarehouseLocs(warehouse_candidates, customers, n_warehouse);

  return 0;
}
