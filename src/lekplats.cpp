#include <cluster_description.h>
#include <cluster_generator.h>
#include <image_io.h>
#include <kmeans.h>
#include <point2D.h>

#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[])
{
    ClusterDescription descr1;
    descr1.mean = Point2D{ 240.0, 350.2 };
    descr1.std_dev = Point2D{ 71.4, 15.7 };
    descr1.points_count = 800;

    ClusterDescription descr2;
    descr2.mean = Point2D{ 354.0, 270.4 };
    descr2.std_dev = Point2D{ 20.4, 90.7 };
    descr2.points_count = 600;

    const std::vector<ClusterDescription> info = { descr1, descr2 };
    ClusterGenerator generator{ info };

    const auto& originalClusters = generator.getClusters();
    const auto data = generator.getMergedClusters();

    const auto means = kmeans(data, 2);
    const auto kmeansClusters = makeClusters(data, means);

    if (!saveToFile("original.png", originalClusters[0], originalClusters[1]))
    {
        std::cerr << "Could not save first image" << std::endl;
        return EXIT_FAILURE;
    }

    if (!saveToFile("kmeans.png", kmeansClusters[0], kmeansClusters[1]))
    {
        std::cerr << "Could not save second image" << std::endl;
    }

    for (size_t i = 0; i < 2; ++i)
    {
        std::cout << "Mean: " << means[i].x << " - " << means[i].y << std::endl;
        std::cout << "Points in the cluster: " << kmeansClusters[i].size() << std::endl;
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}

