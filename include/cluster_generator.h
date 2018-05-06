#pragma once

#include <point2D.h>

#include <vector>

struct ClusterDescription;

class ClusterGenerator
{
public:
    ClusterGenerator(const std::vector<ClusterDescription>& descriptions);

    const std::vector<std::vector<Point2D>>& getClusters() const;
    std::vector<Point2D> getMergedClusters() const;
private:
    const std::vector<std::vector<Point2D>> _clusters;
};

