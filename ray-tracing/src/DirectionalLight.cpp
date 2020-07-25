#include "DirectionalLight.h"
#include <limits>
#include <iostream>

void DirectionalLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  d = -this->d;
  max_t = d.norm();
  d.normalize();
}

