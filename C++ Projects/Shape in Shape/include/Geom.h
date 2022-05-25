#include <cmath>
#include "Point.h"
#include <iostream>
#include <vector>
//#include "Circle.h"

class Geom {
    public:
        static double sep(const Point &a, const Point &b);
        static Point intersection(const Point &a, const Point &b, const Point &c, const Point &d);
        static bool inPoly(const std::vector<Point> vertices, Point &a);
        static double mth(const Point &u, const Point &v, const Point &center);
};

