#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

const char* capture_window = "Capture Window";

int main( ) {
  VideoCapture capture(0);
  // want 1920X1080 ?
  capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
  capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
  if(!capture.isOpened()) {
    cout << "Failed to connect to the camera." << endl;
  }
  namedWindow(capture_window, CV_WINDOW_AUTOSIZE);
  Mat frame;
  while(true) {
    capture >> frame;
    if(frame.empty()) {
      cout << "failed to capture an image" << endl;
      return -1;
    }
    imshow(capture_window, frame);
  }
  return(0);
}
