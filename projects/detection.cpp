#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>

#include <iostream>
#include <sstream>
#include <set>
#include <cmath>
#include <map>
#include <algorithm>
#include <deque>
#include <string>
#include <vector>
#include <list>



void usage(); // funtion that  instruct the user how to use the program works 

class Canny 
{
    public:
    cv::Mat img, gray, edge, imgblur;
    Canny()
    {
        // input image, grayscale of input image, intermediate blurred image, canny edge image
        // ask the user to input an image
        std::cout << "please enter an image " << std::endl;
        std::string imgaddr;
        std::cin >> imgaddr;
        std::cout << "Searching for " + imgaddr << std::endl;
        img  = cv::imread(imgaddr);
        // check  if the user indeed input an image
        if (img.empty())                 // f no image or unable to open the image,
        {
            std::cout << "Error not an image \n\n"; // show an error message on the command line and
            //return -1; // exti the program
        }
        cvtColor(img, gray, cv::COLOR_RGB2GRAY); // convert to grayscale
        cv::GaussianBlur( gray, imgblur, cv::Size(5, 5), 1.5 ); // input image, output image, smoothing window width and height, sigma value wheich determines how much the image will  be smoothed
        cv::Canny( imgblur, edge, 50, 150, 3); // input image, output image, low threshold, high threshold, aperture size for the Sobel operator (set to default)
        cv::namedWindow("Canny Edges", cv::WINDOW_AUTOSIZE);
        //cv::namedWindow("Original Image", cv::WINDOW_AUTOSIZE);
        cv::imshow("Orignal Image", img);
        //cv::imshow("Canny Edges", edge); // display the edges of the image
    }   
    
};


class Hough: public Canny
{
   public: Hough() : Canny()
   {   
        //std::<vector> Mat lines;
        cv::Mat dst, cdst;
        cv::cvtColor(edge, cdst, cv::COLOR_GRAY2BGR);
        std::vector<cv::Vec2f> lines;
      
        HoughLines(edge, lines, 1, CV_PI/360 , 150, 0, 0 );

        // draw the lines 
     
        for ( size_t i = 0; i < lines.size(); i++ )
        {
            float rho = lines[i][0], theta = lines[i][1];
            cv::Point pt1, pt2;
            double a = cos(theta), b  = sin(theta);
            double x0 = a*rho, y0 = b*rho;
            pt1.x = cvRound( x0 + 1000*(-b) );
            pt1.y = cvRound( y0 + 1000*(a) );
            pt2.x = cvRound( x0 - 1000*(-b) );
            pt2.y = cvRound( y0 - 1000*(a) );
            cv::line( cdst, pt1, pt2, cv::Scalar(0, 0, 255)//, 3, cv::LINE_AA 
                );
        }
        cv::namedWindow("Detected lines", cv::WINDOW_AUTOSIZE);
        cv::imshow("Detected lines ", cdst);
    
    }
        
   
};
class Circles: public Canny
{
    public: Circles() : Canny()
    {   cv::Mat cimg, edges;
        cimg = img.clone();
        cv::Canny( imgblur, edges, 200, 20); // input image, output image, low threshold, high threshold, aperture size for the Sobel operator (set to default)
        std::vector<cv::Vec3f> circles;
        HoughCircles(imgblur, circles, cv::HOUGH_GRADIENT,
                    1,  // accumulator resolution (size of the image / 2 )
                    60, // minimum distance between two circles 
                    200, // canny high threshold
                    20, // minimum number of votes 
                    0, // minimum radius
                    0 // maximum radius
                    );
        
        for( size_t i = 0; i < circles.size(); i++ )
        {
            cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            // Draw the outer circle
            cv::circle( cimg, center, radius, cv::Scalar(0, 255, 0), 1,8, 0);
            // Draw the center of the circle
            cv::circle( cimg, center, 3, cv::Scalar(0, 0, 255), -1, 8, 0);
        }
        // // compute distance transform
        // cv::Mat dt;
        // cv::distanceTransform(255-(edges>0), dt, cv::DIST_L2, 3);
        // cv::namedWindow("distance transform");
        // cv::imshow("distance transform", dt/255.0f);

        // // test for semi-circles 

        // float minInlierDist = 2.0f;
        // for ( size_t i = 0; i < circles.size(); i++ )
        // {
        //     // test inlier percentage:
        //     // sample the circle and check for distance to  the next edge
        //     unsigned int counter = 0;
        //     unsigned int inlier = 0;

        //     cv::Point2f center((circles[i][0]), (circles[i][1]));
        //     float radius = (circles[i][2]);

        //     // maximal distance of inlier might depend on the size of the circle
        //     float maxInlierDist = radius/25.0f;
        //     if(maxInlierDist<minInlierDist) maxInlierDist = minInlierDist;
        //     // maybe parameter incrementation might depend on circle size!

        //     for ( float t=0; t<2*3.14159265359f; t+=0.1f)
        //     {
        //         counter++;
        //         float cX = radius*cos(t) + circles[i][0];
        //         float cY = radius*sin(t) + circles[i][1];

        //         if (dt.at<float>(cY,cX) < maxInlierDist )
        //         {
        //             inlier++;
        //             cv::circle(cimg, cv::Point2i(cX,cY),3,cv::Scalar(0,255,0));

        //         }
        //         else
        //         {
        //             cv::circle(cimg, cv::Point2i(cX,cY), 3, cv::Scalar(255, 0, 0));

        //         }
        //         std::cout << 100.0f*(float)inlier/(float)counter << " % of circles with radius " << radius << " detected" << std::endl;

        //     }
        // }
        cv::namedWindow("Detected Circles", cv::WINDOW_AUTOSIZE);
        //cv::imshow( "Image", cimg);
        cv::imshow("Detected Circles", cimg);



    }
};


int main( int argc, char** argv )
{   
    usage();
    // Hough lines;
     //Canny m_canny;
     //Hough m_hough;
    // Circles circles;
    // cv::Mat img;
    //Canny();
    Hough();
    //Circles();
    //m_hough.Canny();
    //m_hough.myTransform();
    // img = cv::imread("road1.png");
   
    // cv::namedWindow("original Image", cv::WINDOW_AUTOSIZE);
    // cv::imshow("Original Image", scr);

    cv::waitKey(0); // holds windows open until the user press a key
    return 0;
}

void usage()
{
    std::cout 
            << "This program performs road sign detection \n\n"
            << "In order to apply it, \n\n"
            << " follow the given instruction\n\n"
            << std::endl;
}