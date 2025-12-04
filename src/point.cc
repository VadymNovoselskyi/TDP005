#include "point.h"

Point operator+=(Point lhs, Point rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}

Point operator*=(Point p, double d)
{
    p.x *= d;
    p.y *= d;
    return p;
}