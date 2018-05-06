#pragma once

#include <point2D.h>
#include <cstddef> // For size_t...

struct ClusterDescription
{
    ClusterDescription() : mean(Point2D{}), std_dev(Point2D{}), points_count(0) { }

    Point2D mean;
    Point2D std_dev;
    std::size_t points_count;
};

