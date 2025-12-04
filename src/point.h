#ifndef POINT_H
#define POINT_H

struct Point
{
    double x;
    double y;
};

Point operator+=(Point lhs, Point rhs);

Point operator*=(Point p, double d);

#endif