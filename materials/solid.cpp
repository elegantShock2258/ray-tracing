#pragma once
#include "./material.cpp"

class SolidMaterial : public Material {
private:
  Color color;

public:
  SolidMaterial(Color &c) {
    this->name = "SOLID";
    this->color = c;
  }
  Color getMaterialColor(const Point &p,const Ray &ray, int res) override {
    auto N = unit_vector(p - Vector3(0, 0, -1));
    return 0.5 * Color(N.x() + 1, N.y() + 1, N.z() + 1);
    // return this->color;
  };
};