#pragma once

#include <array>

struct Point2D
{
    std::array<double, 2> data;

    Point2D(double x = 0.0, double y = 0.0)
        : data { x, y }
    { }

    const double operator [] (const size_t i) const { return data[i]; }

    Point2D& operator+= (const Point2D& other)
    {
        for (size_t i = 0; i < this->data.size(); ++i)
        {
            this->data[i] += other[i];
        }
        return *this;
    }

    Point2D& operator /= (double div)
    {
        for (auto& value : data)
        {
            value /= div;
        }
        return *this;
    }
};

