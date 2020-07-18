// CREATED BY JOEMAH Magenya
// PHYSICS OF DATA 
// ID 123392
/* 
    *May 2020
    *Computer Vision Asignment
*/


#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>

#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include "DetectLane.h"
// #include "Lane.cpp"
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
    cv::Mat m_blur;  // declare variables 
    cv::Mat m_edge;
    cv::Mat mc_edge;

    m_input =  cv::imread(argv[1], cv::IMREAD_COLOR); // read the input image file eg argv[1] can be replaced directly with 
                                                        // "road4.jpg"

    DetectLane detectlane; // declare an object of a class DetectLane


    m_blur = detectlane.d_Noise(m_input); // access the functions to compute the corresponding images
    m_edge = detectlane.d_Edge(m_blur);
    mc_edge = detectlane.d_edge(m_blur);

    detectlane.houghCircles(m_input, mc_edge); // invoke the houghCircles and houghLines  functions to show the results
    detectlane.houghLines(m_input, m_edge);
    cv::waitKey(0); // wait for the user to print any key to exit the program
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


// COMMENTS 
/* 

    * In this project lane detectection is performed by  using opencv library and c++ 
    * receive an input image,
    * transform it to grayscale
    * then apply the GaussianBlur to  smooth the image
    * find the ROI if necessary 
    * then apply the canny to detect edges
    * look for lines with hough transform Lines 
    * finally draw the lines obtained from hough
    
    ** STEPS EXPLAINED** 

     >> The Canny edge detector is an edge detection operator that uses a 
        multi-stage algorithm to detect a wide range of edges in images.
     >> Edge detection results are highly sensitive to image noise.
     >> One way to get rid of the noise on the image, is by applying Gaussian blur to smooth it
     >> To do so, image convolution technique is applied with a Gaussian Kernel (kxk) where k is odd >= 3. 
        The kernel size depends on the expected blurring effect
     >> Here a kernel of size(9 x 9) is used.
     >> Edges correspond to a change of pixel's intensity. To detect it, the easiest way is to apply filters that 
        highlight this intensity change in both directions: x and y
     >> Apply the direcltly opencv functions  cv::houghCircle and cv::HoughLines() to detect corresponding circles or lines
    
    
  
    *** In order to detect perfectly  the lines, one has to play around with the parameters for a specific image
    *** here road4.jpg is used as an example 
    *** The canny threshold has to be chosen in such a way that the image can show clear edges. 
    *** The choise of parameters is of paramount in edge detection and circle detection 
    *** 

*/