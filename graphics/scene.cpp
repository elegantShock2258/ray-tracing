#pragma once
#include "../models/shape.cpp"
#include "../renderers/utils.cpp"
#include "./camera.cpp"
#include <vector>
class Scene {
private:
  double aspect_ratio, vh, vw;
  int image_width, image_height;
  Camera *camera;

public:
  std::vector<Shape *> shapes;
  // include a render method that goes through shapes and sees if the ray goes
  // through it, if it does and then use material color to get color and write
  // color to pixel
  Scene(double aspect_ratio, int image_width, Camera *cam) {
    this->aspect_ratio = aspect_ratio;
    this->image_width = image_width;

    this->image_height = int(image_width / aspect_ratio);
    this->image_height = this->image_height < 1 ? 1 : this->image_height;

    this->camera = cam;
  }
  int imgW() { return this->image_width; }
  int imgH() { return this->image_height; }

  Vector3 origin() { return this->camera->getImageOrigin(); }
  Vector3 i() { return this->camera->getImageI(); }
  Vector3 j() { return this->camera->getImageJ(); }
  Vector3 cam_center() { return this->camera->getCenter(); }

  void renderScene(FILE *image, Color (*getRayColor)(Ray &)) {
    auto center = this->camera->getCenter();
    for (int j = 0; j < this->image_height; j++) {
      for (int i = 0; i < this->image_width; i++) {
        auto pixel_center = this->camera->getImageOrigin() +
                            (i * this->camera->getImageI()) +
                            (j * this->camera->getImageJ());
        auto ray_direction = pixel_center - this->camera->getCenter();
        auto camera_center = this->camera->getCenter();
        Ray ray(camera_center, ray_direction);

        Color pixel_color = getRayColor(ray);

        for (auto shape : shapes) {
          if (shape->hits(ray) > 0.0) {
            auto res = shape->M->getMaterialColor(center);
            pixel_color = res;
          }
        }

        WritePixelInImage(image, pixel_color);
      }
    }
  }
};