#include <chaos_game.h>

#include <point2D_utils.h>

#include <random>

std::vector<Point2D> get_corners(const size_t cornersCount)
{
    std::vector<Point2D> corners;
    corners.reserve(cornersCount);

    // TODO: Implement this properly
    corners.push_back(Point2D(0.0, 0.0));
    corners.push_back(Point2D(480.0, 0.0));
    corners.push_back(Point2D(0.0, 480.0));

    return corners;
}

std::vector<Point2D> chaos_game()
{
    size_t iterations = 500000;
    const size_t cornersCount = 3;
    const auto corners = get_corners(cornersCount);

    std::vector<Point2D> points;
    points.reserve(iterations);

    Point2D currentPosition{ 42.0, 57.0 }; // TODO: Initialize randomly? 

    std::random_device rd;
    std::mt19937 generator{ rd() };
    std::uniform_int_distribution<size_t> dist{ 0, cornersCount - 1 };

    for (size_t n = 0; n < iterations; ++n)
    {
        const auto selectedCorner = corners[dist(generator)];
        const auto direction = selectedCorner - currentPosition;
        currentPosition += 0.5 * direction;

        points.push_back(currentPosition);
    }

    return points;
}
