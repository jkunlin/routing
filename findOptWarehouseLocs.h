#ifndef INCLUDE_ARMY_FINDOPTWAREHOUSELOCS_H_
#define INCLUDE_ARMY_FINDOPTWAREHOUSELOCS_H_

#include "customer.h"
#include "warehouse.h"
#include <vector>

void findOptWarehouseLocs(const std::vector<Warehouse> &warehouse_candidates,
                          const std::vector<Customer> &customers,
                          const int n_warehouse);

#endif // INCLUDE_ARMY_FINDOPTWAREHOUSELOCS_H_
