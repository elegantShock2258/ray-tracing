#include "graphics/camera.cpp"
#include "graphics/scene.cpp"
#include "materials/procedural.cpp"
#include "materials/solid.cpp"
#include "models/sphere.cpp"
#include "renderers/renderers.cpp"
#include <fstream>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "config.cpp"

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

  auto image = std::fstream(OUT_PATH, std::ios::out | std::ios::trunc);

  if (image.fail()) {
    printf("failed to make image file\n");
    return -1;
  }

  int image_height = int(IMAGE_WIDTH / ASPECT_RATIO);
  image_height = (image_height < 1) ? 1 : image_height;

  Camera cam(1.0, 2.0, Vector3(0, 0, 0), image_height, IMAGE_WIDTH);
  Scene scene(ASPECT_RATIO, IMAGE_WIDTH, &cam);

  image << "P3\n" << IMAGE_WIDTH << " " << image_height << "\n255\n";

  Color red(255, 0, 0);
  Color blank(1, 1, 1);
  Material *M = new SolidMaterial(red);
  Material *Ms = new SolidMaterial(blank);
  Material *P = new ProceduralMaterial(eval);

  Sphere s(M, Point(0, 0, -1), 0.5);
  Sphere t(Ms, Point(0, -100.5, -1), 100);

  scene.world.add(&s);
  scene.world.add(&t);

  scene.render(image);
  printf("\nimage rendered");

  return 0;
}