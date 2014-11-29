#include <iostream>
#include <sstream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat main_image;
Mat buffer_image;
const char *windowName = "MAIN WINDOW";
int patch_width;
int patch_height;
int image_width;
int image_height;

void syntax()
{
  printf("patchselector [image] [w] [h]\n");
}

void onmouse(int event, int x, int y, int flags, void *params)
{
  main_image.copyTo(buffer_image);

  // rect start point
  int start_x = x - (patch_width / 2);
  int start_y = y - (patch_height / 2);
  Point start_point(start_x, start_y);

  // rect end point
  int end_x = x + (patch_width / 2);
  int end_y = y + (patch_width / 2);
  Point end_point(end_x, end_y);

  //printf("Drawing rectangle with start_point(%d, %d) and end_point(%d, %d)\n", start_x, start_y, end_x, end_y);
  rectangle(buffer_image, start_point, end_point, Scalar(0, 0, 255));

  // draw rectangle on buffer image and display on window
  imshow(windowName, buffer_image);

  // timestamp generation for image filename
  std::time_t now = std::time(NULL);
  std::tm *ptm = std::localtime(&now);
  char buffer[32];

  switch(event)
  {
    case CV_EVENT_MOUSEMOVE:
      break;
    case CV_EVENT_LBUTTONDOWN:
      break;
    case CV_EVENT_LBUTTONUP:
      printf("Selecting patch at start_point(%d, %d) and end_point(%d, %d)\n", start_x, start_y, end_x, end_y);
      break;

  }
}


int main(int argc, char **argv)
{ 
  if(argc != 4)
  {
    syntax();
    exit(-1);
  }

  main_image = imread(argv[1]);

  patch_width = atoi(argv[2]);
  patch_height = atoi(argv[3]);

  image_width = main_image.rows;
  image_height = main_image.cols;

  namedWindow(windowName, CV_WINDOW_KEEPRATIO);
  setMouseCallback(windowName, onmouse, 0);

  imshow(windowName, main_image);

  waitKey(0);

  // Lazy way to clean up windows
  destroyAllWindows();

  return 0;
}
