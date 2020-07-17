#include "simulate_bayer_mosaic.h"
#include <cstdint>

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  // odd rows: B G B G
  // even rows: G R G R
  bool oddrow=true;
  bool oddcol=true;
  const int num_channels = 3;
  for (int x=0; x<height; ++x){
    for (int y=0; y<width; ++y){
      if (oddrow){
        // B G B G
        if (oddcol){
          // Blue
          bayer[x*width +y]=rgb[num_channels*x*width + y*num_channels + 2];
        } else{
          // Green
          bayer[x*width +y]=rgb[num_channels*x*width + y*num_channels + 1];
        }
      } else{
        // G R G R
        if (oddcol){
          // Green
          bayer[x*width +y]=rgb[num_channels*x*width + y*num_channels + 1];
        } else{
          // Red
          bayer[x*width +y]=rgb[num_channels*x*width + y*num_channels];
        }
      }
      oddcol=!oddcol;
    }
  oddrow=!oddrow;
  }
}
