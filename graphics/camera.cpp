#pragma once

#include "../config.cpp"
#include "../graphics/color.cpp"
#include "../graphics/utils.cpp"
#include "../maths/interval.cpp"
#include "../maths/ray.cpp"
#include "../maths/vector.cpp"
#include "../models/hittable.cpp"
#include "../renderers/utils.cpp"
#include "../ui/progressbar.hpp"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <ranges>
#include <semaphore>
#include <string>
#include <thread>
#include <vector>

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
                       ((j + offset.y()) * this->image_j);

    auto ray_a = this->center;
    auto dir = samplePixel - ray_a;

    return Ray(ray_a, dir);
  }

  unsigned long long min(unsigned long long a, unsigned long long b) {
    return a > b ? b : a;
  }

public:
  Camera(int focal_length, int vh, Vector3 center, int image_height,
         int image_width) {

    this->focal_length = focal_length;
    this->vh = vh;
    this->center = center;

    this->vw = vh * ((double)image_width) / image_height;

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

  Color getRayColor(const Ray &r, const Hittable &world, HitRecord &rec) const {

    auto y = Interval(0, infinity);

    if (world.hit(r, y, rec)) {
      return 0.5 * (rec.normal + Color(1, 1, 1));
    }

    Vector3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);

    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
  }

  void renderChunk(const int chunkNumber, const unsigned long long chunkArea,
                   const unsigned long long totalArea,
                   std::counting_semaphore<2> &sem, progressbar &bar,
                   const int image_width, const int image_height,
                   std::fstream &image, Hittable &world, HitRecord &rec) {

    // thread-local copy (fixes race condition)
    HitRecord local_rec = rec;

    for (unsigned long long v = chunkArea * chunkNumber;
         v < min(chunkArea * (chunkNumber + 1), totalArea); v++) {

      int j = v / image_width;
      int i = v % image_width;

      Color pc(0, 0, 0);

      for (int sample = 0; sample < SAMPLES_PER_PIXEL; sample++) {
        Ray t = getRayFromCamera(i, j);
        pc += getRayColor(t, world, local_rec);
      }

      pc /= SAMPLES_PER_PIXEL;

      sem.acquire();
      bar.update();
      sem.release();

      WritePixelInImage(image, pc);
    }

    image.flush();
  }

  void renderScene(std::fstream &image, int image_width, int image_height,
                   Hittable &world) {

    HitRecord rec;

    progressbar bar(image_height * image_width);

#ifdef CPU_RENDERING
    unsigned long long const area = (image_height * 1ULL * image_width);

    unsigned long long const chunks = (area / CHUNK_AREA) + 1;

    std::counting_semaphore<2> sem(2);

    std::vector<std::thread> threads(chunks);
    std::vector<std::fstream> buffers(chunks);

    for (auto [i, f] : std::views::enumerate(buffers)) {

      f.open("chunk" + std::to_string(i), std::ios::out | std::ios::trunc);
    }

    for (unsigned long long i = 0; i < chunks; i++) {

      threads[i] =
          std::thread(&Camera::renderChunk, this, i, CHUNK_AREA, area,
                      std::ref(sem), std::ref(bar), image_width, image_height,
                      std::ref(buffers[i]), std::ref(world), std::ref(rec));
    }

    for (auto &t : threads)
      t.join();

    for (auto &buffer : buffers)
      buffer.close();

    std::cout << "SPLICING ALL CHUNKS\n";

    for (unsigned long long i = 0; i < chunks; i++) {

      std::cout << "\tSPLICING CHUNK " << i << " ";

      try {

        std::ifstream buffer("chunk" + std::to_string(i));
        image << buffer.rdbuf();
        buffer.close();

        std::cout << "... OK";

      } catch (std::runtime_error &err) {

        std::cout << "... ERROR: " << err.what();
      }

      std::cout << "\n";

      std::remove(("chunk" + std::to_string(i)).c_str());
    }

#endif
  }
};