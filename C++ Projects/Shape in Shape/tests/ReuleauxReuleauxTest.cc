#include "Circle.h"
#include <gtest/gtest.h>
#include "Reuleaux.h"

TEST(ReuleauxReuleaux, Contained)
{
  Point vertices1[3];
  vertices1[0] = Point(0.0, 2.9);
  vertices1[1] = Point(-4.0, -4.0);
  vertices1[2] = Point(4.0, -4.0);

  Point vertices2[3];
  vertices2[0] = Point(0, 1.5);
  vertices2[1] = Point(2.0, -2.0);
  vertices2[2] = Point(-2.0, -2.0);
  ReuleauxTriangle outer = ReuleauxTriangle(vertices1);
  ReuleauxTriangle inner = ReuleauxTriangle(vertices2);
  ASSERT_TRUE(inner.ContainedBy(outer));
}


TEST(ReuleauxReuleaux, Touches_Inside)
{
  // inner at edge of triangle
  Point vertices1[3];
  vertices1[0] = Point(0.0, 2.9);
  vertices1[1] = Point(-4.0, -4.0);
  vertices1[2] = Point(4.0, -4.0);

  Point vertices2[3];
  vertices2[0] = Point(0.0, -1.1);
  vertices2[1] = Point(-2.0, -4.5);
  vertices2[2] = Point(2, -4.5);
  ReuleauxTriangle outer = ReuleauxTriangle(vertices1);
  ReuleauxTriangle inner = ReuleauxTriangle(vertices2);
  ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(ReuleauxReuleaux, Intersect)
{
  // not contained by, intersect
  Point vertices1[3];
  vertices1[0] = Point(0.0, 2.9);
  vertices1[1] = Point(-4.0, -4.0);
  vertices1[2] = Point(4.0, -4.0);

  Point vertices2[3];
  vertices2[0] = Point(0.0, -2.1);
  vertices2[1] = Point(-2.0, -5.5);
  vertices2[2] = Point(2, -5.5);
  ReuleauxTriangle outer = ReuleauxTriangle(vertices1);
  ReuleauxTriangle inner = ReuleauxTriangle(vertices2);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxReuleaux, Touches_Outside)
{
  // inner edge touches outer edge
  Point vertices1[3];
  // vertices1[0] = Point(4.0, -4.0);
  // vertices1[1] = Point(-12.0, -4.0);
  // vertices1[2] = Point(-4.0, 9.9);
  vertices1[0] = Point(0.0, 2.9);
  vertices1[1] = Point(-4.0, -4.0);
  vertices1[2] = Point(4.0, -4.0);

  Point vertices2[3];
  // vertices2[0] = Point(-12.0, -4.0);
  // vertices2[1] = Point(-17.0, -3.7);
  // vertices2[2] = Point(-14.8, -8.2);
  vertices2[0] = Point(0.0, 6.0);
  vertices2[1] = Point(-0.5, -5.2);
  vertices2[2] = Point(0.4, -5.2);
  ReuleauxTriangle outer = ReuleauxTriangle(vertices1);
  ReuleauxTriangle inner = ReuleauxTriangle(vertices2);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxReuleaux, Outside)
{
  // inner completely outside of outer
  Point vertices1[3];
  vertices1[0] = Point(4.0, -4.0);
  vertices1[1] = Point(-12.0, -4.0);
  vertices1[2] = Point(-4.0, 9.9);

  Point vertices2[3];
  vertices2[0] = Point(-6.5, -7.7);
  vertices2[1] = Point(-1.5, -7.6);
  vertices2[2] = Point(-4.0, -12.0);
  ReuleauxTriangle outer = ReuleauxTriangle(vertices1);
  ReuleauxTriangle inner = ReuleauxTriangle(vertices2);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxReuleaux, Surrounds)
{
  // checks when inner contains outer
  Point vertices1[3];
  vertices1[0] = Point(-4.0, -4.0);
  vertices1[1] = Point(-12.0, -4.0);
  vertices1[2] = Point(-4.0, 9.9);

  Point vertices2[3];
  vertices2[0] = Point(-5.7, 2.0);
  vertices2[1] = Point(-1.7, 1.4);
  vertices2[2] = Point(-4.2, -1.7);
  ReuleauxTriangle outer = ReuleauxTriangle(vertices2);
  ReuleauxTriangle inner = ReuleauxTriangle(vertices1);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(ReuleauxReuleaux, Coincident)
{
  // checks when the circles are the same
  Point vertices1[3];
  vertices1[0] = Point(-4.0, -4.0);
  vertices1[1] = Point(-12.0, -4.0);
  vertices1[2] = Point(-4.0, 9.9);

  ReuleauxTriangle outer = ReuleauxTriangle(vertices1);
  ReuleauxTriangle inner = ReuleauxTriangle(vertices1);
  ASSERT_FALSE(inner.ContainedBy(outer));
}