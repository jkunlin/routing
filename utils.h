#ifndef UTILS_H
#define UTILS_H

#include "customer.h"
#include "vehicle.h"
#include <vector>

// 计算两点之间的欧氏距离
double Distance(double x1, double y1, double x2, double y2);

double calculateTravelTime(double x1, double y1, double x2, double y2,
                           VehicleType vt);
double calculateTravelTime(const Node *n1, const Node *n2, VehicleType vt);

double calculateBatteryCost(const Node *n1, const Node *n2, VehicleType vt);

int calculateFullChagerTime(Vehicle &veh);

// 计算多个点的质心
void ComputeCentroid(const std::vector<Customer> &customers, double &centroid_x,
                     double &centroid_y);

#endif // UTILS_H
