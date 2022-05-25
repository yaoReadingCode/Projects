#include "Reuleaux.h"
#include "Circle.h"
#include "Geom.h"
#include "Polygon.h"
#include "Point.h"
#include <cmath>
#include <iostream>
using namespace std;


ReuleauxTriangle::ReuleauxTriangle(const Point vertices[3])
{
    v1_ = Point(vertices[0]);
    v2_ = Point(vertices[1]);
    v3_ = Point(vertices[2]);
}

bool ReuleauxTriangle::ContainedBy(Circle &circle)
{
    bool x = true;
    double d1 = Geom::sep(circle.Center(), v1());
    double d2 = Geom::sep(circle.Center(), v2());
    double d3 = Geom::sep(circle.Center(), v3());
    double rd = Geom::sep(v1(), v2());

    if (d1 <= circle.Radius()
    and d2 <= circle.Radius()
    and d3 <= circle.Radius()) {
        Point centroid = Point(((v1().x + v2().x + v3().x)/3), ((v1().y + v2().y + v3().y)/3));
        double dc = Geom::sep(circle.Center(), centroid);
        double half = Geom::sep(v1(), centroid);
        double remainder = rd - half;
        if ((dc + remainder) <= circle.Radius()) {
            x = true;
        }
    }
    else {
        x = false;
    }
    return x;
}

bool ReuleauxTriangle::ContainedBy(Polygon &polygon)
{
    Point n1 = v1();
    Point n2 = v2();
    Point n3 = v3();
    bool in = Geom::inPoly(polygon.vrtis(), n1);
    in = Geom::inPoly(polygon.vrtis(), n2);
    in = Geom::inPoly(polygon.vrtis(), n3);
    if (in == false) {
        return false;
    }
    else {
        return true;
    }
}

bool ReuleauxTriangle::ContainedBy(ReuleauxTriangle &rt)
{
    double rd = Geom::sep(rt.v1(), rt.v2());
    Circle c1 = Circle(rt.v1(), rd);
    Circle c2 = Circle(rt.v2(), rd);
    Circle c3 = Circle(rt.v3(), rd);
    if (this->ContainedBy(c1) and this->ContainedBy(c2) and this->ContainedBy(c3)) {
        return true;
    }
    else {
        return false;
    }
}

Point ReuleauxTriangle::v1()
{
    return Point(v1_);
}

Point ReuleauxTriangle::v2()
{
    return Point(v2_);
}

Point ReuleauxTriangle::v3()
{
    return Point(v3_);
}


