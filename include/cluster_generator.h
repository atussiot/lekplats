#pragma once

#include <vector>

struct Point2D;
struct ClusterDescription;

std::vector<Point2D> generateCluster(const ClusterDescription& descr);
std::vector<Point2D> generateClusters(const std::vector<ClusterDescription>& clustersInfo);

