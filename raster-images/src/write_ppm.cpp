#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>
#include <string>
using namespace std;
bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");
  
  // ppm header example:
  // P3 (magic number)
  // 50 6 (width height)
  // 255 (max value)
  // std::string PPM_HEADER;
  // PPM_HEADER = "P3\n" + to_string("255\n") + to_string(width) + " " + to_string(height) + "\n" ;

  ofstream ofile(filename);
  ofile << "P3" << endl;
  ofile << width << " " << height << endl;
  ofile << "255" << endl;

  if (num_channels == 1) {
    // grayscale image, r=g=b
    for (int x=0; x<height; ++x){
      for (int y=0; y<width; ++y){
        ofile << (int) data[x*width + y] << " ";
        ofile << (int) data[x*width + y] << " ";
        ofile << (int) data[x*width + y] << " ";
      }
      ofile << endl;
    }
    ofile.close();
    return true;

  } else if (num_channels == 3) {
    // rgb image
    for (int x=0; x<height; ++x){
      for (int y=0; y<width; ++y){
        ofile << (int) data[3*x*width + 3*y] << " ";
        ofile << (int) data[3*x*width + 3*y + 1] << " ";
        ofile << (int) data[3*x*width + 3*y + 2] << " ";
      }
      ofile << endl;
    }
    ofile.close();
    return true;
  } else{
    cout << "ERROR! numchannels is neither 1 nor 3" << endl;
    ofile.close();
    return false;
  }

  return false;
}
