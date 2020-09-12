#include <chaos_game.h>

#include <CppUTest/TestHarness.h>

TEST_GROUP(NextSelectedVertex)
{
    ChaosGame game;
    static constexpr bool CLOCKWISE = true;
    static constexpr size_t PREVIOUS_INDEX = 4;

    void checkAllIndices(size_t restrictedIndex)
    {
        for (size_t nextIndex = 0; nextIndex < game.polygonSize; ++nextIndex)
        {
            const auto indexIsRestricted = nextIndex != restrictedIndex;
            CHECK_EQUAL(indexIsRestricted, isNextTargetValid(&game, PREVIOUS_INDEX, nextIndex));
        }
    }
};

TEST(NextSelectedVertex, IsAlwaysValidWhenThereIsNoRestriction)
{
    game.restriction = Restriction::None;
    const auto restrictedIndex = game.polygonSize;
    checkAllIndices(restrictedIndex);
}

TEST(NextSelectedVertex, IsValidIfDifferentThanRestrictedPreviousIndex)
{
    game.restriction = Restriction::Previous;
    const auto restrictedIndex = PREVIOUS_INDEX;
    checkAllIndices(restrictedIndex);
}

TEST(NextSelectedVertex, IsValidIfDifferentThanRestrictedNextAntiClockwise)
{
    game.restriction = Restriction::NextAntiClockwise;
    const size_t restrictedIndex = getNextIndex(game.polygonSize, PREVIOUS_INDEX, !CLOCKWISE);
    checkAllIndices(restrictedIndex);
}

TEST(NextSelectedVertex, IsValidIfDifferentThanRestrictedNextClockwise)
{
    game.restriction = Restriction::NextClockwise;
    const auto restrictedIndex = getNextIndex(game.polygonSize, PREVIOUS_INDEX, CLOCKWISE);
    checkAllIndices(restrictedIndex);
}

TEST(NextSelectedVertex, IsValidIfDifferentThanRestrictedSecondNextClockwise)
{
    game.restriction = Restriction::SecondNextClockwise;
    const auto restrictedIndex = getSecondNextIndex(game.polygonSize, PREVIOUS_INDEX, CLOCKWISE);
    checkAllIndices(restrictedIndex);
}

TEST(NextSelectedVertex, NewIndexIsActuallyTheNextOneClockwise)
{
    const auto index = 2;
    const auto nextIndex = getNextIndex(game.polygonSize, index, CLOCKWISE);
    CHECK_EQUAL(1, nextIndex);
}

TEST(NextSelectedVertex, NewIndexIsActuallyTheNextOneClockwiseAtZero)
{
    const auto index = 0;
    const auto nextIndex = getNextIndex(game.polygonSize, index, CLOCKWISE);
    CHECK_EQUAL(game.polygonSize - 1, nextIndex);
}

TEST(NextSelectedVertex, NewIndexIsActuallyTheNextOneAnticlockwise)
{
    const auto index = 2;
    const auto nextIndex = getNextIndex(game.polygonSize, index, !CLOCKWISE);
    CHECK_EQUAL(3, nextIndex);
}

TEST(NextSelectedVertex, NewIndexIsActuallyTheNextOneAnticlockwiseAtLastIndex)
{
    const auto index = game.polygonSize - 1;
    const auto nextIndex = getNextIndex(game.polygonSize, index, !CLOCKWISE);
    CHECK_EQUAL(0, nextIndex);
}

TEST(NextSelectedVertex, NewIndexIsActuallyTheSecondNextOneClockwiseAtZero)
{
    const auto index = 0;
    const auto nextIndex = getSecondNextIndex(game.polygonSize, index, CLOCKWISE);
    CHECK_EQUAL(game.polygonSize - 2, nextIndex);
}

TEST(NextSelectedVertex, NewIndexIsActuallyTheSecondNextOneClockwiseAtLastIndex)
{
    const auto index = game.polygonSize - 1;
    const auto nextIndex = getSecondNextIndex(game.polygonSize, index, CLOCKWISE);
    CHECK_EQUAL(game.polygonSize - 3, nextIndex);
}

