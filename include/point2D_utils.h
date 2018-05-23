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
        return std::hash<double>()(p.x) ^ std::hash<double>()(p.y);
    }
};

}

// Other useful functions
double squaredEuclidianDistance(const Point2D& a, const Point2D& b);

