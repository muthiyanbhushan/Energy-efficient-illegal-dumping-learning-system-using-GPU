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

#define  TEST_IMAGE "/home/ubuntu/illegal_dumping/Test_image/t_image.jpg"
#define  BASE_IMAGE "/home/ubuntu/illegal_dumping/Base_image/b_image.jpg"
#define  CROPPED_IMAGE "/home/ubuntu/illegal_dumping/Cropped_image/image"

//include "Blob.h"

using namespace cv;


// global variables ///////////////////////////////////////////////////////////////////////////////
const cv::Scalar SCALAR_BLACK = cv::Scalar(0.0, 0.0, 0.0);
const cv::Scalar SCALAR_WHITE = cv::Scalar(255.0, 255.0, 255.0);
const cv::Scalar SCALAR_BLUE = cv::Scalar(255.0, 0.0, 0.0);
const cv::Scalar SCALAR_GREEN = cv::Scalar(0.0, 200.0, 0.0);
const cv::Scalar SCALAR_RED = cv::Scalar(0.0, 0.0, 255.0);
//default capture width and height
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;

///////////////////////////////////////////////////////////////////////////////////////////////////


void drawObject(int x, int y, Mat &frame) {


	circle(frame, Point(x, y), 20, Scalar(0, 255, 0), 2);
	if (y - 25>0)
		line(frame, Point(x, y), Point(x, y - 25), Scalar(0, 255, 0), 2);
	else line(frame, Point(x, y), Point(x, 0), Scalar(0, 255, 0), 2);
	if (y + 25<FRAME_HEIGHT)
		line(frame, Point(x, y), Point(x, y + 25), Scalar(0, 255, 0), 2);
	else line(frame, Point(x, y), Point(x, FRAME_HEIGHT), Scalar(0, 255, 0), 2);
	if (x - 25>0)
		line(frame, Point(x, y), Point(x - 25, y), Scalar(0, 255, 0), 2);
	else line(frame, Point(x, y), Point(0, y), Scalar(0, 255, 0), 2);
	if (x + 25<FRAME_WIDTH)
		line(frame, Point(x, y), Point(x + 25, y), Scalar(0, 255, 0), 2);
	else line(frame, Point(x, y), Point(FRAME_WIDTH, y), Scalar(0, 255, 0), 2);

	putText(frame, "x y", Point(x, y + 30), 1, 1, Scalar(0, 255, 0), 2);

}

void CropImage(int x, int y,int dim,Mat &frame,int version)
{
                 std::stringstream ss;
                 ss<<version;
                 std::string Strng = CROPPED_IMAGE + ss.str();
                 Strng += ".jpg";
                 cv::Rect roi;
                 cv::Mat crop;         
                 roi.x = x - (dim);
                 roi.y = y - (dim);
           
                 if(roi.x<0)
                    roi.x = 0;
                 if(roi.y<0)
                    roi.y = 0;               
                 
                 roi.width = frame.size().width - (roi.x+dim);
                 roi.height = frame.size().height - (roi.y);                 
                 crop = frame(roi);
                 Mat img = crop.clone();
                 Mat I1;
                 Size size(640,480);
                 resize(img,I1,size);
                 imwrite( Strng, I1 );
}

void CaptureImage()
{
  VideoCapture cap(1); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
      {  std::cout<<"camera not working"; }

        Mat frame;
        cap >> frame; // get a new frame from camera
        imwrite( "Gray_Imagecp.jpg", frame );
}

int main(int argc, char** argv)
{


    Mat imgFrame1=imread(TEST_IMAGE, CV_LOAD_IMAGE_UNCHANGED);
    Mat imgFrame2=imread(BASE_IMAGE, CV_LOAD_IMAGE_UNCHANGED);

       Mat I1;
       Mat I2;
    
       Size size(640,480);

       resize(imgFrame1,I1,size);
       resize(imgFrame2,I2,size);
    
       Mat imgFrame1Copy = I1.clone();
       Mat imgFrame2Copy = I2.clone();


       Mat imgDifference;
       Mat imgThresh;

       cvtColor(imgFrame1Copy, imgFrame1Copy, CV_BGR2GRAY);
       cvtColor(imgFrame2Copy, imgFrame2Copy, CV_BGR2GRAY);
        
       GaussianBlur(imgFrame1Copy, imgFrame1Copy, cv::Size(5, 5), 0);
       GaussianBlur(imgFrame2Copy, imgFrame2Copy, cv::Size(5, 5), 0);

       absdiff(imgFrame1Copy, imgFrame2Copy, imgDifference);

       threshold(imgDifference, imgThresh, 30, 255.0, CV_THRESH_BINARY);
       
       //imshow("imgThresh", imgThresh);
      

       Mat structuringElement3x3 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
       Mat structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
       Mat structuringElement7x7 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
       Mat structuringElement9x9 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9));


       erode(imgThresh, imgThresh, structuringElement5x5);

       erode(imgThresh, imgThresh, structuringElement5x5);

       dilate(imgThresh, imgThresh,structuringElement5x5);
       dilate(imgThresh, imgThresh,structuringElement5x5);
       dilate(imgThresh, imgThresh, structuringElement5x5);
       dilate(imgThresh, imgThresh, structuringElement5x5);

         

           // imshow("imgThresh2", imgThresh);
       Mat imgThreshCopy = imgThresh.clone();
       int version = 1;
        
        

       std::string Strng = "IMG";
       //imshow(Strng, imgThreshCopy);
        waitKey(0);

        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;

        findContours(imgThreshCopy, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        std::cout<<hierarchy.size()<<std::endl;

        Mat imgContours(imgThresh.size(), CV_8UC3, SCALAR_BLACK);

        drawContours(imgContours, contours, -1, SCALAR_WHITE, -1);
        //imshow("imgContours", imgContours);
  
           

// Object detection Code
        int i=0;
        double refArea = 0;
	if (hierarchy.size() > 0) 
	{ 		
	 int numObjects = hierarchy.size();
	 for (int index = 0; index >= 0; index = hierarchy[index][0]) { 				
	      Moments moment = moments((cv::Mat)contours[index]); 				
	      double area = moment.m00;
              std::cout<<"area is: "<<area<<std::endl;
              if( area > 2000 )
                {
                  i++;
                  int x = moment.m10 / area; 					
                  int y = moment.m01 / area;
                  std::cout<<x<<" "<<y<<std::endl;
                  //imshow("Frame1tst", imgFrame1Copy);
                 // drawObject(x, y, imgFrame1Copy);
                   int dim = std::sqrt(area);
                  CropImage(x,y,dim,I1,i);
                  //break;
                }
              }
        }
        
      
     


    return 0;

}
