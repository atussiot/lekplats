#include <van_eck_sequence.h>

#include <numeric>

#include <CppUTest/TestHarness.h>

TEST_GROUP(VanEck) {
    // TODO: would be nice to iterate through some values to catch odd cases
    const int iterations = 1239;
    const int n0 = 0;
    std::map<int, ValInfo> S;
    void setup() { S = generate_van_eck_seq_stats(iterations, n0); }
};

// True only for N > x, or maybe zero should not be taken into account?
// TODO: figure out x
TEST(VanEck, cannotProduceMoreNewValuesThanHalfTheNumberOfIterations)
{ CHECK(S.size() <= iterations / 2); }

TEST(VanEck, numberOfZerosIsConsistentWithNumberOfValuesEncountered) {
    const auto zero = S.at(0);
    int expected_size = zero.count - 1; // The first zero occurrence counts itself

    // Depends on the last value, if it was new then the following zero was not added...
    const auto last_idx = iterations - 1;
    const auto new_last = std::find_if(S.begin(), S.end(),
                                       [&last_idx] (const std::map<int, ValInfo>::value_type& val)
                                       {
                                           const auto is_new = val.second.count == 1;
                                           const auto is_last = val.second.last == last_idx;
                                           return is_new && is_last;
                                       }); 
    if (new_last != S.end()) ++expected_size;

    UNSIGNED_LONGS_EQUAL(expected_size, S.size());
}

TEST(VanEck, sumOfCountsMustEqualNumberOfIterations) {
    const auto sum = std::accumulate(S.begin(), S.end(), 0,
                                     [] (int val, const std::map<int, ValInfo>::value_type& p)
                                     { return val + p.second.count; });
    UNSIGNED_LONGS_EQUAL(iterations, sum);
}

TEST(VanEck, firstMissingValueIsActuallyNotFoundWhileAllPreviousValuesAre) {
    const auto first_missing = first_missing_value(S);
    CHECK(S.find(first_missing) == S.end());
    for (int i = 0; i < first_missing; ++i) { CHECK(S.find(i) != S.end()); }
}

