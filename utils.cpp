#include "utils.h"
#include <cassert>
#include <cmath>

double Distance(double x1, double y1, double x2, double y2) {
  return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// TODO: get from table
double calculateTravelTime(double x1, double y1, double x2, double y2,
                           VehicleType vt) {
  if (vt == VehicleType::A) {
    return Distance(x1, y1, x2, y2) / 50;
  } else if (vt == VehicleType::B) {
    return Distance(x1, y1, x2, y2) / 50;
  } else {
    assert(false);
  }
}

double calculateTravelTime(const Node *n1, const Node *n2, VehicleType vt) {
  return calculateTravelTime(n1->x, n1->y, n2->x, n2->y, vt);
}

double calculateBatteryCost(const Node *n1, const Node *n2, VehicleType vt) {
  return 0;
}

// 充满电需要的时间
int calculateFullChagerTime(Vehicle &veh) {
  int remain_battery = veh.remain_battery; // x%
  VehicleType vt = veh.type;
  return 0;
}

void ComputeCentroid(const std::vector<Customer> &customers, double &centroid_x,
                     double &centroid_y) {
  centroid_x = 0.0;
  centroid_y = 0.0;
  for (const auto &customer : customers) {
    centroid_x += customer.x;
    centroid_y += customer.y;
  }
  centroid_x /= customers.size();
  centroid_y /= customers.size();
}
