#pragma once

#include <vector>

struct Point2D;

/// @brief Computes a K-mean clustering on the given set of observation
/// @param data The set of observation
/// @param k The number of means (and clusters) to find
/// @return The positions of the means
std::vector<Point2D> kmeans(const std::vector<Point2D>& data, size_t k);
std::vector<std::vector<Point2D>> makeClusters(const std::vector<Point2D>& data,
                                               const std::vector<Point2D>& means);

// NOTE: Exposed only for testing purposes
std::vector<Point2D> initializeMeansForgy(const std::vector<Point2D>& data, size_t k);
std::vector<size_t> randomPartition(const std::vector<Point2D>& data, size_t k);
std::vector<size_t> assignPointsToClusters(const std::vector<Point2D>& data,
                                           const std::vector<Point2D>& means);
std::vector<Point2D> updateMeans(const std::vector<Point2D>& data,
                                 const std::vector<size_t>& labels,
                                 size_t k);

