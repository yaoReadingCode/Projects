#include "Reuleaux.h"
#include <gtest/gtest.h>
#include "Polygon.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

TEST(PolygonReuleaux, Contained)
{
  std::vector <Point> vts;
  vts.push_back(Point(-5.0, 0.0));
  vts.push_back(Point(-4.0, 6.0));
  vts.push_back(Point(0.0, 10.0));
  vts.push_back(Point(4.0, 6.0));
  vts.push_back(Point(4.0, 2.0));
  vts.push_back(Point(0.0, 0.0));

  Point vertices[3];
  vertices[0] = Point(-8.0, -2.0);
  vertices[1] = Point(8.0, -2.0);
  vertices[2] = Point(0.0, 11.9);

  ReuleauxTriangle outer = ReuleauxTriangle(vertices);
  Polygon inner = Polygon(vts);
  ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(PolygonReuleaux, Touches_Inside)
{
  std::vector <Point> vts;
  vts.push_back(Point(0.0, -2.0));
  vts.push_back(Point(-8.0, -2.0));
  vts.push_back(Point(0.0, 11.9));
  vts.push_back(Point(4.0, 6.0));
  vts.push_back(Point(4.0, 2.0));
  vts.push_back(Point(8.0, -2.0));

  Point vertices[3];
  vertices[0] = Point(-8.0, -2.0);
  vertices[1] = Point(8.0, -2.0);
  vertices[2] = Point(0.0, 11.9);

  ReuleauxTriangle outer = ReuleauxTriangle(vertices);
  Polygon inner = Polygon(vts);
  ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(PolygonReuleaux, Intersects)
{
  std::vector <Point> vts;
  vts.push_back(Point(0.0, -8.0));
  vts.push_back(Point(-8.0, -2.0));
  vts.push_back(Point(0.0, 11.9));
  vts.push_back(Point(4.0, 6.0));
  vts.push_back(Point(10.0, 6.0));
  vts.push_back(Point(8.0, -2.0));

  Point vertices[3];
  vertices[0] = Point(-8.0, -2.0);
  vertices[1] = Point(8.0, -2.0);
  vertices[2] = Point(0.0, 11.9);

  ReuleauxTriangle outer = ReuleauxTriangle(vertices);
  Polygon inner = Polygon(vts);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonReuleaux, Touches_Outside)
{
  std::vector <Point> vts;
  vts.push_back(Point(0.0, -15.0));
  vts.push_back(Point(-6.0, -8.0));
  vts.push_back(Point(-8.0, -2.0));
  vts.push_back(Point(-4.0, -6.0));
  vts.push_back(Point(4.0, -6.0));
  vts.push_back(Point(8.0, -2.0));

  Point vertices[3];
  vertices[0] = Point(-8.0, -2.0);
  vertices[1] = Point(8.0, -2.0);
  vertices[2] = Point(0.0, 11.9);

  ReuleauxTriangle outer = ReuleauxTriangle(vertices);
  Polygon inner = Polygon(vts);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonReuleaux, Outside)
{
  std::vector <Point> vts;
  vts.push_back(Point(0.0, -15.0));
  vts.push_back(Point(-6.0, -8.0));
  vts.push_back(Point(-8.0, -4.0));
  vts.push_back(Point(-4.0, -6.0));
  vts.push_back(Point(4.0, -6.0));
  vts.push_back(Point(10.0, -4.0));

  Point vertices[3];
  vertices[0] = Point(-8.0, -2.0);
  vertices[1] = Point(8.0, -2.0);
  vertices[2] = Point(0.0, 11.9);

  ReuleauxTriangle outer = ReuleauxTriangle(vertices);
  Polygon inner = Polygon(vts);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonReuleaux, Surrounds)
{
  std::vector <Point> vts;
  vts.push_back(Point(8.0, -2.0));
  vts.push_back(Point(0.0, -10.0));
  vts.push_back(Point(-10.0, 0.0));
  vts.push_back(Point(-10.0, 10.0));
  vts.push_back(Point(0.0, 20.0));
  vts.push_back(Point(10.0, 10.0));

  Point vertices[3];
  vertices[0] = Point(-8.0, -2.0);
  vertices[1] = Point(8.0, -2.0);
  vertices[2] = Point(0.0, 11.9);

  ReuleauxTriangle outer = ReuleauxTriangle(vertices);
  Polygon inner = Polygon(vts);
  ASSERT_FALSE(inner.ContainedBy(outer));
}