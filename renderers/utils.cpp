#pragma once
#include <cstdio>
#include "../maths/vector.cpp"

inline void WritePixelInImage(FILE *image, Point &p) {

  int ir = (int)(255.999 * p.x());
  int ig = (int)(255.999 * p.y());
  int ib = (int)(255.999 * p.z());

  fprintf(image, "%d %d %d\n", ir, ig, ib);
}