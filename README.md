Manual image filtering through convolution, ignoring border pixels that do not
fit the convolution matrix and making them black. This is done with C++ and uses
the CImg library to represent the images and read/edit pixel values. More info
on CImg can be found on http://cimg.eu/ .

A compile command for the code is

clang++ -std=c++11 imagefilter.cpp convolution.cpp -lX11 -lpthread -o runfilter

It takes input in the format:
```
./runfilter F E J image.jpg
```

Where **F** is the filter you want to apply, the current ones are:

s - Sharpen

b - Blur

e - Emboss

g - Gaussian Blur

d - Edge Detection

And **E** is how edges are handled, which currently are:

c - crop

e - extend

And **J** is the format the files could be outputted at, options currently are:

j - jpeg

p - png

b - bmp

n - no file output

And image.jpg is the image you want to apply to the filter on.

Features I may add in the future are:

*option to handle edges through wrapping, extending, or mirroring (extending added)

*allowing for manual filter inputs

*options to save filtered images (done)
