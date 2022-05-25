#include "Circle.h"
#include <gtest/gtest.h>
#include "Reuleaux.h"

TEST(CircleReuleaux, Contained)
{
  Point vertices[3];
  vertices[0] = Point(0.0, 3.0);
  vertices[1] = Point(-4.0, -4.0);
  vertices[2] = Point(4.0, -4.0);
  Circle inner = Circle(Point(0.0, -2.0), 1.0);
  ReuleauxTriangle outer = ReuleauxTriangle(vertices);
  ASSERT_TRUE(inner.ContainedBy(outer));
}


TEST(CircleReuleaux, Touches_Inside)
{
  // inner at edge of triangle
  Point vertices[3];
  vertices[0] = Point(0.0, 3.0);
  vertices[1] = Point(-4.0, -4.0);
  vertices[2] = Point(4.0, -4.0);
  Circle inner = Circle(Point(0.0, -3.0), 2.0);
  ReuleauxTriangle outer = ReuleauxTriangle(vertices);
  ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(CircleReuleaux, Intersect)
{
  // not contained by, intersect
  Point vertices[3];
  vertices[0] = Point(0.0, 3.0);
  vertices[1] = Point(-4.0, -4.0);
  vertices[2] = Point(4.0, -4.0);
  Circle inner = Circle(Point(0.0, -3.0), 3.0);
  ReuleauxTriangle outer = ReuleauxTriangle(vertices);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CircleReuleaux, Touches_Outside)
{
  // inner edge touches outer edge
  Point vertices[3];
  vertices[0] = Point(0.0, 3.0);
  vertices[1] = Point(-4.0, -4.0);
  vertices[2] = Point(4.0, -4.0);
  Circle inner = Circle(Point(0.0, -7.0), 2.0);
  ReuleauxTriangle outer = ReuleauxTriangle(vertices);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CircleReuleaux, Outside)
{
  // inner completely outside of outer
  Point vertices[3];
  vertices[0] = Point(0.0, 3.0);
  vertices[1] = Point(-4.0, -4.0);
  vertices[2] = Point(4.0, -4.0);
  Circle inner = Circle(Point(0.0, -8.0), 2.0);
  ReuleauxTriangle outer = ReuleauxTriangle(vertices);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CircleReuleaux, Surrounds)
{
  // checks when inner contains outer
  Point vertices[3];
  vertices[0] = Point(0.0, 3.0);
  vertices[1] = Point(-4.0, -4.0);
  vertices[2] = Point(4.0, -4.0);
  Circle inner = Circle(Point(0.0, -2.0), 6.0);
  ReuleauxTriangle outer = ReuleauxTriangle(vertices);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CircleReuleaux, Coincident)
{
  // checks when the circles are the same
  Point vertices[3];
  vertices[0] = Point(0.0, 3.0);
  vertices[1] = Point(-4.0, -4.0);
  vertices[2] = Point(4.0, -4.0);
  Circle inner = Circle(Point(0.0, -2.0), 3.5);
  ReuleauxTriangle outer = ReuleauxTriangle(vertices);
  ASSERT_FALSE(inner.ContainedBy(outer));
}