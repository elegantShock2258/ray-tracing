#include "../materials/material.cpp"
#include "./shape.cpp"
#include <cmath>
class Sphere : public Shape {
private:
  Point center;
  double r;

public:
  Sphere(Material *M, Point center, double r) {
    this->M = M;
    this->center = center;
    this->r = r;
  }

  double hits(const Ray &r) override {
    // if |(P-C)|2 == r2
    Vector3 oc =  -r.origin() + this->center;
    auto a = r.direction().length_squared();
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = oc.length_squared() - (this->r * this->r);
    auto D = b * b - 4 * a * c;


    if (D < 0) {
      return -1.0;
    } else {
      return (-b - std::sqrt(D)) / (2.0 * a);
    }
  }
};