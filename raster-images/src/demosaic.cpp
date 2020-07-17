#include "demosaic.h"

bool within_bounds(
  const int x,
  const int y,
  const int width,
  const int height
){
  return ((x>=0) && (y>=0) && (x<=height) && (y<=width));
}

// average the topleft, topright, botleft, botright elements
unsigned char avg_unaligned(
  const int x,
  const int y,
  const int width,
  const int height,
  const std::vector<unsigned char> & arr
){
  static int denom=0;
  static int num=0;

  if (within_bounds(x-1, y-1, width, height)){
    denom+=1;
    num+=(int) arr[(x-1)*width + y-1];
  }
  if (within_bounds(x-1, y+1, width, height)){
    denom+=1;
    num+=(int) arr[(x-1)*width + y + 1];
  }
  if (within_bounds(x+1, y-1, width, height)){
    denom+=1;
    num+=(int) arr[(x+1)*width + y-1];
  }
  if (within_bounds(x+1, y+1, width, height)){
    denom+=1;
    num+=(int) arr[(x+1)*width + y + 1];
  }
  // TODO: catch divide by 0
  return (unsigned char) (num/denom);
}

// average the topleft, topright, botleft, botright elements
unsigned char avg_aligned(
  const int x,
  const int y,
  const int width,
  const int height,
  const std::vector<unsigned char> & arr
){
  static int denom=0;
  static int num=0;

  if (within_bounds(x-1, y, width, height)){
    denom+=1;
    num+=(int) arr[(x-1)*width + y];
  }
  if (within_bounds(x+1, y, width, height)){
    denom+=1;
    num+=(int) arr[(x+1)*width + y];
  }
  if (within_bounds(x, y-1, width, height)){
    denom+=1;
    num+=(int) arr[x*width + y-1];
  }
  if (within_bounds(x, y+1, width, height)){
    denom+=1;
    num+=(int) arr[x*width + y + 1];
  }
  // TODO: catch divide by 0
  return (unsigned char) (num/denom);
}

// average the top and bottom elements
unsigned char avg_vertical(
  const int x,
  const int y,
  const int width,
  const int height,
  const std::vector<unsigned char> & arr
){
  static int denom=0;
  static int num=0;

  if (within_bounds(x-1, y, width, height)){
    denom+=1;
    num+=(int) arr[(x-1)*width + y];
  }
  if (within_bounds(x+1, y, width, height)){
    denom+=1;
    num+=(int) arr[(x+1)*width + y];
  }
  // TODO: catch divide by 0
  return (unsigned char) (num/denom);
}

// average the left and right elements
unsigned char avg_hor(
  const int x,
  const int y,
  const int width,
  const int height,
  const std::vector<unsigned char> & arr
){
  static int denom=0;
  static int num=0;

  if (within_bounds(x, y-1, width, height)){
    denom+=1;
    num+=(int) arr[x*width + y-1];
  }
  if (within_bounds(x, y+1, width, height)){
    denom+=1;
    num+=(int) arr[x*width + y + 1];
  }
  // TODO: catch divide by 0
  return (unsigned char) (num/denom);
}

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  bool oddrow=true;
  bool oddcol=true;
  int denom=0;
  int num=0;
  for (int x=0; x<height; ++x){
    for (int y=0; y<width; ++y){
      if (oddrow){
        // B G B G
        if (oddcol){   // Blue part of mosaic

          // average red parts
          rgb[3*x*width + y*3] = avg_unaligned(x,y,width,height,bayer);

          // average green parts
          rgb[3*x*width + y*3 + 1] = avg_aligned(x,y,width,height,bayer);

          // take blue part directly
          rgb[3*x*width + y*3 + 2] = bayer[x*width + y];

        } else{        // Green part of mosaic

          // average red parts
          rgb[3*x*width + y*3] = avg_hor(x,y,width,height,bayer);

          // take green part directly
          rgb[3*x*width + y*3 + 1] = bayer[x*width + y];

          // average blue parts
          rgb[3*x*width + y*3 + 2] = avg_vertical(x,y,width,height,bayer);

        }
      } else{
        // G R G R
        if (oddcol){   // Green part of mosaic

          // average red parts
          rgb[3*x*width + y*3] = avg_hor(x,y,width,height,bayer);

          // take green part directly
          rgb[3*x*width + y*3 + 1] = bayer[x*width + y];

          // average blue parts
          rgb[3*x*width + y*3 + 2] = avg_vertical(x,y,width,height,bayer);

        } else{        // Red part of mosaic

          // take red part directly
          rgb[3*x*width + y*3] = bayer[x*width + y];

          // average green parts
          rgb[3*x*width + y*3 + 1] = avg_aligned(x,y,width,height,bayer);

          // average blue parts
          rgb[3*x*width + y*3 + 2] = avg_unaligned(x,y,width,height,bayer);
        }
      }
      oddcol=!oddcol;
    }
  oddrow=!oddrow;
  }
}
