#pragma once
#include "../maths/vector.cpp"

class Camera {
private:
  double focal_length, vh, vw;
  Vector3 topLeft, center, image_i, image_j, viewport_u, viewport_v,
      originPixel;

public:
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
};