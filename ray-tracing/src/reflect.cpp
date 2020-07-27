#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  // Page 87 of textbook has formula
  return in - 2*(in.dot(n))*n;
}
