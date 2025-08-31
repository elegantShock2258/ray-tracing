#pragma once
#include "../graphics/color.cpp"
#include "../maths/ray.cpp"
#include <cstdarg>

class Material {
private:
public:
  std::string name = "BASE MAT";
  virtual Color getMaterialColor(const Point &center, const Ray &ray, int res) {
    return Color(0, 0, 0);
  }
  virtual ~Material() = default;
};