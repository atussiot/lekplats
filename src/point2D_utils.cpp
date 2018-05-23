#include <point2D_utils.h>

#include <cmath>

bool operator== (const Point2D& a, const Point2D& b)
{
    return (a.x == b.x) && (a.y == b.y);
}

double squaredEuclidianDistance(const Point2D& a, const Point2D& b)
{
    return std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2);
}

