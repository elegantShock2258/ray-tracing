#pragma once
#include "../graphics/color.cpp"

class Material {
private:
public:
  std::string name = "BASE MAT";
  virtual Color getMaterialColor(const Point &p) {
    return Color(0, 0, 0);
  }
  virtual ~Material() = default;
};