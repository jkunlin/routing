#ifndef KMEANS_H
#define KMEANS_H

#include <vector>
#include "customer.h"

// 执行 K-Means 聚类算法
void KMeansClustering(const std::vector<Customer>& customers, int k, std::vector<int>& assignments);

#endif // KMEANS_H

