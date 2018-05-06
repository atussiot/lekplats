#include <cluster_generator.h>

#include <cluster_description.h>
#include <point2D.h>

#include <random>

std::vector<Point2D> generateCluster(const ClusterDescription& descr)
{
    std::vector<Point2D> vectorOut;
    vectorOut.reserve(descr.points_count);

    std::random_device rd;
    std::mt19937 generator{ rd() };
    std::normal_distribution<> distr_x{ descr.mean.x, descr.std_dev.x }; 
    std::normal_distribution<> distr_y{ descr.mean.y, descr.std_dev.y }; 

    for (size_t n = 0; n < descr.points_count; ++n)
    {
        vectorOut.emplace_back(Point2D{ distr_x(generator), distr_y(generator) });
    }
    
    return vectorOut;
}

std::vector<Point2D> generateClusters(const std::vector<ClusterDescription>& clustersInfo)
{
    const auto countOp = [](size_t a, const ClusterDescription& b) { return a + b.points_count; };
    const auto totalSize = std::accumulate(clustersInfo.begin(), clustersInfo.end(), 0, countOp);

    std::vector<Point2D> vectorOut;
    vectorOut.reserve(totalSize);

    std::random_device rd;
    std::mt19937 generator{ rd() };

    for (const auto& descr : clustersInfo)
    {
        std::normal_distribution<> distr_x{ descr.mean.x, descr.std_dev.x }; 
        std::normal_distribution<> distr_y{ descr.mean.y, descr.std_dev.y }; 
        for (size_t n = 0; n < descr.points_count; ++n)
        {
            vectorOut.emplace_back(Point2D{ distr_x(generator), distr_y(generator) }); 
        }
    }

    return vectorOut;
}

