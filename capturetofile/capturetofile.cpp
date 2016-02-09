#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

int main( ) {
  const char* source_filename = "source.jpg";
  const char* binary_filename = "binary.jpg";
  const char* clean_filename = "clean.jpg";
  char this_source_filename[255];
  char this_binary_filename[255];
  char this_clean_filename[255];

  VideoCapture capture(1);
  // want 1920X1080 ?
  capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
  capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
  capture.set(CV_CAP_PROP_FPS, 10);
  if(!capture.isOpened()) {
    cout << "Failed to connect to the camera." << endl;
  }
  Mat frame, framecopy, hsv, binary, tmpBinary, clean;
//Change maxFrames for maximum amount of frames saved.
  int maxFrames = 600;
  for(int i=0; i < maxFrames; i++) {
    cout << "Frame " << i << endl;
    capture >> frame;
    if(frame.empty()) {
      cout << "failed to capture an image" << endl;
      return -1;
    }
    framecopy = frame.clone();
    sprintf(this_source_filename, "%d%s", i, source_filename);
    imwrite(this_source_filename, framecopy);
    
    cvtColor(framecopy, hsv, CV_BGR2HSV);
    inRange(hsv, Scalar(30,22,158), Scalar(100,255,255), binary);
    sprintf(this_binary_filename, "%d%s", i, binary_filename);
    //imwrite(this_binary_filename, binary);

    std::vector < std::vector<Point> > contours;
    std::vector < std::vector<Point> > filteredContours;
    tmpBinary = binary.clone();
    findContours(tmpBinary, contours, RETR_LIST, CHAIN_APPROX_NONE);
    tmpBinary.release();
    cvtColor( binary, clean, CV_GRAY2RGB );
    clean.setTo(Scalar(255,255,255));

    for (size_t contourIdx = 0; contourIdx < contours.size(); contourIdx++) {
      Point2d center;
      Moments moms = moments(Mat(contours[contourIdx]));

      // filter blobs which are too small
      double area = moms.m00;
      if ( area < 400 ) {
        continue;
      }
      center = Point2d(moms.m10 / moms.m00, moms.m01 / moms.m00);
      circle(clean, center, 2, Scalar(0), 2, 8, 0);
      filteredContours.push_back(contours[contourIdx]);
    }

    drawContours( clean, filteredContours, -1, Scalar(0,255,0) );
    sprintf(this_clean_filename, "%d%s", i, clean_filename);
    //imwrite(this_clean_filename, clean);
  }
  return(0);
}
