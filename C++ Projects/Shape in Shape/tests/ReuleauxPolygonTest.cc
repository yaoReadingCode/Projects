#include "Polygon.h"
#include <gtest/gtest.h>
#include "Reuleaux.h"

TEST(ReuleauxPolygon, Contained)
{
  Point vertices[3];
  vertices[0] = Point(-4.0, -4.0);
  vertices[1] = Point(4.0, -4.0);
  vertices[2] = Point(0.0, 2.9);

  std::vector <Point> vts;
  vts.push_back(Point(0.0, 6.0));
  vts.push_back(Point(8.0, -4.0));
  vts.push_back(Point(6.0, -10.0));
  vts.push_back(Point(-8.0, -4.0));
  vts.push_back(Point(-4.0, 2.0));

  Polygon outer = Polygon(vts);
  ReuleauxTriangle inner = ReuleauxTriangle(vertices);
  ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(ReuleauxPolygon, Touches_Inside)
{
  Point vertices[3];
  vertices[0] = Point(-1.0, -1.0);
  vertices[1] = Point(3.0, -4.0);
  vertices[2] = Point(3.6, 1.0);

  std::vector <Point> vts;
  vts.push_back(Point(0.0, 6.0));
  vts.push_back(Point(4.0, 2.0));
  vts.push_back(Point(4.0, -6.0));
  vts.push_back(Point(-6.0, -8.0));
  vts.push_back(Point(-4.0, 2.0));

  Polygon outer = Polygon(vts);
  ReuleauxTriangle inner = ReuleauxTriangle(vertices);
  ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(ReuleauxPolygon, Intersect)
{
  Point vertices[3];
  vertices[0] = Point(-1.0, -1.0);
  vertices[1] = Point(3.0, -4.0);
  vertices[2] = Point(3.6, 1.0);

  std::vector <Point> vts;
  vts.push_back(Point(0.0, 6.0));
  vts.push_back(Point(4.0, 2.0));
  vts.push_back(Point(3.0, -5.0));
  vts.push_back(Point(-6.0, -8.0));
  vts.push_back(Point(-4.0, 2.0));

  Polygon outer = Polygon(vts);
  ReuleauxTriangle inner = ReuleauxTriangle(vertices);
  ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(ReuleauxPolygon, Touches_Outside)
{
  Point vertices[3];
  vertices[0] = Point(-1.0, -1.0);
  vertices[1] = Point(3.0, -4.0);
  vertices[2] = Point(3.6, 1.0);

  std::vector <Point> vts;
  vts.push_back(Point(6.0, 4.0));
  vts.push_back(Point(10.0, -2.0));
  vts.push_back(Point(6.0, -8.0));
  vts.push_back(Point(4.0, -5.0));
  vts.push_back(Point(4.0, 2.0));

  Polygon outer = Polygon(vts);
  ReuleauxTriangle inner = ReuleauxTriangle(vertices);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxPolygon, Surrounds)
{
  Point vertices[3];
  vertices[0] = Point(-1.0, -1.0);
  vertices[1] = Point(3.0, -4.0);
  vertices[2] = Point(3.6, 1.0);

  std::vector <Point> vts;
  vts.push_back(Point(1.0, 0.0));
  vts.push_back(Point(0.0, -1.0));
  vts.push_back(Point(-1.0, -1.0));
  vts.push_back(Point(2.0, -1.0));

  Polygon outer = Polygon(vts);
  ReuleauxTriangle inner = ReuleauxTriangle(vertices);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxPolygon, Coincident)
{
  Point vertices[3];
  vertices[0] = Point(-1.0, -1.0);
  vertices[1] = Point(3.0, -4.0);
  vertices[2] = Point(3.6, 1.0);

  std::vector <Point> vts;
  vts.push_back(Point(-1.0, -1.0));
  vts.push_back(Point(3.0, -4.0));
  vts.push_back(Point(3.6, 1.0));

  Polygon outer = Polygon(vts);
  ReuleauxTriangle inner = ReuleauxTriangle(vertices);
  ASSERT_FALSE(inner.ContainedBy(outer));
}