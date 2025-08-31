#pragma once
#include "./material.cpp"

class ProceduralMaterial : public Material {
private:
  Color (*eval)(const Point &, const Ray &, int res);

public:
  ProceduralMaterial(Color (*colorFunction)(const Point &, const Ray &, int res)) {
    this->name = "Procedural";
    this->eval = colorFunction;
  }
  Color getMaterialColor(const Point &p, const Ray &ray, int res) override {
    return eval(p, ray,res);
  }
};