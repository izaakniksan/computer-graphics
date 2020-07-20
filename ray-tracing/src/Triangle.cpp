#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>
#include <unsupported/Eigen/MatrixFunctions>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{

  Eigen::Vector3d a,b,c;
  a = std::get<0>(this->corners);
  b = std::get<1>(this->corners);
  c = std::get<2>(this->corners);

  // use textbook page 78 formula:
  double xa = a[0];
  double xb = b[0];
  double xc = c[0];
  double ya = a[1];
  double yb = b[1];
  double yc = c[1];
  double za = a[2];
  double zb = b[2];
  double zc = c[2];
  double xd = ray.direction[0];
  double yd = ray.direction[1];
  double zd = ray.direction[2];

  Eigen::Matrix3d A(3,3);
  A(0,0) = xa-xb;
  A(0,1) = xa-xc;
  A(0,2) = xd;
  A(1,0) = ya - yb;
  A(1,1) = ya - yc;
  A(1,2) = yd;
  A(2,0) = za-zb;
  A(2,1) = za-zc;
  A(2,2) = zd;

  Eigen::Vector3d RHS = a-ray.origin;
  Eigen::Vector3d soln = A.colPivHouseholderQr().solve(RHS);

  double beta = soln[0];
  double gamma = soln[1];
  double temp_t = soln[2];

  if ((temp_t < min_t) 
     || (gamma < 0) || (gamma > 1) 
     || (beta < 0 ) || (beta > (1-gamma))){
    return false;
  }
  n = (a-b).cross(a-c);
  n.normalize();
  t=temp_t;
  return true;
}


