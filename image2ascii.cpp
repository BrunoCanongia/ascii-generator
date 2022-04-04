// Brunoid - Image to ASCII

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
using namespace cv;


int main(int argc, char** argv)
{
    // load image from arg
    if (!argv[1]) {
      std::cout << "No image" << std::endl;
      return 1;
    }
    std::string image_path = samples::findFile(argv[1]);
    Mat img = imread(image_path, IMREAD_COLOR);
    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    
    Vec3b bgrPixel;
    
    // density symbols in asc order
    // you can add more
    char symbols[] = {' ', '.', ',', ';', 'o', 's', 'N', '@', '#'};
  
    // 85 is the max value of (0.07 * 255 + 0.72 * 255 + 0.21 * 255) / 3
    // https://en.wikipedia.org/wiki/Grayscale
    // +1 for adjustment
    int step = (85 / sizeof(symbols)) + 1;
    
    
    // get every pixel grayscale
    for (int i=0; i< img.rows; i++) {
      for (int j=0; j< img.cols ; j++) {
        bgrPixel = img.at<Vec3b>(i,j);
        
        // adjust color variation
        int grayScale = (0.07 * bgrPixel[0] + 0.72 * bgrPixel[1] + 0.21 * bgrPixel[2]) / 3;
        // choose symbol
        std::cout << symbols[grayScale/step] << " ";
      }
      std::cout << std::endl;
    }
    
    return 0;
}
