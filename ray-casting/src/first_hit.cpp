#include "first_hit.h"
#include <iostream>

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  bool does_hit = false;
  Eigen::Vector3d temp_n;
  double temp_t; 
  for(int i=0; i<objects.size();++i){
    auto x=objects[i];
    if ((*x).intersect(ray, min_t, temp_t, temp_n)){
      if (!does_hit || temp_t < t){
        does_hit = true;
        t=temp_t;
        n=temp_n;
        hit_id=i;
      }
    }
  };
  return does_hit;
}

