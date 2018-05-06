#include <cluster_description.h>
#include <cluster_generator.h>

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
