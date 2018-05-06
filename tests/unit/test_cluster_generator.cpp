#include <cluster_description.h>
#include <cluster_generator.h>

#include <CppUTest/TestHarness.h>

TEST_GROUP(SingleClusterGenerator)
{
    const ClusterDescription EMPTY_DESCRIPTION;
    ClusterDescription description;
};

TEST(SingleClusterGenerator, DoesNotFailWithZeroPointCount)
{
    const auto emptyCluster = generateCluster(EMPTY_DESCRIPTION);
    UNSIGNED_LONGS_EQUAL(0, emptyCluster.size());
}

TEST(SingleClusterGenerator, CreatesTheRightAmountOfPoints)
{
    const size_t expected_count = 42;
    description.points_count = expected_count;
    const auto cluster = generateCluster(description);

    UNSIGNED_LONGS_EQUAL(expected_count, cluster.size());
}

