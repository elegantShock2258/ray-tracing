#pragma once

#include "../maths/vector.cpp"
#include <cstdio>

#define Color Vector3
#define MAX_SCALE 255.99
void writeColor(FILE *file, const Color &c) {
  auto r = int(MAX_SCALE * c.x());
  auto g = int(MAX_SCALE * c.y());
  auto b = int(MAX_SCALE * c.z());

  fprintf(file, "%d %d %d\n", r, g, b);
}