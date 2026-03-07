#pragma once
#include "./renderers.cpp"
#include <fstream>
#include <stdio.h>
#include "./utils.cpp"

void renderGradient(std::fstream &image, int h, int w) {
  for (int i = 0; i < h; i++) {
    for (int j = 0; j <w; j++) {
      double r = (double)(i) / (w - 1);
      double g = (double)(j) / (h - 1);
      double b = 0.0;
      auto t = Color(r, g, b);
      WritePixelInImage(image, t);
    }
  }
}