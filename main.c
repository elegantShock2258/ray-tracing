#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "image_config.h"
#include "renderers/renderers.c"

struct stat st = { 0 };

static void renderImage(FILE *image) {
  renderGradient(image);
}

int main(int n, char **args) {
  if (stat("build", &st) == -1)
  {
    printf("making directory ./build ...\n");
    mkdir("build", 0700);
  }

  FILE *image = fopen(OUT_PATH, "w");

  if (image == NULL)
  {
    printf("failed to make image file\n");
    return -1;
  }

  fprintf(image, "P3\n%d %d\n255\n", IMAGE_WIDTH, IMAGE_HEIGHT);
  renderImage(image);
  printf("image rendered");

  return 0;
}