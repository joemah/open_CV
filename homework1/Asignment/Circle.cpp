//CREATED BY JOEMAH
/* 
    *May 2020
    *Computer Vision Asignment
*/
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <iostream>
#include <vector>
#include <string> 
#include "DetectLane.h"
#include "Lane.cpp"

// DETECT CIRCLES
/*
    *detect all circles from  the edges of the image 
    *m_blur is the image from the d_Noise function
*/

//std::vector<cv::Vec3f> 
void DetectLane::houghCircles(cv::Mat m_input, cv::Mat m_blur)
{    
    cv::Mat m_edge, cimg;
    cimg = m_input.clone(); // clone the input image
    std::vector<cv::Vec3f> circles;
    cv::Canny( m_blur, m_edge, 200, 20); 
    HoughCircles(m_blur, circles,  cv::HOUGH_GRADIENT, 
                 1,         // accumulator resolution (size of the image / 2 )
                 m_blur.rows/16,  // minimum distance between two circles 
                 200,         // canny high threshold
                 30,           // minimum number of votes 
                 2, // minimum radius
                 50 // maximum radius
                 );
    for( size_t i = 0; i < circles.size(); i++ )
    {
        cv::Vec3i c = circles[i];
        cv::Point center =  cv::Point(c[0], c[1]);

        // Draw the center of the circle
        cv::circle( cimg, center, 2, cv::Scalar(0,0,255), 3, cv::LINE_AA);
        // Draw the outer circle           
        int radius = c[2];
        cv::circle( cimg, center, radius, cv::Scalar(0,255,0), 3, cv::LINE_AA);
    }
  
    cv::namedWindow("Detected", cv::WINDOW_AUTOSIZE);
        //cv::imshow( "Image", cimg);
    cv::imshow("Detected", cimg);
    cv::imwrite("Circle.jpg", cimg);

}

