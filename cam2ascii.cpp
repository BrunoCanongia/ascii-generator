#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;


int main(){

  VideoCapture cap(0); 
  cap.set(CAP_PROP_FRAME_WIDTH, 320);
  cap.set(CAP_PROP_FRAME_HEIGHT, 240);

  if(!cap.isOpened()){
    std::cout << "Error opening video stream or file" << std::endl;
    return -1;
  }
	
  Vec3b bgrPixel;
  // density symbols in asc order
  // you can add more
  char symbols[] = {' ', '.', ',', ';', 'o', 's', 'N', '@', '#'};
  
  // 85 is the max value of (0.07 * 255 + 0.72 * 255 + 0.21 * 255) / 3
  // https://en.wikipedia.org/wiki/Grayscale
  // +1 for adjustment
  int step = (85 / sizeof(symbols)) + 1;
  
  while(1){

    Mat frame;
    Mat frameResized;
    
    cap >> frame;
    resize(frame, frameResized, Size(64, 48), 0, 0, INTER_CUBIC);
    
    // clean the terminal screen
    std::cout<< u8"\033[2J\033[1;1H"; 

    for (int i=0; i< frameResized.rows; i++) {
      for (int j=0; j< frameResized.cols ; j++) {
        bgrPixel = frameResized.at<Vec3b>(i,j);
        
        // adjust color variation
        int grayScale = (0.07 * bgrPixel[0] + 0.72 * bgrPixel[1] + 0.21 * bgrPixel[2]) / 3;
        // choose symbol
        std::cout << symbols[(grayScale/step)] << " ";
      }
      std::cout << std::endl;
    }
    
 

    if (frame.empty())
      break;


    imshow( "Frame", frame );


    char c=(char)waitKey(25);
    if(c==27)
      break;
  }
 

  cap.release();

  destroyAllWindows();
	
  return 0;
}
