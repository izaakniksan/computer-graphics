#include "viewing_ray.h"
#include <Eigen/Geometry>
// #include <iostream>
void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ray.origin = camera.e;
  ray.direction = -camera.d*camera.w  
                  + (camera.width/width)*(j + 0.5 -width/2)*camera.u 
                  + (camera.height/height)*(height/2 - i -0.5)*camera.v;
  //  std::cout << "direction: " << ray.direction<<std::endl;
}

