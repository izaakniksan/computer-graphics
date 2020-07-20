#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{

  if (ray.direction.dot(this->normal) == 0){
    return false;
  }
  // plane/line intersection equation:
  // (p - p0) dot n = 0
  // (e + td - p0) dot n = 0

  double temp_t = ((this->normal).dot(this->point - ray.origin))/((ray.direction).dot(this->normal));
  if (temp_t > min_t){
    t = temp_t;
    n = this->normal;
    return true;
  }
  return false; 
}

