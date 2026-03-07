#pragma once
#include "../maths/interval.cpp"
#include "../maths/vector.cpp"
#include <cstdio>
#include <fstream>
#include <memory>

inline void WritePixelInImage(std::fstream &image, Point &p) {

  auto r = p.x();
  auto g = p.y();
  auto b = p.z();

  static const Interval intensity(0.000, 0.999);

  int rbyte = int(256 * intensity.clamp(r));
  int gbyte = int(256 * intensity.clamp(g));
  int bbyte = int(256 * intensity.clamp(b));

  image << rbyte << " " << gbyte << " " << bbyte << "\n";
}