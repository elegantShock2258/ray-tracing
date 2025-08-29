#pragma once
#include "../materials/material.cpp"
#include "../maths/ray.cpp"
class Shape {
public:
  Material *M;
  virtual double hits(const Ray &p) { return 0; };
};