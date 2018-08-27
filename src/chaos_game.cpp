#include <chaos_game.h>

#include <point2D_utils.h>

#include <complex>
#include <random>

std::vector<Point2D> get_corners(const Point2D& center, const double radius,
                                 const size_t cornersCount);
bool isNextTargetValid(size_t targetsCount, size_t previousIndex, size_t newIndex);

std::vector<Point2D> chaos_game()
{
    // TODO: These two can be parameters
    size_t iterations = 500000;
    const size_t cornersCount = 5;

    // XXX: Values picked to match the final image geometry, should disappear
    const double radius = 1280.0;
    const Point2D center{ radius, radius };
    const auto corners = get_corners(center, radius, cornersCount);

    std::vector<Point2D> points;
    points.reserve(iterations);

    Point2D currentPosition{ 42.0, 57.0 }; // TODO: Initialize randomly? 

    std::random_device rd;
    std::mt19937 generator{ rd() };
    std::uniform_int_distribution<size_t> dist{ 0, cornersCount - 1 };

    size_t n = 0;
    size_t previousSelection = cornersCount + 1;

    while (n < iterations)
    {
        const auto index = dist(generator);
        if (!isNextTargetValid(cornersCount, previousSelection, index)) continue;

        const auto selectedCorner = corners[index];
        const auto direction = selectedCorner - currentPosition;
        currentPosition += 0.5 * direction;

        points.push_back(currentPosition);
        previousSelection = index;
        ++n;
    }

    return points;
}

// Below: implementation details, but would be good candidates for unit testing

std::vector<Point2D> get_corners(const Point2D& center, const double radius,
                                 const size_t cornersCount)
{
    std::vector<Point2D> corners;
    corners.reserve(cornersCount);

    static constexpr double PI = 3.141592653589793238463;
    const double angle = 2.0 * PI / static_cast<double>(cornersCount);

    for (size_t i = 0; i < cornersCount; ++i)
    {
        // TODO: the half pi correction is to make it "point up". Works, but should not be done
        // here (it's a rendering issue after all)
        const auto cornerCmplx = std::polar(radius, static_cast<double>(i) * angle - PI * 0.5);
        // TODO: Would be better to just work on the unit circle and scale later
        // In fact, would be better to work with complex numbers everywhere here
        Point2D corner { cornerCmplx.real(), cornerCmplx.imag() };
        corner += center;
        corners.push_back(corner);
    }

    return corners;
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

