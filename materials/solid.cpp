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
  Color getMaterialColor(const Point &p) override {
    return this->color;
  };
};