#include "Circle.h"
#include "Geom.h"
#include "Polygon.h"
#include "Reuleaux.h"
#include <cmath>
#include <iostream>

using namespace std;

Circle::Circle(const Point &center, double radius)
{
    center_ = Point(center);
    radius_ = radius;
}

//
// contained if distance between centers is less than or equal to
// difference in radius
bool Circle::ContainedBy(Circle &circle)
{
    return Geom::sep(circle.Center(), Center()) <= (circle.Radius() - Radius());
}

// Code for this came from https://www.geeksforgeeks.org/check-line-touches-intersects-circle/
bool Circle::ContainedBy(Polygon &polygon)
{
    bool x = true;
    Point g = this->Center();
    bool in = Geom::inPoly(polygon.vrtis(), g);
    if (in == false) {
        return false;
    }
    for (unsigned int j = 0; j < polygon.vrtis().size()-1; j++) {
        g = this->Center();
        double dist = Geom::mth(polygon.vrtis().at(j), polygon.vrtis().at(j+1), g);
        if (this->Radius() > dist) {
            x = false;
        }
        else if ((this->Radius() < dist)){
            in = Geom::inPoly(polygon.vrtis(), g);
            if (in != false) {
                return true;
            }
        }
    }
    return x;
}

bool Circle::ContainedBy(ReuleauxTriangle &rt)
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

Point Circle::Center()
{
    return Point(center_);
}

double Circle::Radius()
{
    return radius_;
}