#include <point2D_utils.h>

#include <cmath>

bool operator== (const Point2D& a, const Point2D& b)
{
    return a.data == b.data;
}

double squaredEuclidianDistance(const Point2D& a, const Point2D& b)
{
    double dist = 0.0;
    for (size_t i = 0; i < a.data.size(); ++i)
    {
        dist += std::pow(a[i] - b[i], 2);
    }
    return dist;
}

