#include "rgb_to_gray.h"

void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray)
{
  gray.resize(height*width);
  const int num_channels=3;
  for (int x=0; x<height; ++x){
    for (int y=0; y<width; ++y){
      int avg=0;
      for (int z=0; z<num_channels; ++z){
         avg+= rgb[num_channels*x*width + y*num_channels+z];
      }
      gray[x*width + y] = (unsigned char) (avg/3);
    }
  }
}


