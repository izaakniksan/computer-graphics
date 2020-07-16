#include "reflect.h"
#include <algorithm>

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);
  for (int x=0; x<height; ++x){
    for (int y=0; y<width; ++y){
      for (int z=0; z<num_channels; ++z){
        reflected[num_channels*x*width + y*num_channels +z] = input[num_channels*(x+1)*width - y*num_channels+z];
      }
    }
  }
}
