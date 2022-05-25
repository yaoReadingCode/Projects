#include "Circle.h"
#include <gtest/gtest.h>
#include "Reuleaux.h"

TEST(ReuleauxCircle, Contained)
{
  Point vertices[3];
  vertices[0] = Point(-2.0, 0.0);
  vertices[1] = Point(2.0, 0.0);
  vertices[2] = Point(0.0, 3.5);
  Circle outer = Circle(Point(0.0, 1.0), 3.0);
  ReuleauxTriangle inner = ReuleauxTriangle(vertices);
  ASSERT_TRUE(inner.ContainedBy(outer));
}


TEST(ReuleauxCircle, Touches_Inside)
{
  // inner at edge of triangle
  Point vertices[3];
  vertices[0] = Point(0.0, 3.0);
  vertices[1] = Point(-4.0, -4.0);
  vertices[2] = Point(4.0, -4.0);
  Circle outer = Circle(Point(0.0, 0.0), 6.0);
  ReuleauxTriangle inner = ReuleauxTriangle(vertices);
  ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(ReuleauxCircle, Intersect)
{
  // not contained by, intersect
  Point vertices[3];
  vertices[0] = Point(0.0, 3.0);
  vertices[1] = Point(-4.0, -4.0);
  vertices[2] = Point(4.0, -4.0);
  Circle outer = Circle(Point(0.0, -2.0), 4.5);
  ReuleauxTriangle inner = ReuleauxTriangle(vertices);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxCircle, Touches_Outside)
{
  // inner edge touches outer edge
  Point vertices[3];
  vertices[0] = Point(0.0, 3.0);
  vertices[1] = Point(-4.0, -4.0);
  vertices[2] = Point(4.0, -4.0);
  Circle outer = Circle(Point(0.0, -1.0), 4.1);
  ReuleauxTriangle inner = ReuleauxTriangle(vertices);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxCircle, Outside)
{
  // inner completely outside of outer
  Point vertices[3];
  vertices[0] = Point(0.0, 3.0);
  vertices[1] = Point(-4.0, -4.0);
  vertices[2] = Point(4.0, -4.0);
  Circle outer = Circle(Point(0.0, -8.0), 2.0);
  ReuleauxTriangle inner = ReuleauxTriangle(vertices);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxCircle, Surrounds)
{
  // checks when inner contains outer
  Point vertices[3];
  vertices[0] = Point(0.0, 3.0);
  vertices[1] = Point(-4.0, -4.0);
  vertices[2] = Point(4.0, -4.0);
  Circle outer = Circle(Point(0.0, -1.0), 3.0);
  ReuleauxTriangle inner = ReuleauxTriangle(vertices);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxCircle, Coincident)
{
  // checks when the circles are the same
  Point vertices[3];
  vertices[0] = Point(0.0, 3.5);
  vertices[1] = Point(-2.0, 0.0);
  vertices[2] = Point(2.0, 0.0);
  Circle outer = Circle(Point(0.0, 3), 3.6);
  ReuleauxTriangle inner = ReuleauxTriangle(vertices);
  ASSERT_FALSE(inner.ContainedBy(outer));
}