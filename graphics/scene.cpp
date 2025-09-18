#pragma once
#include "../models/shape.cpp"
#include "../renderers/utils.cpp"
#include "./camera.cpp"
#include "./utils.cpp"
#include <vector>

class Scene {
private:
  double aspect_ratio, vh, vw;
  int image_width, image_height;
  Camera *camera;

public:
  HittableList world;
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

  void render(FILE* image){
    this->camera->renderScene(image,image_width, image_height,this->world);
  }
};