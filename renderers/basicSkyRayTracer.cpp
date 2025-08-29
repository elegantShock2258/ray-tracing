#pragma once
#include "../graphics/color.cpp"
#include "../graphics/scene.cpp"
#include "../maths/ray.cpp"
#include "./utils.cpp"

#include <cstdio>

Color getRayColor(Ray &r) {
  Vector3 ud = unit_vector(r.direction());
  auto a = 0.5 * (ud.y() + 1.0);
  auto res = (1 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
  return res;
}

void SkyTracer(FILE *image, Scene *s) {
  auto center = s->cam_center();
  for (int j = 0; j < s->imgH(); j++) {
    for (int i = 0; i < s->imgW(); i++) {
      auto pixel_center = s->origin() + (i * s->i()) + (j * s->j());
      auto ray_direction = pixel_center - s->cam_center();
      Ray ray(center, ray_direction);

      Color pixel_color = getRayColor(ray);

      WritePixelInImage(image, pixel_color);
    }
  }
}