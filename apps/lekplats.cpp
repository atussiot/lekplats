#include <cluster_description.h>
#include <cluster_generator.h>
#include <image_io.h>
#include <kmeans.h>
#include <point2D.h>
#include <van_eck_sequence.h>

#include <cstdlib>
#include <iostream>

int play_with_kmeans();
int play_with_van_eck();

int main(int argc, char* argv[])
{
    // TODO: Split to different applications (?)
    //return play_with_kmeans();
    return play_with_van_eck();
}

int play_with_kmeans()
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
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < means.size(); ++i)
    {
        std::cout << "Mean: " << means[i][0] << " - " << means[i][1] << std::endl;
        std::cout << "Points in the cluster: " << kmeansClusters[i].size() << std::endl;
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}

int play_with_van_eck()
{
    static const int N = 1000;
    std::cout << "Number of iterations: " << N << std::endl << std::endl;
    for (int ini = 0; ini < 11; ++ini) {
        const auto S = generate_van_eck_seq_stats(N, ini);
        std::cout << "[" << ini << "] ";
        std::cout << "Number of elements: " << S.size() << " - ";
        std::cout << "First missing value: " << first_missing_value(S) << " - ";
        std::cout << "Highest value: " << highest_value(S) << std::endl;
    }
    return EXIT_SUCCESS;
}
