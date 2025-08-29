#pragma once
#include "./vector.cpp"
class Ray {
public:
  Ray(Point &a, Point &b) {
    this->a = a;
    this->b = b;
  }

  Point at(double t) const { return this->a + this->b * t; }
  Point origin() const { return this->a; }
  Point direction() const { return this->b; }

private:
  // r = a+b*t
  Point a, b;
};