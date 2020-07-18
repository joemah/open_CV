// CREATED BY JOEMAH Magenya
// PHYSICS OF DATA 
// ID 123392
/* 
    *May 2020
    *Computer Vision Asignment

    WHAT THE CODE DOES
    * detect the corresponding houghcircles detected by the cv::CAnny() function using the cv::houghCircles() function
    * modify the parameters of the canny edge detector according to the image you are using.
    * displays the detected cirlces to the original  image
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
cv::Mat DetectLane::d_edge(cv::Mat m_blur)
{   
    cv::Mat mc_edge;
    cv::Canny(m_blur, mc_edge, 190, 10);

    return mc_edge;
}
//std::vector<cv::Vec3f> 
void DetectLane::houghCircles(cv::Mat m_input, cv::Mat m_blur)
{    
    cv::Mat cimg;
    cimg = m_input.clone(); // clone the input image
    std::vector<cv::Vec3f> circles;
    //cv::Canny( m_blur, mc_edge, 200, 20); 
    HoughCircles(m_blur, circles,  cv::HOUGH_GRADIENT, 
                 1,         // accumulator resolution (size of the image / 2 )
                 m_blur.rows,  // minimum distance between two circles 
                 190,         // canny high threshold
                 28,           // minimum number of votes 
                 5, // minimum radius
                 50 // maximum radius
                 );
    for( size_t i = 0; i < circles.size(); i++ )
    {
        cv::Vec3i c = circles[i];
        cv::Point center =  cv::Point(c[0], c[1]);

        // Draw the center of the circle
        cv::circle( cimg, center, 1, cv::Scalar(0,0,255), 3, cv::LINE_AA);
        // Draw the outer circle           
        int radius = c[2];
        cv::circle( cimg, center, radius, cv::Scalar(0,255,0), 3, cv::LINE_AA);
    }
  
    cv::namedWindow("Detected", cv::WINDOW_AUTOSIZE);
        //cv::imshow( "Image", cimg);
    cv::imshow("Detected", cimg);
    cv::imwrite("Circle.jpg", cimg);

}

