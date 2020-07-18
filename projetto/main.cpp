#include <iostream>
#include <string> 
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "lDetector.h"
#include "lineDetector.cpp"

//void usage();

int main( int argc, char * argv[] )
{
    //usage();

    if (argc != 2)
    {
        std::cout << "Not enough augments follow the instructions " << std::endl;
        return -1;

    }
    // the input argument is merely the image location

    cv::Mat img = cv::imread(argv[1]);
    lDetector ldetector; // create the class object
    cv::Mat m_denoise;
    cv::Mat m_edges;
    cv::Mat m_mask;
    std::vector<cv::Vec2f> h_lines;
    float plot = -1.0;
    std::vector<std::vector<cv::Point2f> > lrlines; // left and right lines
    std::vector<std::vector<cv::Point2f> > line;
    std::string turn;
    
    // remove noise with a Gaussian filter 
    m_denoise = ldetector.noiseD(img);
    
    //detect edges in the image 
    m_edges = ldetector.edgeD(m_denoise);

    // mask the image to get only the required output
    m_mask = ldetector.mask(m_edges);

    // get the Hough lines in the image
    h_lines = ldetector.houghLines(m_mask);

    if (!h_lines.empty())
    {
        // separate lines into right and left
        lrlines = ldetector.lSeparation(h_lines, m_edges);
        //plot the detection lane

        plot = ldetector.plotLine(img, lrlines);
    
    }
    else
        {
            plot = -1;
        }
    return plot;


}
