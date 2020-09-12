#include <chaos_game.h>

#include <cmath>

std::vector<std::complex<double>> ChaosGame::generate_points()
{
    const auto vertices = regular_polygon_vertices(polygonSize);

    std::vector<std::complex<double>> points;
    points.reserve(pointsCount);

    std::complex<double> currentPosition = get_random();

    std::uniform_int_distribution<size_t> dist{ 0, polygonSize - 1 };

    size_t n = 0;
    size_t previousSelection = polygonSize + 1;

    while (n < pointsCount)
    {
        const auto index = dist(_generator);
        if (!isNextTargetValid(this, previousSelection, index)) continue;

        const auto selectedVertex = vertices[index];
        const auto direction = selectedVertex - currentPosition;
        currentPosition += fraction * direction;

        points.push_back(currentPosition);
        previousSelection = index;
        ++n;
    }

    return points;
}

std::complex<double> ChaosGame::get_random()
{
    std::uniform_real_distribution<> dist{ -1.0, 1.0 };
    return std::complex<double>{ dist(_generator), dist(_generator) };
}

std::vector<std::complex<double>> regular_polygon_vertices(const size_t polygonSize)
{
    std::vector<std::complex<double>> vertices;
    vertices.reserve(polygonSize);

    static const double PI = std::acos(-1.0);
    const double angle = 2.0 * PI / static_cast<double>(polygonSize);

    for (size_t i = 0; i < polygonSize; ++i)
    {
        vertices.emplace_back(std::polar(1.0, static_cast<double>(i) * angle));
    }

    return vertices;
}

size_t getNextIndex(const size_t polygonSize, const size_t index, const bool clockwise)
{
    auto nextIndex = index + (clockwise ? polygonSize - 1 : 1);
    if (nextIndex >= polygonSize) nextIndex %= polygonSize; // Adjust in case we looped
    return nextIndex;
}

size_t getSecondNextIndex(const size_t polygonSize, const size_t index, const bool clockwise)
{
    auto secondNext = index + (clockwise ? polygonSize - 2 : 2);
    if (secondNext >= polygonSize) secondNext %= polygonSize; // Adjust in case we looped
    return secondNext;
}

bool isNextTargetValid(const ChaosGame* game, const size_t previousIndex, const size_t newIndex)
{
    size_t forbiddenIndex;
    constexpr bool CLOCKWISE = true;
    switch (game->restriction)
    {
    case Restriction::None:
        return true;
    case Restriction::Previous:
        forbiddenIndex = previousIndex;
        break;
    case Restriction::NextAntiClockwise:
        forbiddenIndex = getNextIndex(game->polygonSize, previousIndex, !CLOCKWISE);
        break;
    case Restriction::NextClockwise:
        forbiddenIndex = getNextIndex(game->polygonSize, previousIndex, CLOCKWISE);
        break;
    case Restriction::SecondNextClockwise:
        forbiddenIndex = getSecondNextIndex(game->polygonSize, previousIndex, CLOCKWISE);
        break;
    }

    return newIndex != forbiddenIndex;
}

