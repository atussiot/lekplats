#include <cluster_description.h>
#include <cluster_generator.h>
#include <image_io.h>
#include <kmeans.h>
#include <point2D.h>

#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[])
{
    ClusterDescription d1, d2, d3;

    d1.mean = Point2D{ 240.0, 350.2 };
    d1.std_dev = Point2D{ 71.4, 15.7 };
    d1.points_count = 800;

    d2.mean = Point2D{ 354.0, 270.4 };
    d2.std_dev = Point2D{ 20.4, 90.7 };
    d2.points_count = 600;

    d3.mean = Point2D{ 201.3, 194.4 };
    d3.std_dev = Point2D{ 27.8, 28.7 };
    d3.points_count = 700;

    const std::vector<ClusterDescription> info = { d1, d2, d3 };
    ClusterGenerator generator{ info };

    const auto& originalClusters = generator.getClusters();
    const auto data = generator.getMergedClusters();

    const auto means = kmeans(data, 3);
    const auto kmeansClusters = makeClusters(data, means);

    if (!saveToFile("original.png", originalClusters))
    {
        std::cerr << "Could not save first image" << std::endl;
        return EXIT_FAILURE;
    }

    if (!saveToFile("kmeans.png", kmeansClusters))
    {
        std::cerr << "Could not save second image" << std::endl;
    }

    for (size_t i = 0; i < means.size(); ++i)
    {
        std::cout << "Mean: " << means[i].x << " - " << means[i].y << std::endl;
        std::cout << "Points in the cluster: " << kmeansClusters[i].size() << std::endl;
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}

