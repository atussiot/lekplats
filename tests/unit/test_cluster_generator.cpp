#include <cluster_generator.h>

#include <cluster_description.h>
#include <point2D_utils.h>

#include <numeric>

#include <CppUTest/TestHarness.h>

TEST_GROUP(AClusterGenerator)
{
    std::vector<ClusterDescription> descriptions;

    void setup()
    {
        ClusterDescription d1, d2;
        d1.points_count = 12;
        d2.points_count = 21;
        d1.mean = Point2D{ -123.456, 654.321 };
        d2.mean = Point2D{ -1.2, -34.5 };
        d1.std_dev = Point2D{ 21.12, 12.21 };
        d2.std_dev = Point2D{ 123.321, 321.123 };
        descriptions.push_back(d1);
        descriptions.push_back(d2);
    }
};

TEST(AClusterGenerator, DoesNotCreateAnythingIfGivenNoInfo)
{
    ClusterGenerator emptyGenerator{ std::vector<ClusterDescription>( ) };

    UNSIGNED_LONGS_EQUAL(0, emptyGenerator.getClusters().size());
    UNSIGNED_LONGS_EQUAL(0, emptyGenerator.getMergedClusters().size());
}

TEST(AClusterGenerator, CreatesTheExpectedAmountOfClusters)
{
    const size_t expected_count = 4;
    const std::vector<ClusterDescription> emptyInfo(expected_count);
    ClusterGenerator generator{ emptyInfo };

    UNSIGNED_LONGS_EQUAL(expected_count, generator.getClusters().size());
}

TEST(AClusterGenerator, CreatesTheExpectedAmountOfPoints)
{
    ClusterGenerator generator{ descriptions };

    for (size_t i = 0; i < descriptions.size(); ++i)
    {
        UNSIGNED_LONGS_EQUAL(descriptions[i].points_count, generator.getClusters()[i].size());
    }
}

TEST(AClusterGenerator, CreatesASingleDatasetContainingAllTheClusters)
{
    ClusterGenerator generator{ descriptions };
    const auto dataset = generator.getMergedClusters();

    const auto op = [](size_t a, const ClusterDescription& b) { return a + b.points_count; };
    const auto expectedSize = std::accumulate(descriptions.begin(), descriptions.end(), 0, op);

    UNSIGNED_LONGS_EQUAL(expectedSize, dataset.size());
}

TEST(AClusterGenerator, DoesNotShuffleTheValuesIfNotRequired)
{
    ClusterGenerator generator{ descriptions };
    const auto shuffle = false;
    const auto& clusters = generator.getClusters();
    const auto dataset = generator.getMergedClusters(shuffle);

    auto it = dataset.begin();
    for (const auto& cluster : clusters)
    {
        for (const auto& point : cluster)
        {
            CHECK(point == *it);
            ++it;
        }
    }
    CHECK(dataset.end() == it)
}

TEST(AClusterGenerator, ShufflesTheValuesInTheSingleDatasetIfRequired)
{
    ClusterGenerator generator{ descriptions };
    const auto shuffle = true;
    const auto shuffledDataset = generator.getMergedClusters(shuffle);
    const auto dataset = generator.getMergedClusters(!shuffle);

    CHECK(!std::equal(dataset.begin(), dataset.end(), shuffledDataset.begin()));
}

