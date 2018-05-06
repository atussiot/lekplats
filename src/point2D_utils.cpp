#include <point2D_utils.h>

bool operator== (const Point2D& a, const Point2D& b)
{
    return (a.x == b.x) && (a.y == b.y);
}
