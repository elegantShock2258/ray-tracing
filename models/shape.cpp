#pragma once
#include "../materials/material.cpp"
#include "./hittable.cpp"
class Shape : public Hittable {
public:
  Material *M;
};