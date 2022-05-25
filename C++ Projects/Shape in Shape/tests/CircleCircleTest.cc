#include "Circle.h"
#include <gtest/gtest.h>
#include "Reuleaux.h"


TEST(CircleCircle, Contained)
{
  Circle inner = Circle(Point(0.0,0.0), 2.0);
  Circle outer = Circle(Point(0.0,0.0), 4.0);
  ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(CircleCircle, Touches_Inside)
{
  // inner at edge of circle
  Circle inner = Circle(Point(0.0,2.0), 2.0);
  Circle outer = Circle(Point(0.0,0.0), 4.0);
  ASSERT_TRUE(inner.ContainedBy(outer));
}

TEST(CircleCircle, Intersect)
{
  // not contained by, intersect
  Circle inner = Circle(Point(0.0, 3.0), 2.0);
  Circle outer = Circle(Point(0.0, 0.0), 4.0);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CircleCircle, Touches_Outside)
{
  // inner edge touches outer edge
  Circle inner = Circle(Point(0.0, 6.0), 2.0);
  Circle outer = Circle(Point(0.0, 0.0), 4.0);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CircleCircle, Outside)
{
  // inner completely outside of outer
  Circle inner = Circle(Point(0.0,6.0), 1.0);
  Circle outer = Circle(Point(0.0,0.0), 4.0);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CircleCircle, Surrounds)
{
  // checks when inner contains outer
  Circle outer = Circle(Point(0.0, 0.0), 2.0);
  Circle inner = Circle(Point(0.0, 0.0), 4.0);
  ASSERT_FALSE(inner.ContainedBy(outer));
}

TEST(CircleCircle, Coincident)
{
  // checks when the circles are the same
  Circle inner = Circle(Point(0.0, 0.0), 4.0);
  Circle outer = Circle(Point(0.0, 0.0), 4.0);
  ASSERT_TRUE(inner.ContainedBy(outer));
}






/* 
   You'll need to extend this by adding additional tests for:
    1. Inner and Outer intersect (not contained)
    2. Inner is entirely outside Outer (not contained)
    3. Inner surrounds Outer (not contained)
    4. Inner perimeter touches Outer perimeter, Inner is inside Outer (contained)
    5. Inner perimeter touches Outer perimeter, Inner is outside Outer (not contained)
*/
