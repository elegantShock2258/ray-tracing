#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#define OUT_PATH "build/image.ppm"
#include "graphics/camera.cpp"
#include "graphics/scene.cpp"
#include "renderers/renderers.cpp"

struct stat st = {0};

static void renderImage(FILE *image, int w, int h) {
  // renderGradient(image, w, h);
}

int main(int n, char **args) {
  if (stat("build", &st) == -1) {
    printf("making directory ./build ...\n");
    mkdir("build", 0700);
  }

  FILE *image = fopen(OUT_PATH, "w");

  if (image == NULL) {
    printf("failed to make image file\n");
    return -1;
  }

  int image_width = 400;
  auto aspect_ratio = 16.0 / 9;
  int image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  Camera cam(1.0, 2.0, Vector3(0, 0, 0), image_height, image_width);
  Scene scene(aspect_ratio, image_width, &cam);

  fprintf(image, "P3\n%d %d\n255\n", image_width, image_height);
  // renderImage(image, image_width, image_height);
  SkyTracer(image, &scene);
  printf("image rendered");

  return 0;
}