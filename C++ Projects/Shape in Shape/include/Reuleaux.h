/*
 * Copyright (C) 2018 David C. Harrison. All right reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */

#ifndef _REULEAUX_H_
#define _REULEAUX_H_

#include "Containable.h"
#include "Point.h"

class ReuleauxTriangle : public Containable {
  private:
    Point v1_;
    Point v2_;
    Point v3_;
  public:
    // do not modify or remove this constructor
    ReuleauxTriangle(const Point vertices[3]);

    // do not modify or remove these functions
    bool ContainedBy(Circle &circle);
    bool ContainedBy(Polygon &polygon);
    bool ContainedBy(ReuleauxTriangle &rt);

    Point v1();
    Point v2();
    Point v3();
};

#endif
