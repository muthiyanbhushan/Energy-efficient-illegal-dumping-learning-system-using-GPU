#include "opencv2/opencv.hpp"
#include <stdlib.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include <sstream>
#include <string>
#include <math.h> 

#include<iostream> 
#include <cstdlib>

using namespace cv;


void CaptureImage(char** argv)
{
  VideoCapture cap(1); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
      {  std::cout<<"camera not working"; }
	char path[100];
        Mat frame;
        cap >> frame; // get a new frame from camera
	printf("path argv: %s",argv[0]);
	strcpy(path,"/home/ubuntu/illegal_dumping/");
	strcat(path,argv[1]);
	printf("PATH TO SAVE: %s",path );
        imwrite( path, frame );            // Give absolute path for image or it will store in current directory.using namespace cv;using namespace cv;
}


int main(int argc, char* argv[])
{
   CaptureImage(argv);

}
