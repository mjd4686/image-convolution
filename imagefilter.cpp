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

  if(numargs > 5){
    std::cout << "Too many arguments, aborting" << '\n';
    return 0;
  }
  else if(numargs < 5){
    std::cout << "Too few arguments, aborting" << '\n';
    return 0;
  }
  else{
    std::cout << "running convolution with: ";
    CImg<float> dispimg;
    CImg<float> filtputimg(args[4]);
    char filename = *args[4];
    char filt = *args[1];
    char edge = *args[2];
    char file = *args[3];
    if(filt == 's'){
      std::cout << "Sharpen" << '\n';
      if(edge == 'c'){
        dispimg = filter(filtputimg, sharpen);
      }
      else{
        dispimg = filterextend(filtputimg, sharpen);
      }
    }
    else if(filt == 'e'){
      std::cout << "Emboss" << '\n';
      if(edge == 'c'){
        dispimg = filter(filtputimg, emboss);
      }
      else{
        dispimg = filterextend(filtputimg, emboss);
      };
    }
    else if(filt == 'g'){
      std::cout << "Gaussian Blur" << '\n';
      if(edge == 'c'){
        dispimg = filter(filtputimg, gaussianblur);
      }
      else{
        dispimg = filterextend(filtputimg, gaussianblur);
      }
    }
    else if(filt == 'b'){
      std::cout << "Blur" << '\n';
      if(edge == 'c'){
        dispimg = filter(filtputimg, blur);
      }
      else{
        dispimg = filterextend(filtputimg, blur);
      }
    }
    else if(filt == 'd'){
      std::cout << "Edge Detection" << '\n';
      if(edge == 'c'){
        dispimg = filter(filtputimg, edgedetect);
      }
      else{
        dispimg = filterextend(filtputimg, edgedetect);
      }
    }
    else{
      std::cout << "input for filter isn't recognized, aborting" << '\n';
      return 0;
    }
    if(file == 'j'){
      const char* temp = "filteredimage.jpg";
      dispimg.save_jpeg(temp, 100);
    }
    else if(file == 'p'){
      const char* temp = "filteredimage.png";
      dispimg.save_png(temp, 24);
    }
    else if(file == 'b'){
      const char* temp = "filteredimage.bmp";
      dispimg.save_bmp(temp);
    }
    CImgDisplay display(dispimg, "displayed image");
    while(!display.is_closed()){
      display.wait();
    }
  }

  return 0;
}
