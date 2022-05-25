#include "Polygon.h"
#include "Point.h"
#include "Circle.h"
#include "Reuleaux.h"
#include "Geom.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
#define FAKE_NUMBER 696969



Polygon::Polygon(std::vector<Point> vertices)
{
    for (auto i = vertices.begin(); i != vertices.end(); i++) {
        vrtis_.push_back(Point(i->x, i->y));
    }
}

bool Polygon::ContainedBy(Circle &circle)
{
    bool x = true;
    for (unsigned int i = 0; i < this->vrtis_.size(); i += 1) {
        double dis = Geom::sep(Point(this->vrtis_.at(i).x, this->vrtis_.at(i).y), circle.Center());
        if (dis <= circle.Radius()) {
            x = true;
            break;
        }
        else {
            x = false;
            break;
        }
    }
    return x;
}

bool Polygon::ContainedBy(Polygon &polygon)
{
    bool x = false;
    for (unsigned int i = 0; i < vrtis().size(); i++) {
        if (vrtis().size() != polygon.vrtis().size()) {
            x = false;
            break;
        }
        if ((vrtis().at(i).x == polygon.vrtis().at(i).x) and ((vrtis().at(i).y == polygon.vrtis().at(i).y)) ) {
            x = true;
        }
    }
    if (x == true) {
        return true;
    }
    for (unsigned int i = 0; i < vrtis().size()-1; i++) {
        for (unsigned int j = 0; j < polygon.vrtis().size()-1; j++) {
            Point Inter = Geom::intersection(this->vrtis().at(i), this->vrtis().at(i+1), polygon.vrtis().at(j), polygon.vrtis().at(j+1));
            if (Inter.x != FAKE_NUMBER) {
                if (this->vrtis().at(i).x == Inter.x and this->vrtis().at(i).y == Inter.y) {
                    bool in = Geom::inPoly(polygon.vrtis(), this->vrtis().at(i+1));
                    if (in == false) {
                        return false;
                    }
                }
                else if (this->vrtis().at(i+1).x == Inter.x and this->vrtis().at(i+1).y == Inter.y) {
                    bool in = Geom::inPoly(polygon.vrtis(), this->vrtis().at(i));
                    if (in == false) {
                        return false;
                    }
                }
                else {
                    return false;
                }
            }
        }
    }
    bool in = Geom::inPoly(polygon.vrtis(), this->vrtis().at(1));
    if (in == true) {
        return true;
    }
    else {
        return false;
    }
}

bool Polygon::ContainedBy(ReuleauxTriangle &rt)
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

std::vector<Point> Polygon::vrtis()
{
    return vrtis_;
}
