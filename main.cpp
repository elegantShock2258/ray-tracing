#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#define OUT_PATH "build/image.ppm"
#include "graphics/camera.cpp"
#include "graphics/scene.cpp"
#include "materials/procedural.cpp"
#include "materials/solid.cpp"
#include "models/sphere.cpp"
#include "renderers/renderers.cpp"

struct stat st = {0};

Color eval(const Point &p, const Ray &r, int res) {
  auto N = unit_vector(r.at(res) - Vector3(0, 0, -1));
  return 0.5 * Color(N.x() + 1, N.y() + 1, N.z() + 1);
}
Color e2(const Point &p, const Ray &r, int res) {
  auto N = unit_vector(r.at(res) - Vector3(0, 0, -1));
  return 0.5 * Color(N.x() + 1, N.y() + 1, N.z() + 1);
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

  int image_width = 800;
  auto aspect_ratio = 16.0 / 9;
  int image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  Camera cam(1.0, 2.0, Vector3(0, 0, 0), image_height, image_width);
  Scene scene(aspect_ratio, image_width, &cam);

  fprintf(image, "P3\n%d %d\n255\n", image_width, image_height);

  Color red(255, 0, 0);
  Color blank(1, 1, 1);
  Material *M = new SolidMaterial(red);
  Material *Ms = new SolidMaterial(blank);
  Material *P = new ProceduralMaterial(eval);

  Sphere s(M, Point(0, 0, -1), 0.5);
  Sphere t(Ms, Point(0, -100.5, -1), 100);

  scene.world.add(&s);
  scene.world.add(&t);


  scene.renderScene(image, getSkyRayColor);
  printf("image rendered");

  return 0;
}