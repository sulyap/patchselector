#include <iostream>
#include <sstream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <opencv2/opencv.hpp>

#define LINE_COLOR Scalar(0, 0, 255)
#define LINE_THICKNESS 5

using namespace std;
using namespace cv;

Mat main_image;
Mat buffer_image;
const char *windowName = "MAIN WINDOW";
int patch_width;
int patch_height;
int image_width;
int image_height;
const char *directory;

void syntax()
{
  printf("patchselector [image] [w] [h] [dir]\n");
}

bool dirExists(const char *dir_path) 
{
  struct stat info;

  if(stat(dir_path, &info) != 0)
  {
    printf("Cannot access %s\n", dir_path);
    return false;
  } 
  else if(info.st_mode & S_IFDIR)
  {
    printf("%s is a directory\n", dir_path); 
    return true;
  }
  else
  {
    printf("%s is not a directory\n", dir_path); 
    return false;
  }
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
  rectangle(buffer_image, start_point, end_point, LINE_COLOR, LINE_THICKNESS);

  // draw rectangle on buffer image and display on window
  imshow(windowName, buffer_image);

  // timestamp generation for image filename
  std::time_t now = std::time(NULL);
  std::stringstream ss;

  switch(event)
  {
    case CV_EVENT_MOUSEMOVE:
      break;
    case CV_EVENT_LBUTTONDOWN:
      break;
    case CV_EVENT_LBUTTONUP:
      printf("Selecting patch at start_point(%d, %d) and end_point(%d, %d)\n", start_x, start_y, end_x, end_y);

      // Save file to directory
      ss << directory << "/" << now << ".jpg";
      std::string filename = ss.str();
      printf("Saving filename: %s\n", ss.str().c_str());
      imwrite(ss.str().c_str(), main_image(Rect(start_x, start_y, patch_width, patch_height)));
      break;
  }
}


int main(int argc, char **argv)
{ 
  if(argc != 5)
  {
    syntax();
    exit(-1);
  }

  if(!dirExists(argv[4])) 
  {
    exit(-1);
  }
  else 
  {
    directory = argv[4];
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
