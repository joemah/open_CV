//CREATED BY JOEMAH
/* 
    *May 2020
    *Computer Vision Asignment
*/

// WHAT THE CODE DOES
/*
    * receive an input image,
    * transform it to grayscale
    * then apply the GaussianBlur to  smooth the image
    * find the ROI
    * then apply the canny to detect edges
    *  look for lines with hough transform Lines 
    * finally draw the lines obtained from hough
*/
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>

#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "DetectLane.h"
#include "Circle.cpp"

void usage( char** argv); // a function  that gives instuction  on how to use the program

// this is the main function which contains all  the functions used to  detect roadlines and signs

int main( int argc, char** argv )
{   
    usage(argv);
    if (argc != 2 )
    { 
        std::cout << "Not enough arguments, please  enter ./main and the image name\n\n " << std::endl;
        return -1;
    }

    cv::Mat m_input;
    cv::Mat m_blur;
    cv::Mat m_edge;
  
    m_input =  cv::imread(argv[1], cv::IMREAD_COLOR); // read the input image file eg road4.jpg

    DetectLane detectlane; // create the class object 

    m_blur = detectlane.d_Noise(m_input);
    m_edge = detectlane.d_Edge(m_blur);

    detectlane.houghCircles(m_input, m_edge);
    detectlane.houghLines(m_input, m_edge);
    cv::waitKey(0); 
    return 0;
}

void usage(char** argv) // gives the direction of use of the program  to the user
{
    std::cout << "This program performs lane and sign detection, In order to use it, follow the instruction as below\n\n"
        << "load the image as follow \n\n"
        << argv[0] << "navigate to the path conataining the main function\n\n" 
        << "For example  " << argv[0]<< " image.jpg\n\n" //is the name of the program.
        << std::endl;

}