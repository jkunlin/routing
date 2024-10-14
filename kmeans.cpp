#include "kmeans.h"
#include "utils.h"
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm>

// 定义一个结构体表示质心
struct Centroid {
    double x;
    double y;
};

void KMeansClustering(const std::vector<Customer>& customers, int k, std::vector<int>& assignments) {
    const int max_iterations = 100;
    const double epsilon = 1e-4;
    int num_customers = customers.size();
    assignments.resize(num_customers);

    // 初始化质心，随机选择 k 个客户的位置作为初始质心
    std::srand(std::time(nullptr));
    std::vector<Centroid> centroids(k);
    std::vector<int> initial_indices(num_customers);
    for (int i = 0; i < num_customers; ++i) {
        initial_indices[i] = i;
    }
    std::random_shuffle(initial_indices.begin(), initial_indices.end());
    for (int i = 0; i < k; ++i) {
        centroids[i].x = customers[initial_indices[i]].x;
        centroids[i].y = customers[initial_indices[i]].y;
    }

    for (int iter = 0; iter < max_iterations; ++iter) {
        bool is_converged = true;

        // Step 1: 分配客户到最近的质心
        for (int i = 0; i < num_customers; ++i) {
            double min_dist = std::numeric_limits<double>::max();
            int best_cluster = -1;
            for (int j = 0; j < k; ++j) {
                double dist = Distance(customers[i].x, customers[i].y, centroids[j].x, centroids[j].y);
                if (dist < min_dist) {
                    min_dist = dist;
                    best_cluster = j;
                }
            }
            if (assignments[i] != best_cluster) {
                is_converged = false;
                assignments[i] = best_cluster;
            }
        }

        // Step 2: 更新质心位置
        std::vector<double> sum_x(k, 0.0);
        std::vector<double> sum_y(k, 0.0);
        std::vector<int> count(k, 0);

        for (int i = 0; i < num_customers; ++i) {
            int cluster = assignments[i];
            sum_x[cluster] += customers[i].x;
            sum_y[cluster] += customers[i].y;
            count[cluster] += 1;
        }

        for (int j = 0; j < k; ++j) {
            if (count[j] > 0) {
                double new_x = sum_x[j] / count[j];
                double new_y = sum_y[j] / count[j];
                if (Distance(centroids[j].x, centroids[j].y, new_x, new_y) > epsilon) {
                    is_converged = false;
                }
                centroids[j].x = new_x;
                centroids[j].y = new_y;
            }
        }

        // 检查是否收敛
        if (is_converged) {
            break;
        }
    }
}

