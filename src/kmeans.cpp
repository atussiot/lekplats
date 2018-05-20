#include <kmeans.h>

#include <point2D_utils.h>

#include <cmath>
#include <random>
#include <stdexcept>

// TODO: a more elegant way to select this
const bool useForgy = false;

// Main algorithm
std::vector<Point2D> kmeans(const std::vector<Point2D>& data, const size_t k)
{
    // Preconditions
    if (k > data.size())
    {
        throw std::runtime_error("");
    }

    // Initialization (initial assignment)
    std::vector<Point2D> means;
    std::vector<size_t> previousLabels(k), labels;

    if (useForgy)
    {
        means = initializeMeansForgy(data, k);
        labels = assignPointsToClusters(data, means);
    }
    else
    {
        labels = randomPartition(data, k);
    }

    // Update and reassign (until it converges)
    while (labels != previousLabels)
    {
        previousLabels = labels;
        means = updateMeans(data, labels, k);
        labels = assignPointsToClusters(data, means);
    }

    return means;
}

// Implementations

std::vector<Point2D> initializeMeansForgy(const std::vector<Point2D>& data, const size_t k)
{
    std::unordered_set<Point2D> uniqueMeans;

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<size_t> dist{ 0, data.size() - 1 };

    for (size_t n = 0; uniqueMeans.size() < k; ++n)
    {
        uniqueMeans.insert(data[dist(generator)]);
    }

    std::vector<Point2D> means;
    means.insert(means.end(), std::make_move_iterator(uniqueMeans.begin()),
                              std::make_move_iterator(uniqueMeans.end()));

    return means;
}

std::vector<size_t> randomPartition(const std::vector<Point2D>& data, const size_t k)
{
    std::vector<size_t> labels;
    labels.reserve(data.size());

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<size_t> dist{ 0, k - 1 };

    for (size_t i = 0; i < data.size(); ++i)
    {
        labels.push_back(dist(generator));
    }

    return labels;
}

double squaredEuclidianDistance(const Point2D& a, const Point2D& b)
{
    return std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2);
}

std::vector<size_t> assignPointsToClusters(const std::vector<Point2D>& data,
                                           const std::vector<Point2D>& means)
{
    std::vector<size_t> assignments;
    assignments.reserve(data.size());

    for (const auto& point : data)
    {
        std::vector<double> distances;
        for (const auto& mean : means)
        {
            distances.push_back(squaredEuclidianDistance(point, mean));
        }
        const auto nearest = std::min_element(distances.begin(), distances.end());
        assignments.push_back(std::distance(distances.begin(), nearest));
    }

    return assignments;
}

std::vector<Point2D> updateMeans(const std::vector<Point2D>& data,
                                 const std::vector<size_t>& labels,
                                 const size_t k)
{
    std::vector<Point2D> means(k);
    std::vector<double> counts(k);

    for (size_t i = 0; i < data.size(); ++i)
    {
        means[ labels[i] ] += data[i];
        counts[ labels[i] ] += 1.0;
    }

    for (size_t i = 0; i < means.size(); ++i)
    {
        means[i] /= counts[i];
    }

    return means;
}

std::vector<std::vector<Point2D>> makeClusters(const std::vector<Point2D>& data,
                                               const std::vector<Point2D>& means)
{
    std::vector<std::vector<Point2D>> clusters(means.size());

    for (const auto& point : data)
    {
        std::vector<double> distances;
        for (const auto& mean : means)
        {
            distances.push_back(squaredEuclidianDistance(point, mean));
        }
        const auto nearest = std::min_element(distances.begin(), distances.end());
        clusters[std::distance(distances.begin(), nearest)].push_back(point);
    }

    return clusters;
}

