#include "CImg.h"
#include <math.h>
#include <iostream>
#include "imagefilter.h"
using cimg_library::CImg;

CImg<float> filter(CImg<float>& image, CImg<float> filter){
  int cropoffset = filter.width()%2;
  CImg<float> outputimg(image.width(), image.height(), 1, image.spectrum());
  for(int s = 0; s < image.spectrum(); s++){
    for(int x = 0; x < image.width(); x++){
      for(int y = 0; y < image.height(); y++){
        int filtersum = 0;
        int total = 0;
        int filtercenter = filter.width()/2;
        for(int fx = 0; fx < filter.width(); fx++){
          for(int fy = 0; fy < filter.height(); fy++){
            if((0 <= (x + (fx-filtercenter))) && ((x + (fx-filtercenter)) < outputimg.width())
            && (0 <= (y + (fy-filtercenter))) && ((y + (fy-filtercenter)) < outputimg.height())){
              float f = filter(fx,fy,0);
              float img = image((x + (fx-filtercenter)),(y + (fy-filtercenter)),s);
              total = total + f*img;
              //filtersum = filtersum + f;
            }
          }
        }
        int pixel = total;
        if(pixel < 0){
          pixel = 0;
        }
        if(pixel > 255){
          pixel = 255;
        }
        if((x < cropoffset) || (x >= (image.width()-cropoffset)) || (y < cropoffset) || (y >= (image.height()-cropoffset))){
          outputimg(x,y,s) = 0;
        }
        else{
          outputimg(x,y,s) = pixel;
        }
      }
    }
  }
  return outputimg;
}

CImg<float> filterextend(CImg<float>& image, CImg<float> filter){
  int cropoffset = filter.width()%2;
  CImg<float> outputimg(image.width(), image.height(), 1, image.spectrum());
  for(int s = 0; s < image.spectrum(); s++){
    for(int x = 0; x < image.width(); x++){
      for(int y = 0; y < image.height(); y++){
        int filtersum = 0;
        int total = 0;
        int filtercenter = filter.width()/2;
        for(int fx = 0; fx < filter.width(); fx++){
          for(int fy = 0; fy < filter.height(); fy++){
            if((0 <= (x + (fx-filtercenter))) && ((x + (fx-filtercenter)) < outputimg.width())
            && (0 <= (y + (fy-filtercenter))) && ((y + (fy-filtercenter)) < outputimg.height())){
              float f = filter(fx,fy,0);
              float img = image((x + (fx-filtercenter)),(y + (fy-filtercenter)),s);
              total = total + f*img;
              //filtersum = filtersum + f;
            }
            else{
              if((0 >= (x + (fx-filtercenter))) && (0 >= (y + (fy-filtercenter)))){
                float f = filter(fx,fy,0);
                float img = image(0,0,s);
                total = total + f*img;
              }
              else if((0 >= (x + (fx-filtercenter))) && (outputimg.height()-1 <= (y + (fy-filtercenter)))){
                float f = filter(fx,fy,0);
                float img = image(0,outputimg.height()-1,s);
                total = total + f*img;
              }
              else if((outputimg.width()-1 <= (x + (fx-filtercenter))) && (0 >= (y + (fy-filtercenter)))){
                  float f = filter(fx,fy,0);
                  float img = image(outputimg.width()-1,0,s);
                  total = total + f*img;
              }
              else if((outputimg.width()-1 <= (x + (fx-filtercenter))) && (outputimg.height()-1 <= (y + (fy-filtercenter)))){
                float f = filter(fx,fy,0);
                float img = image(outputimg.width()-1,outputimg.height()-1,s);
                total = total + f*img;
              }
              else if((0 > (x + (fx-filtercenter)))){
                float f = filter(fx,fy,0);
                float img = image(0,(y + (fy-filtercenter)),s);
                total = total + f*img;
              }
              else if((outputimg.width() <= (x + (fx-filtercenter)))){
                float f = filter(fx,fy,0);
                float img = image(outputimg.width()-1,(y + (fy-filtercenter)),s);
                total = total + f*img;
              }
              else if((0 > (y + (fy-filtercenter)))){
                float f = filter(fx,fy,0);
                float img = image((x + (fx-filtercenter)),0,s);
                total = total + f*img;
              }
              else{
                float f = filter(fx,fy,0);
                float img = image((x + (fx-filtercenter)),outputimg.height()-1,s);
                total = total + f*img;
              }
            }
          }
        }
        int pixel = total;
        if(pixel < 0){
          pixel = 0;
        }
        if(pixel > 255){
          pixel = 255;
        }
        outputimg(x,y,s) = pixel;
      }
    }
  }
  return outputimg;
}
