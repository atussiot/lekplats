#include <point2D_utils.h>

#include <cmath>

bool operator== (const Point2D& a, const Point2D& b)
{
    return a.data == b.data;
}

Point2D operator-(const Point2D& a, const Point2D& b)
{
    Point2D c;
    for (size_t i = 0; i < a.data.size(); ++i)
    {
        c.data[i] = a[i] - b[i];
    }
    return c;
}

Point2D operator*(const double coef, const Point2D& point)
{
    Point2D point_out;
    for (size_t i = 0; i < point.data.size(); ++i)
    {
        point_out.data[i] = coef * point[i];
    }
    return point_out;
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

