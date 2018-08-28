#include <chaos_game.h>

#include <cmath>
#include <random>

std::vector<std::complex<double>> regular_polygon_vertices(const size_t verticesCount);
bool isNextTargetValid(size_t targetsCount, size_t previousIndex, size_t newIndex);

std::vector<std::complex<double>> chaos_game(const size_t pointsCount, const size_t verticesCount)
{
    const auto vertices = regular_polygon_vertices(verticesCount);

    std::vector<std::complex<double>> points;
    points.reserve(pointsCount);

    std::complex<double> currentPosition{ 0.42, 0.57 }; // TODO: Initialize randomly?

    std::random_device rd;
    std::mt19937 generator{ rd() };
    std::uniform_int_distribution<size_t> dist{ 0, verticesCount - 1 };

    size_t n = 0;
    size_t previousSelection = verticesCount + 1;

    while (n < pointsCount)
    {
        const auto index = dist(generator);
        if (!isNextTargetValid(verticesCount, previousSelection, index)) continue;

        const auto selectedVertex = vertices[index];
        const auto direction = selectedVertex - currentPosition;
        currentPosition += 0.5 * direction;

        points.push_back(currentPosition);
        previousSelection = index;
        ++n;
    }

    return points;
}

// Below: implementation details, but would be good candidates for unit testing

std::vector<std::complex<double>> regular_polygon_vertices(const size_t verticesCount)
{
    std::vector<std::complex<double>> vertices;
    vertices.reserve(verticesCount);

    static const double PI = std::acos(-1.0);
    const double angle = 2.0 * PI / static_cast<double>(verticesCount);

    for (size_t i = 0; i < verticesCount; ++i)
    {
        vertices.emplace_back(std::polar(1.0, static_cast<double>(i) * angle));
    }

    return vertices;
}

bool isNextTargetValid(size_t targetsCount, size_t previousIndex, size_t newIndex)
{
    // TODO: Allow to choose among different strategies here
    auto forbiddenIndex = previousIndex;
    if (forbiddenIndex >= targetsCount)
    {
        forbiddenIndex %= targetsCount;
    }

    return newIndex != forbiddenIndex;
}

