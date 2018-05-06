#pragma once

struct Point2D
{
    double x, y;

    Point2D(double x = 0.0, double y = 0.0) : x(x), y(y) { }

    Point2D& operator+= (const Point2D& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Point2D& operator /= (double value)
    {
        x /= value;
        y /= value;
        return *this;
    }
};

