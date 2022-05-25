#include "Circle.h"
#include <gtest/gtest.h>
#include "Polygon.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

TEST(PolygonCircle, Contained)
{
  std::vector <Point> vts;
  vts.push_back(Point((2.0), 6.0));
  vts.push_back(Point(4.0, 4.0));
  vts.push_back(Point(6.0, -4.0));
  vts.push_back(Point(2.0, -6.0));
  vts.push_back(Point(-4.0, -4.0));
  vts.push_back(Point(-6.0, 2.0));

  Circle outer = Circle(Point(0.0, 0.0), 8.0);
  Polygon inner = Polygon(vts);
  ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(PolygonCircle, Touches_Inside)
{
  std::vector <Point> vts;
  vts.push_back(Point(-2.0, 6.0));
  vts.push_back(Point(4.0, 4.0));
  vts.push_back(Point(6.0, -4.0));
  vts.push_back(Point(2.0, -6.0));
  vts.push_back(Point(-4.0, -4.0));
  vts.push_back(Point(-8.0, 0.0));

  Circle outer = Circle(Point(0.0, 0.0), 8.0);
  Polygon inner = Polygon(vts);
  ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(PolygonCircle, Intersects)
{
  std::vector <Point> vts;
  vts.push_back(Point(-5.0, 10.0));
  vts.push_back(Point(4.0, 4.0));
  vts.push_back(Point(6.0, -4.0));
  vts.push_back(Point(2.0, -6.0));
  vts.push_back(Point(-4.0, -4.0));
  vts.push_back(Point(-8.0, 0.0));

  Circle outer = Circle(Point(0.0, 0.0), 8.0);
  Polygon inner = Polygon(vts);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonCircle, Touches_Outside)
{
  std::vector <Point> vts;
  vts.push_back(Point(-16.0, 6.0));
  vts.push_back(Point(-10.0, 4.0));
  vts.push_back(Point(-8.0, 0.0));
  vts.push_back(Point(-14.0, -4.0));
  vts.push_back(Point(-18.0, -2.0));
  vts.push_back(Point(-18.0, 2.0));

  Circle outer = Circle(Point(0.0, 0.0), 8.0);
  Polygon inner = Polygon(vts);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonCircle, Outside)
{
  std::vector <Point> vts;
  vts.push_back(Point(-16.0, 6.0));
  vts.push_back(Point(-10.0, 4.0));
  vts.push_back(Point(-9.0, 0.0));
  vts.push_back(Point(-14.0, -4.0));
  vts.push_back(Point(-18.0, -2.0));
  vts.push_back(Point(-18.0, 2.0));

  Circle outer = Circle(Point(0.0, 0.0), 8.0);
  Polygon inner = Polygon(vts);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonCircle, Surrounds)
{
  std::vector <Point> vts;
  vts.push_back(Point(-6.0, 10.0));
  vts.push_back(Point(8.0, 8.0));
  vts.push_back(Point(12.0, -2.0));
  vts.push_back(Point(8.0, -10.0));
  vts.push_back(Point(-10.0, -8.0));
  vts.push_back(Point(-12.0, 2.0));

  Circle outer = Circle(Point(0.0, 0.0), 8.0);
  Polygon inner = Polygon(vts);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(PolygonCircle, Coincident)
{
  std::vector <Point> vts;
  vts.push_back(Point(-4.8, 6.4));
  vts.push_back(Point(0.0, 8.0));
  vts.push_back(Point(4.2, 6.8));
  vts.push_back(Point(8.0, 0.0));
  vts.push_back(Point(0.0, -8.0));
  vts.push_back(Point(-8.0, 0.0));

  Circle outer = Circle(Point(0.0, 0.0), 8.0);
  Polygon inner = Polygon(vts);
  ASSERT_TRUE(inner.ContainedBy(outer));
}