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

  bool hit(const Ray &r, double ray_tmin, double ray_tmax,
             HitRecord &rec) const override {
    // if |(P-C)|2 == r2
    Vector3 oc = center - r.origin();
    auto a = r.direction().length_squared();
    auto h = dot(r.direction(), oc);
    auto c = oc.length_squared() - this->r * this->r;

    auto discriminant = h * h - a * c;
    if (discriminant < 0)
      return false;

    auto sqrtd = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (h - sqrtd) / a;
    if (root <= ray_tmin || ray_tmax <= root) {
      root = (h + sqrtd) / a;
      if (root <= ray_tmin || ray_tmax <= root)
        return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    rec.set_face_normal(r, (rec.p - center) / this->r);

    return true;
  }
};