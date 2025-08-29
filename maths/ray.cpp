#include "./vector.cpp"
class Ray {
public:
  Ray(Point &a, Point &b) {
    this->a = a;
    this->b = b;
  }


  Point at(double t) { return this->a + this->b * t; }
  Point origin() { return this->a; }
  Point direction() { return this->b; }

private:
  Point a, b;
};