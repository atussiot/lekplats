#include <chaos_game.h>

#include <point2D_utils.h>

#include <complex>
#include <random>

std::vector<Point2D> regular_polygon_vertices(const Point2D& center, const double radius,
                                              const size_t verticesCount);
bool isNextTargetValid(size_t targetsCount, size_t previousIndex, size_t newIndex);

std::vector<Point2D> chaos_game(const size_t pointsCount, const size_t verticesCount)
{
    // XXX: Values picked to match the final image geometry, should disappear
    const double radius = 1280.0;
    const Point2D center{ radius, radius };
    const auto vertices = regular_polygon_vertices(center, radius, verticesCount);

    std::vector<Point2D> points;
    points.reserve(pointsCount);

    Point2D currentPosition{ 42.0, 57.0 }; // TODO: Initialize randomly? 

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

std::vector<Point2D> regular_polygon_vertices(const Point2D& center, const double radius,
                                              const size_t verticesCount)
{
    std::vector<Point2D> vertices;
    vertices.reserve(verticesCount);

    static constexpr double PI = 3.141592653589793238463;
    const double angle = 2.0 * PI / static_cast<double>(verticesCount);

    for (size_t i = 0; i < verticesCount; ++i)
    {
        // TODO: the half pi correction is to make it "point up". Works, but should not be done
        // here (it's a rendering issue after all)
        const auto vertexCmplx = std::polar(radius, static_cast<double>(i) * angle - PI * 0.5);
        // TODO: Would be better to just work on the unit circle and scale later
        // In fact, would be better to work with complex numbers everywhere here
        Point2D vertex { vertexCmplx.real(), vertexCmplx.imag() };
        vertex += center;
        vertices.push_back(vertex);
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

