#include <stdio.h>

#include "../image_config.h"

void renderGradient(FILE *image) {
  for (int i = 0; i < IMAGE_HEIGHT; i++)
  {
    for (int j = 0; j < IMAGE_WIDTH; j++)
    {
      double r = (double) (i) / (IMAGE_WIDTH - 1);
      double g = (double) (j) / (IMAGE_HEIGHT - 1);
      double b = 0.0;

      int ir = (int) (255.999 * r);
      int ig = (int) (255.999 * g);
      int ib = (int) (255.999 * b);

      fprintf(image, "%d %d %d\n", ir, ig, ib);
    }
  }
}