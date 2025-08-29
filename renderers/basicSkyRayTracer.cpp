#pragma once
#include "../graphics/color.cpp"
#include "../graphics/scene.cpp"
#include "../maths/ray.cpp"

#include <cstdio>

Color getSkyRayColor(Ray &r) {
  Vector3 ud = unit_vector(r.direction());
  auto a = 0.5 * (ud.y() + 1.0);
  auto res = (1 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
  return res;
}
