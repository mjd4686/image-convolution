#include <iostream>
#include "CImg.h"
#include "imagefilter.h"
using cimg_library::CImg;
using cimg_library::CImgDisplay;

int main(int numargs, char* args[]){

  CImg<float> edgedetect(3,3,1,1,
  -1,-1,-1,
  -1,8,-1,
  -1,-1,-1);
  CImg<float> sharpen(3,3,1,1,
  0,-1,0,
  -1,5,-1,
  0,-1,0);
  CImg<float> emboss(3,3,1,1,
  -2,-1,0,
  -1,1,1,
  0,1,2);
  float n = 1.0/9.0;
  CImg<float> blur(3,3,1,1,
  n,n,n,
  n,n,n,
  n,n,n);
  float gb = 1.0/16.0;
  CImg<float> gaussianblur(3,3,1,1,
  gb*1,gb*2,gb*2,
  gb*2,gb*4,gb*2,
  gb*1,gb*2,gb*1);

  if(numargs > 3){
    std::cout << "Too many arguments, aborting" << '\n';
    return 0;
  }
  else if(numargs < 3){
    std::cout << "Too few arguments, aborting" << '\n';
    return 0;
  }
  else{
    std::cout << "running convolution with: ";
    CImg<float> dispimg;
    CImg<float> inputimg(args[2]);
    char in = *args[1];
    if(in == 's'){
      std::cout << "Sharpen" << '\n';
      dispimg = filter(inputimg, sharpen);
    }
    else if(in == 'e'){
      std::cout << "Emboss" << '\n';
      dispimg = filter(inputimg, emboss);
    }
    else if(in == 'g'){
      std::cout << "Gaussian Blur" << '\n';
      dispimg = filter(inputimg, gaussianblur);
    }
    else if(in == 'b'){
      std::cout << "Blur" << '\n';
      dispimg = filter(inputimg, blur);
    }
    else if(in == 'd'){
      std::cout << "Edge Detection" << '\n';
      dispimg = filter(inputimg, edgedetect);
    }
    else{
      std::cout << "Input for filter isn't recognized, aborting" << '\n';
      return 0;
    }
    CImgDisplay display(dispimg, "displayed image");
    while(!display.is_closed()){
      display.wait();
    }
  }

  return 0;
}
