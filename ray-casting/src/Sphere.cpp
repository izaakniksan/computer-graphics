#include "Sphere.h"
#include "Ray.h"
#include <iostream>
#include <cmath>

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  // we are given center and radius (this->center and this->radius)
  auto d = ray.direction;
  auto e = ray.origin;
  auto c = this->center;
  auto R = this->radius;
  double discrim = (pow(d.dot(e-c),2)) - (d.dot(d))*((e-c).dot(e-c)-pow(R,2));
  if (discrim < 0){
    return false;
  } else if (discrim == 0) {
    double temp_t = -d.dot(e-c)/(d.dot(d));
    if (temp_t > min_t){
      t=temp_t;
      n=((e+t*d)-c)/R;
      return true;
    } else{
      return false;
    } 
  } else{

    double t_minus = (-d.dot(e-c) - sqrt(discrim))/(d.dot(d));
    if (t_minus > min_t){
      t=t_minus;
      n=((e+t*d)-c)/R;
      return true;
    }
  
    double t_plus = (-d.dot(e-c) + sqrt(discrim))/(d.dot(d));
    if (t_plus > min_t){
      t=t_plus;
      n=((e+t*d)-c)/R;
      return true;
    }
    return false; 
  } 
}

