#include "path.h"


void Path::add(Point p)
{
    _points.add(p);
}


void Path::clear()
{
    _points.clear();
}


unsigned Path::length() const
{
    return _points.size();
}


Point Path::operator[](unsigned i) const
{
    return _points[i]; // DynamicArray rzuci wyjatek jesli i >= length()
}


std::ostream& operator<<(std::ostream& out, const Path& p)
{
    for (unsigned i = 0; i < p.length(); i++)
    {
        out << "(" << p[i].x() << "," << p[i].y() << ")";


        if (i < p.length() - 1)
        {
            out << " -> ";
        }
    }

    return out;
}
