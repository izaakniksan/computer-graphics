#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  
    Eigen::Vector3d q = ray.origin + ray.direction*t;
    Eigen::Vector3d rgb = Eigen::Vector3d(0,0,0);  

    // Lambertian:
    auto kd = (*(*objects[hit_id]).material).kd;

    // Blinn Phong:
    auto ks = (*(*objects[hit_id]).material).ks;
    auto p = (*(*objects[hit_id]).material).phong_exponent;

    // Ambient:
    // (note that Ia=[0.1,0.1,0.1])
    // https://github.com/alecjacobson/computer-graphics-ray-tracing/issues/1
    auto ka = (*(*objects[hit_id]).material).ka;
    rgb+=ka*0.1;
    for (auto light : lights){
      auto I =(*light).I;
      double temp_max_t;
      Eigen::Vector3d d; // l in textboox
      Eigen::Vector3d v = - ray.direction; // v in textbook
      (*light).direction(q, d, temp_max_t);
      I.normalize();
      d.normalize();

      // Is point q in shadow?
      Ray shadow_ray;
      shadow_ray.origin = q;
      shadow_ray.direction = d;
      int garbage;
      double garbage2;
      Eigen::Vector3d garbage3;
      if (!first_hit(shadow_ray, 0.00001, objects, garbage, garbage2, garbage3)) {

        Eigen::Vector3d h = (v + d).normalized();
        rgb+=(kd.array()*I.array()).matrix()*(std::max(0.0, n.dot(d))); // Lambertian
        rgb+= (ks.array()*I.array()).matrix()*(std::max(0.0, pow(n.dot(h),p))); // Blinn 
      }
    }

    // clamp to 1
    for (int i=0; i<3; ++i){
      rgb[i]=std::min(rgb[i],1.0);
    }

    return rgb;
}
