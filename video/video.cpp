#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <limits>
 
using namespace cv;

const char* source_window = "Source";
const char* binary_window = "Binary Image";
const char* clean_window = "Cleaned Image";

/** @function main */
int main( int, char** argv )
{
  char* image_dir = argv[1]; 
  Mat source, binary, clean;
  char source_name[250];
  char binary_name[250];
  char clean_name[250];
  namedWindow ( source_window, CV_WINDOW_AUTOSIZE );
  namedWindow ( binary_window, CV_WINDOW_AUTOSIZE );
  namedWindow ( clean_window, CV_WINDOW_AUTOSIZE );

  for ( int i = 0; i < 600; i++ ) {

    sprintf(source_name, "%s/%dsource.jpg", image_dir, i);
    sprintf(binary_name, "%s/%dbinary.jpg", image_dir, i);
    sprintf(clean_name, "%s/%dclean.jpg", image_dir, i);

    printf("source file is %s\n", source_name);

    /// Load source image and convert it to gray
    //source = imread( source_name, CV_LOAD_IMAGE_COLOR );
    binary = imread( binary_name, CV_LOAD_IMAGE_COLOR );
    //clean = imread( clean_name, CV_LOAD_IMAGE_COLOR );

    //sleep(100);

    //imshow(source_window, source);
    imshow(binary_window, binary);
    //imshow(clean_window, clean);

  }
  
  return(0);
}
