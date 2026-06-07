#include "point.h"


Point::Point()
    : _x(0), _y(0)
{
}


Point::Point(unsigned x, unsigned y)
    : _x(x), _y(y) //lista inicjalizacyjna zamiast _x = x
{
}

unsigned Point::x() const
{
    return _x;
}

unsigned Point::y() const
{
    return _y;
}
