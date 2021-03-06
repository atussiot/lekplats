#include <cluster_generator.h>

#include <cluster_description.h>
#include <point2D.h>

#include <random>

using Clusters = std::vector<std::vector<Point2D>>;

Clusters generateClusters(const std::vector<ClusterDescription>& descriptions)
{
    Clusters clusters;
    clusters.reserve(descriptions.size());

    std::random_device rd;
    std::mt19937 generator{ rd() };

    for (const auto& descr : descriptions)
    {
        std::vector<Point2D> cluster;
        cluster.reserve(descr.points_count);

        std::normal_distribution<> distr_x{ descr.mean[0], descr.std_dev[0] };
        std::normal_distribution<> distr_y{ descr.mean[1], descr.std_dev[1] };

        for (size_t n = 0; n < descr.points_count; ++n)
        {
            cluster.emplace_back(Point2D{ distr_x(generator), distr_y(generator) });
        }

        clusters.emplace_back(std::move(cluster));
    }

    return clusters;
}

ClusterGenerator::ClusterGenerator(const std::vector<ClusterDescription>& descriptions)
    : _clusters(generateClusters(descriptions))
{ }

const Clusters& ClusterGenerator::getClusters() const
{
    return _clusters;
}

std::vector<Point2D> ClusterGenerator::getMergedClusters(const bool shuffle) const
{
    const auto countOp = [](size_t a, const std::vector<Point2D>& b) { return a + b.size(); };
    const auto totalSize = std::accumulate(_clusters.begin(), _clusters.end(), 0, countOp);

    std::vector<Point2D> vectorOut;
    vectorOut.reserve(totalSize);

    for (const auto& cluster : _clusters)
    {
        vectorOut.insert(vectorOut.end(), cluster.begin(), cluster.end());
    }

    if (shuffle)
    {
        auto rand = std::default_random_engine{ };
        std::shuffle(vectorOut.begin(), vectorOut.end(), rand);
    }

    return vectorOut;
}

