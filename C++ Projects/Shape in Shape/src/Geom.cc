#include "Geom.h"
#include <cmath>
#include <iostream>

#define FAKE_NUMBER 696969

using namespace std;

// Code gotten from
// Professor Harisson
double Geom::sep(const Point &a, const Point &b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// Code gotten from
// https://www.geeksforgeeks.org/program-for-point-of-intersection-of-two-lines/
Point Geom::intersection(const Point &a, const Point &b, const Point &c, const Point &d) {
    // First line; line ab
    double a1 = b.y - a.y;
    double b1 = a.x - b.x;
    double c1 = (a1*a.x) + (b1*a.y);

    // Second line; line cd
    double a2 = d.y - c.y;
    double b2 = c.x - d.x;
    double c2 = (a2*c.x) + (b2*c.y);

    double determinant = (a1*b2) - (a2*b1);

    if (determinant == 0) {
        return Point(FAKE_NUMBER, FAKE_NUMBER);
    }
    else {
        double xt = ((b2*c1) - (b1*c2))/determinant;
        double yt = ((a1*c2) - (a2*c1))/determinant;
        // checks if point is on both lines
        if (xt >= std::min(a.x, b.x) and xt <= std::max(a.x, b.x)
        and yt >= std::min(a.y, b.y) and yt <= std::max(a.y, b.y)
        and xt >= std::min(c.x, d.x) and xt <= std::max(c.x, d.x)
        and yt >= std::min(c.y, d.y) and yt <= std::max(c.y, d.y)) {
            
            return Point(xt, yt);
        }
        else {
            return Point(FAKE_NUMBER, FAKE_NUMBER); 
        }
    }
}

// Code gotten from https://wrf.ecse.rpi.edu/Research/Short_Notes/pnpoly.html
bool Geom::inPoly(const std::vector<Point> vertices, Point &a)
{
    bool in = false;
    unsigned int i = 0;
    unsigned int j = vertices.size() -1;
    for (i = 0; i < vertices.size(); j = i++) {
        if ( ((vertices[i].y > a.y) != (vertices[j].y > a.y)) &&
        (a.x < (vertices[j].x - vertices[i].x) * (a.y - vertices[i].y) / (vertices[j].y - vertices[i].y) + vertices[i].x) ) {

            in = not in;
        }
    }
    return in;
}

double Geom::mth(const Point &u, const Point &v, const Point &center)
{
    double a = u.y - v.y;
    double b = v.x - u.x;
    double c = ((u.x - v.x)*u.y) + (u.x*(v.y - u.y));
    double dist = (abs((a * center.x) + (b * center.y) + c)) / sqrt(a * a + b * b);
    return dist;
}