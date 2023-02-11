#pragma once

#include <cmath>

namespace geometry {

inline void rotate(float& x, float& y, float angle)
{
  float ca = std::cos(angle);
  float sa = std::sin(angle);
  float rx = x * ca - y * sa;
  float ry = x * sa + y * ca;

  x = rx;
  y = ry;
}

}  // namespace geometry
