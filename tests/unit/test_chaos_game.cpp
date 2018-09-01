#include <chaos_game.h>

#include <CppUTest/TestHarness.h>

TEST_GROUP(NextSelectedVertex)
{
    static constexpr size_t COUNT = 5;
    static constexpr Restriction NO_RESTRICTION = Restriction::None;
    static constexpr size_t PREVIOUS_INDEX = 2;
};

TEST(NextSelectedVertex, IsAlwaysValidWhenThereIsNoRestriction)
{
    for (size_t nextIndex = 0; nextIndex < COUNT; ++nextIndex)
        CHECK(isNextTargetValid(NO_RESTRICTION, COUNT, PREVIOUS_INDEX, nextIndex));
}

TEST(NextSelectedVertex, IsNotValidIfSameAsRestrictedPreviousIndex)
{
    constexpr size_t nextIndex = PREVIOUS_INDEX;
    CHECK_FALSE(isNextTargetValid(Restriction::Previous, COUNT, PREVIOUS_INDEX, nextIndex));
}

TEST(NextSelectedVertex, IsValidIfDifferentThanRestrictedPreviousIndex)
{
    for (size_t nextIndex = 0; nextIndex < COUNT; ++nextIndex)
        if (nextIndex != PREVIOUS_INDEX)
            CHECK(isNextTargetValid(Restriction::Previous, COUNT, PREVIOUS_INDEX, nextIndex));
}

TEST(NextSelectedVertex, IsNotValidIfNextAntiClockwiseToRestrictedPreviousIndex)
{
    constexpr auto restriction = Restriction::NextAntiClockwise;
    constexpr size_t nextIndex = PREVIOUS_INDEX + 1;
    CHECK_FALSE(isNextTargetValid(restriction, COUNT, PREVIOUS_INDEX, nextIndex));
}

TEST(NextSelectedVertex, IsValidIfDifferentThanRestrictedNextAntiClockwise)
{
    constexpr auto restriction = Restriction::NextAntiClockwise;
    for (size_t nextIndex = 0; nextIndex < COUNT; ++nextIndex)
        if (nextIndex != PREVIOUS_INDEX + 1)
            CHECK(isNextTargetValid(restriction, COUNT, PREVIOUS_INDEX, nextIndex));
}

TEST(NextSelectedVertex, IsNotValidIfNextClockwiseToRestrictedPreviousIndex)
{
    constexpr auto restriction = Restriction::NextClockwise;
    constexpr size_t nextIndex = PREVIOUS_INDEX - 1;
    CHECK_FALSE(isNextTargetValid(restriction, COUNT, PREVIOUS_INDEX, nextIndex));
}

TEST(NextSelectedVertex, IsValidIfDifferentThanRestrictedNextClockwise)
{
    constexpr auto restriction = Restriction::NextClockwise;
    for (size_t nextIndex = 0; nextIndex < COUNT; ++nextIndex)
        if (nextIndex != PREVIOUS_INDEX - 1)
            CHECK(isNextTargetValid(restriction, COUNT, PREVIOUS_INDEX, nextIndex));
}

