#include <kmeans.h>

#include <cluster_description.h>
#include <cluster_generator.h>
#include <point2D_utils.h>

#include <CppUTest/TestHarness.h>

TEST_GROUP(Kmeans)
{
    std::vector<Point2D> data;

    void setup()
    {
        ClusterDescription descr;
        descr.std_dev = Point2D{ 42.2, 66.6 };
        descr.points_count = 200;

        ClusterDescription descr2;
        descr2.mean = Point2D{ 80.8, 100.2 };
        descr2.std_dev = Point2D{ 25.4, 45.6 };
        descr2.points_count = 198;

        std::vector<ClusterDescription> info = { descr, descr2 };
        ClusterGenerator generator { info };

        data = generator.getMergedClusters();
    }
};

TEST(Kmeans, returnsAnEmptyVectorIfGivenNoData)
{
    const auto means = kmeans(std::vector<Point2D>{ }, 0);
    UNSIGNED_LONGS_EQUAL(0, means.size());
}

TEST(Kmeans, throwsAnExceptionIfNumberOfMeansIsHigherThanNumberOfObservations)
{
    CHECK_THROWS(std::runtime_error, kmeans(std::vector<Point2D>{ }, 1));
}

TEST(Kmeans, forgyInitializesWithValuesFromTheData)
{
    const size_t number_of_means = 4;
    const auto means = initializeMeansForgy(data, number_of_means);

    UNSIGNED_LONGS_EQUAL(number_of_means, means.size());
    for (const auto& mean : means)
    {
        const auto found = std::find(data.begin(), data.end(), mean);
        CHECK(found != data.end());
    }
}

TEST(Kmeans, randomPartitionAssignsARandomLabelToEachObservation)
{
    const size_t number_of_means = 6;
    const auto labels = randomPartition(data, number_of_means);

    UNSIGNED_LONGS_EQUAL(data.size(), labels.size());
    for (const auto label : labels)
    {
        CHECK(label < number_of_means);
    }
}

TEST(Kmeans, assignsEachPointToACluster)
{
    const size_t number_of_means = 5;
    const auto means = initializeMeansForgy(data, number_of_means);
    const auto labels = assignPointsToClusters(data, means);

    UNSIGNED_LONGS_EQUAL(data.size(), labels.size());
    for (const auto label : labels)
    {
        CHECK(label < number_of_means);
    }
}

TEST(Kmeans, works)
{
    const auto means = kmeans(data, 2);
    UNSIGNED_LONGS_EQUAL(2, means.size());
}
