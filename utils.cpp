#include "utils.h"
#include <cmath>

double Distance(double x1, double y1, double x2, double y2) {
  return std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
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
