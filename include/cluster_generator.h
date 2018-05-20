#pragma once

#include <point2D.h>

#include <vector>

struct ClusterDescription;

class ClusterGenerator
{
public:
    /// @note The cluster are already generated when the object is constructed
    ClusterGenerator(const std::vector<ClusterDescription>& descriptions);

    const std::vector<std::vector<Point2D>>& getClusters() const;
    /// Merge all the clusters into a single dataset
    /// @param shuffle Set the point in a random order, just concatenate the clusters otherwise
    std::vector<Point2D> getMergedClusters(bool shuffle = true) const;
private:
    const std::vector<std::vector<Point2D>> _clusters;
};

