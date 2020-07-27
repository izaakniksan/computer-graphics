#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"
#include <iostream>
#include <algorithm> 

const int max_rec_calls = 5;
const double epsilon = 0.0001;

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  if (num_recursive_calls > max_rec_calls){
    return false;
  }
  int hit_id=-1;
  double t;
  Eigen::Vector3d n;
  bool ret = first_hit(ray, min_t, objects, hit_id, t, n);
  n.normalize();

  if (ret){
    rgb = blinn_phong_shading(ray, hit_id, t, n, objects, lights);
    // reflection
    auto km = (*(*objects[hit_id]).material).km;
    Ray reflect_ray = {
      (ray.origin + t*ray.direction), // origin
      reflect(ray.direction, n) // direction
    };
    Eigen::Vector3d rec_rgb;
    if (raycolor(reflect_ray,epsilon,objects,lights,num_recursive_calls+1,rec_rgb)){
      rgb += (km.array()*rec_rgb.array()).matrix();
    }
  }
  return ret;
}
