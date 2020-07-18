#ifndef LDETECTOR_H
#define LDETECTOR_H

#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>

/*
    the lDetector class contains all the functions necessary to perfom roaline detection

*/

class lDetector 
{

    public: 
        cv::Mat noiseD( cv::Mat m_input ); // removes the noise using GaussianBluir
        cv::Mat edgeD( cv::Mat m_noise ); // performs the edge detection, i.e filter the image to obtail only the edges
        cv::Mat mask(cv::Mat img_edge);  // mask the image to take care only  of the output reuslt
        std::vector<cv::Vec2f> houghLines( cv::Mat m_mask); //detect hough lines in edges
        std::vector<std::vector<cv::Vec2f> > lSeparation(std::vector<cv::Vec2f> lines, cv::Mat m_edges); // split detected lines side by side
        float plotLine(cv::Mat m_input,  std::vector<std::vector<cv::Point2f> > line); //Plot the resulting lines

    
    private: 
        double imgcenter;
        bool rflags = false; // shows that there's a left boundary detected
        bool lflags = false; // indicates that there's a right boundary detected 
        

        
};

#endif // LDETECTOR_H