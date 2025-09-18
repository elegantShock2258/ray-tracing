#pragma once
#include "../graphics/color.cpp"
#include "../graphics/utils.cpp"
#include "../maths/interval.cpp"
#include "../maths/ray.cpp"
#include "../maths/vector.cpp"
#include "../models/hittable.cpp"
#include "../renderers/utils.cpp"
#include <cstdlib>
#include "../ui/progressbar.hpp"
class Camera {
private:
  double focal_length, vh, vw;
  Vector3 topLeft, center, image_i, image_j, viewport_u, viewport_v,
      originPixel;
  Vector3 sample_square() const {
    return Vector3(random_double() - 0.5, random_double() - 0.5, 0);
  }
  Ray getRayFromCamera(int i, int j) const {
    auto offset = sample_square();
    auto samplePixel = this->originPixel + ((i + offset.x()) * this->image_i) +
                       (((j + offset.y())) * this->image_j);

    auto ray_a = this->center;
    auto dir = samplePixel - ray_a;

    return Ray(ray_a, dir);
  }
public:
  int samples_per_pixel = 200;

  Camera(int focal_length, int vh, Vector3 center, int image_height,
         int image_width) {
    this->focal_length = focal_length;
    this->vh = vh;
    this->center = center;

    this->vw = vh * ((double)image_width) / image_height;
    this->center = center;

    this->viewport_u = Vector3(vw, 0, 0);
    this->viewport_v = Vector3(0, -vh, 0);

    this->image_i = Vector3(vw / image_width, 0, 0);
    this->image_j = Vector3(0, -vh / (double)image_height, 0);

    this->topLeft = this->center - Vector3(0, 0, focal_length) -
                    (this->viewport_u / 2) - (this->viewport_v / 2);
    this->originPixel = this->topLeft + 0.5 * (this->image_i + this->image_j);
  }
  Vector3 getImageOrigin() { return this->originPixel; }
  Vector3 getImageI() { return this->image_i; }
  Vector3 getImageJ() { return this->image_j; }
  Vector3 getCenter() { return this->center; }

  Color getRayColor(const Ray &r, const Hittable &world) const {
    HitRecord rec;
    auto y = Interval(0, infinity);
    if (world.hit(r, y, rec)) {
      return 0.5 * (rec.normal + Color(1, 1, 1));
    }

    Vector3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
  }

  void renderScene(FILE *image, int image_width, int image_height,
                   Hittable &world) {
    auto center = this->getCenter();

    progressbar bar(image_height*image_width);
    for (int j = 0; j < image_height; j++) {
      for (int i = 0; i < image_width; i++) {
        bar.update();
        auto pixel_center = this->getImageOrigin() + (i * this->getImageI()) +
                            (j * this->getImageJ());
        auto ray_direction = pixel_center - this->getCenter();
        auto camera_center = this->getCenter();
        Ray ray(camera_center, ray_direction);

        Color pc(0, 0, 0);
        for (int sample = 0; sample < this->samples_per_pixel; sample++) {
          Ray t = getRayFromCamera(i, j);
          pc += this->getRayColor(t, world);
        }
        pc /= samples_per_pixel;
        WritePixelInImage(image, pc);
      }
    }
  }
};