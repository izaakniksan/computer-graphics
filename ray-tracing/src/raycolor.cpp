#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"
#include <iostream>
#include <algorithm> 

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  // std::cout << "TODO: deal with num_recursive_calls=" << num_recursive_calls << std::endl;
  int hit_id=-1;
  double t;
  Eigen::Vector3d n;
  bool ret = first_hit(ray, min_t, objects, hit_id, t, n);
  n.normalize();

  if (ret){
    rgb = blinn_phong_shading(ray, hit_id, t, n, objects, lights);
  }
  return ret;
}
