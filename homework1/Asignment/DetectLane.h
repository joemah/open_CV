//CREATED BY JOEMAH
/* 
    *May 2020
    *Computer Vision Asignment
*/
#ifndef DETECTLANE_H
#define DETECTLANE_H

#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>

// THE DETECTOCTOR CLASS 

/* the detectlane class contains all  functions necessary for the detection.
 */

class DetectLane
{
    public:
        cv::Mat d_Noise( cv::Mat m_input); // blurs the image using the GaussianBlur function
        // void ROI( cv::Mat& m_input, cv::Mat& dst, const cv::Point** vertices, int nVertices); // select the region of interest
        cv::Mat d_Edge( cv::Mat m_noise );// detect the edges from  the denosed image using the cv::Canny 
        void houghLines( cv::Mat m_input, cv::Mat m_edge); // detect the lanes from  the  edges
        void houghCircles( cv::Mat m_input, cv::Mat m_blur); // detect the circles from  the edges of the image
    
    private:
        double center;
        bool rflags = false;
        bool lflags = false;

}; 

#endif // DETECTLANE_H
