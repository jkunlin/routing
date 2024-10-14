#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include "customer.h"

// 计算两点之间的欧氏距离
double Distance(double x1, double y1, double x2, double y2);

// 计算多个点的质心
void ComputeCentroid(const std::vector<Customer>& customers, double& centroid_x, double& centroid_y);

#endif // UTILS_H

