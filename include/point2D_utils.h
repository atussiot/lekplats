#pragma once
#include <point2D.h>

#include <functional>

// Needed these to help the compiler with std::unordered_set<Point2D>
bool operator== (const Point2D& a, const Point2D& b);
namespace std {

template<>
struct hash<Point2D>
{
    size_t operator() (const Point2D& p) const
    {
        size_t ret = 0;
        for (const auto value : p.data)
        {
            ret ^= std::hash<double>()(value);
        }
        return ret;
    }
};

}

// Other useful functions
Point2D operator-(const Point2D& a, const Point2D& b);
Point2D operator*(const double, const Point2D& point);
double squaredEuclidianDistance(const Point2D& a, const Point2D& b);

