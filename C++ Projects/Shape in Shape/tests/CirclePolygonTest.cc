#include "Circle.h"
#include <gtest/gtest.h>
#include "Polygon.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

TEST(CirclePolygon, Contained)
{
  std::vector <Point> vts;
  vts.push_back(Point(-7.0, 0.0));
  vts.push_back(Point(-6.0, 8.0));
  vts.push_back(Point(0.0, 9.0));
  vts.push_back(Point(-1.0, 5.0));
  vts.push_back(Point(8.0, 1.0));
  vts.push_back(Point(0.0, 0.0));

  Circle inner = Circle(Point(-4.0, 4.0), 2.0);
  Polygon outer = Polygon(vts);
  ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(CirclePolygon, Touches_Inside)
{
  std::vector <Point> vts;
  vts.push_back(Point(-7.0, 0.0));
  vts.push_back(Point(-6.0, 8.0));
  vts.push_back(Point(0.0, 9.0));
  vts.push_back(Point(-1.0, 4.0));
  vts.push_back(Point(8.0, 1.0));
  vts.push_back(Point(0.0, 0.0));

  Circle inner = Circle(Point(-3.0, 4.0), 2.0);
  Polygon outer = Polygon(vts);
  ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(CirclePolygon, Intersects)
{
  std::vector <Point> vts;
  vts.push_back(Point(-7.0, 0.0));
  vts.push_back(Point(-6.0, 8.0));
  vts.push_back(Point(0.0, 9.0));
  vts.push_back(Point(-3.0, 4.0));
  vts.push_back(Point(8.0, 1.0));
  vts.push_back(Point(0.0, 0.0));

  Circle inner = Circle(Point(-3.0, 4.0), 2.0);
  Polygon outer = Polygon(vts);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CirclePolygon, Touches_Outside)
{
  std::vector <Point> vts;
  vts.push_back(Point(-7.0, 0.0));
  vts.push_back(Point(-6.0, 8.0));
  vts.push_back(Point(0.0, 9.0));
  vts.push_back(Point(-3.0, 4.0));
  vts.push_back(Point(8.0, 1.0));
  vts.push_back(Point(0.0, 0.0));

  Circle inner = Circle(Point(4.0, 9.0), 4.0);
  Polygon outer = Polygon(vts);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CirclePolygon, Outside)
{
  std::vector <Point> vts;
  vts.push_back(Point(-7.0, 0.0));
  vts.push_back(Point(-6.0, 8.0));
  vts.push_back(Point(0.0, 9.0));
  vts.push_back(Point(-3.0, 4.0));
  vts.push_back(Point(8.0, 1.0));
  vts.push_back(Point(0.0, 0.0));

  Circle inner = Circle(Point(4.0, 9.0), 3.0);
  Polygon outer = Polygon(vts);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CirclePolygon, Surrounds)
{
  std::vector <Point> vts;
  vts.push_back(Point(-7.0, 0.0));
  vts.push_back(Point(-6.0, 8.0));
  vts.push_back(Point(0.0, 9.0));
  vts.push_back(Point(-3.0, 4.0));
  vts.push_back(Point(8.0, 1.0));
  vts.push_back(Point(0.0, 0.0));

  Circle inner = Circle(Point(-2.0, 4.0), 12.0);
  Polygon outer = Polygon(vts);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CirclePolygon, Coincident)
{
  std::vector <Point> vts;
  vts.push_back(Point(-15.0, 0.0));
  vts.push_back(Point(-12.0, 9.0));
  vts.push_back(Point(-9.0, 12.0));
  vts.push_back(Point(0.0, 15.0));
  vts.push_back(Point(9.0, 12.0));
  vts.push_back(Point(12.0, 9.0));
  vts.push_back(Point(15.0, 0.0));
  vts.push_back(Point(13.0, -7.5));
  vts.push_back(Point(9.0, -12.0));
  vts.push_back(Point(0.0, -15.0));
  vts.push_back(Point(-9.0, -12.0));
  vts.push_back(Point(-12.0, -9.0));

  Circle inner = Circle(Point(0.0, 0.0), 15.0);
  Polygon outer = Polygon(vts);
  ASSERT_FALSE(inner.ContainedBy(outer));
}