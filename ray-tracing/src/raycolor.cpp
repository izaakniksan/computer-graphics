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
  if (ret){
    Eigen::Vector3d q = ray.origin + ray.direction*t;
    rgb = Eigen::Vector3d(0,0,0);  

    // Lambertian:
    auto kd = (*(*objects[hit_id]).material).kd;

    // Ambient:
    // (note that Ia=[0.1,0.1,0.1])
    // https://github.com/alecjacobson/computer-graphics-ray-tracing/issues/1
    auto ka = (*(*objects[hit_id]).material).ka;
    rgb+=ka*0.1;
    for (auto light : lights){
      auto I =(*light).I;
      double temp_max_t;
      Eigen::Vector3d d; // l in textboox
      (*light).direction(q, d, temp_max_t);
      n.normalize();
      I.normalize();
      d.normalize();
      rgb+=(kd.array()*I.array()).matrix()*(std::max(0.0, n.dot(d)));
    }

    // clamp to 1
    for (int i=0; i<3; ++i){
      rgb[i]=std::min(rgb[i],1.0);
    }
  }
  return ret;
}
