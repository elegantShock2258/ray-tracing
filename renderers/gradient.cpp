#pragma once
#include "./renderers.cpp"
#include <stdio.h>
#include "./utils.cpp"

void renderGradient(FILE *image, int IMAGE_HEIGHT, int IMAGE_WIDTH) {
  for (int i = 0; i < IMAGE_HEIGHT; i++) {
    for (int j = 0; j < IMAGE_WIDTH; j++) {
      double r = (double)(i) / (IMAGE_WIDTH - 1);
      double g = (double)(j) / (IMAGE_HEIGHT - 1);
      double b = 0.0;
      auto t = Color(r, g, b);
      WritePixelInImage(image, t);
    }
  }
}