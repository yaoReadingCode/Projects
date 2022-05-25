#include "Reuleaux.h"
#include <gtest/gtest.h>
#include "Polygon.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

TEST(PolygonPolygon, Contained)
{
  std::vector <Point> vts1;
  vts1.push_back(Point(-5.0, 0.0));
  vts1.push_back(Point(-4.0, 6.0));
  vts1.push_back(Point(0.0, 10.0));
  vts1.push_back(Point(4.0, 6.0));
  vts1.push_back(Point(4.0, 2.0));
  vts1.push_back(Point(0.0, 0.0));

  std::vector <Point> vts2;
  vts2.push_back(Point(-3.0, 2.0));
  vts2.push_back(Point(-1.0, 6.0));
  vts2.push_back(Point(2.0, 5.0));
  vts2.push_back(Point(3.0, 2.0));
  vts2.push_back(Point(-1.0, 1.0));

  Polygon outer = Polygon(vts1);
  Polygon inner = Polygon(vts2);

  ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(PolygonPolygon, Touches_Inside)
{
  std::vector <Point> vts1;
  vts1.push_back(Point(-5.0, 0.0));
  vts1.push_back(Point(-4.0, 6.0));
  vts1.push_back(Point(0.0, 10.0));
  vts1.push_back(Point(4.0, 6.0));
  vts1.push_back(Point(4.0, 2.0));
  vts1.push_back(Point(0.0, 0.0));

  std::vector <Point> vts2;
  vts2.push_back(Point(-3.0, 2.0));
  vts2.push_back(Point(-2.0, 8.0));
  vts2.push_back(Point(2.0, 5.0));
  vts2.push_back(Point(3.0, 2.0));
  vts2.push_back(Point(-1.0, 1.0));

  Polygon outer = Polygon(vts1);
  Polygon inner = Polygon(vts2);

  ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(PolygonPolygon, Intersects)
{
  std::vector <Point> vts1;
  vts1.push_back(Point(-5.0, 0.0));
  vts1.push_back(Point(-4.0, 6.0));
  vts1.push_back(Point(0.0, 10.0));
  vts1.push_back(Point(4.0, 6.0));
  vts1.push_back(Point(4.0, 2.0));
  vts1.push_back(Point(0.0, 0.0));

  std::vector <Point> vts2;
  vts2.push_back(Point(-3.0, 2.0));
  vts2.push_back(Point(-2.0, 10.0));
  vts2.push_back(Point(2.0, 5.0));
  vts2.push_back(Point(3.0, 2.0));
  vts2.push_back(Point(-1.0, 1.0));

  Polygon outer = Polygon(vts1);
  Polygon inner = Polygon(vts2);

  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonPolygon, Touches_Outside)
{
  std::vector <Point> vts1;
  vts1.push_back(Point(-5.0, 0.0));
  vts1.push_back(Point(-4.0, 6.0));
  vts1.push_back(Point(0.0, 10.0));
  vts1.push_back(Point(4.0, 6.0));
  vts1.push_back(Point(4.0, 2.0));
  vts1.push_back(Point(0.0, 0.0));

  std::vector <Point> vts2;
  vts2.push_back(Point(-2.0, 12.0));
  vts2.push_back(Point(-1.0, 9.0));
  vts2.push_back(Point(-3.0, 8.0));
  vts2.push_back(Point(-5.0, 7.0));
  vts2.push_back(Point(-7.0, 9.0));

  Polygon outer = Polygon(vts1);
  Polygon inner = Polygon(vts2);

  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonPolygon, Outside)
{
  std::vector <Point> vts1;
  vts1.push_back(Point(-5.0, 0.0));
  vts1.push_back(Point(-4.0, 6.0));
  vts1.push_back(Point(0.0, 10.0));
  vts1.push_back(Point(4.0, 6.0));
  vts1.push_back(Point(4.0, 2.0));
  vts1.push_back(Point(0.0, 0.0));

  std::vector <Point> vts2;
  vts2.push_back(Point(-2.0, 12.0));
  vts2.push_back(Point(-2.0, 10.0));
  vts2.push_back(Point(-3.0, 8.0));
  vts2.push_back(Point(-5.0, 7.0));
  vts2.push_back(Point(-7.0, 9.0));

  Polygon outer = Polygon(vts1);
  Polygon inner = Polygon(vts2);

  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonPolygon, Surrounds)
{
  std::vector <Point> vts1;
  vts1.push_back(Point(-5.0, 0.0));
  vts1.push_back(Point(-4.0, 6.0));
  vts1.push_back(Point(0.0, 10.0));
  vts1.push_back(Point(4.0, 6.0));
  vts1.push_back(Point(4.0, 2.0));
  vts1.push_back(Point(0.0, 0.0));

  std::vector <Point> vts2;
  vts2.push_back(Point(-3.0, 2.0));
  vts2.push_back(Point(-1.0, 6.0));
  vts2.push_back(Point(2.0, 5.0));
  vts2.push_back(Point(3.0, 2.0));
  vts2.push_back(Point(-1.0, 1.0));

  Polygon outer = Polygon(vts2);
  Polygon inner = Polygon(vts1);

  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonReuleaux, Coincident)
{
  std::vector <Point> vts1;
  vts1.push_back(Point(-5.0, 0.0));
  vts1.push_back(Point(-4.0, 6.0));
  vts1.push_back(Point(0.0, 10.0));
  vts1.push_back(Point(4.0, 6.0));
  vts1.push_back(Point(4.0, 2.0));
  vts1.push_back(Point(0.0, 0.0));

  Polygon outer = Polygon(vts1);
  Polygon inner = Polygon(vts1);
  ASSERT_TRUE(inner.ContainedBy(outer));
}