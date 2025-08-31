#pragma once
#include "../maths/ray.cpp"
#include "../maths/vector.cpp"
#include <bits/stdc++.h>

class HitRecord {
public:
  Point p;
  Vector3 normal;
  double t;
  bool front;

  // outward_normal is a unit vector
  void set_face_normal(const Ray &r, const Vector3 &outward_normal) {
    this->front = dot(r.direction(), outward_normal) < 0;
    this->normal = this->front ? outward_normal : -outward_normal;
  }
};

class Hittable {
public:
  virtual ~Hittable() = default;

  virtual bool hit(const Ray &r, double ray_tmin, double ray_tmax,
                   HitRecord &rec) const = 0;
};

class HittableList : public Hittable {
public:
  std::vector<Hittable *> objects;

  HittableList() {}
  HittableList(Hittable *object) { add(object); }

  void clear() { objects.clear(); }

  void add(Hittable *object) { objects.push_back(object); }

  bool hit(const Ray &r, double ray_tmin, double ray_tmax,
           HitRecord &rec) const override {
    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = ray_tmax;

    for (const auto &object : objects) {
      if (object->hit(r, ray_tmin, closest_so_far, temp_rec)) {
        hit_anything = true;
        closest_so_far = temp_rec.t;
        rec = temp_rec;
      }
    }

    return hit_anything;
  }
};
