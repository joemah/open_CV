#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <iostream> 
#include <string>
#include <vector>
#include "lDetector.h"


// bluring the input image
// apply the gaussian filter to sthe input image to denoise it
// return the denoise image

cv::Mat lDetector::noiseD(cv::Mat m_input)
{
    cv::Mat m_output, m_gray;
    cv::cvtColor(m_input, m_gray, cv::COLOR_RGB2GRAY);
    cv::GaussianBlur(m_gray, m_output, cv::Size(5, 5), 0, 0);

    return m_output;
}

// detect edges 
/* detect  all the edges in the blurred image 
   by applying the Canny edge detector
*/

cv::Mat lDetector::edgeD(cv::Mat m_noise)
{
    cv::Mat m_edge;
    //cv::cvtColor(m_noise, m_gray, cv::COLOR_RGB2GRAY);
    cv::Canny(m_noise, m_edge,  50, 150, 3);

    return m_edge;
}


cv::Mat lDetector::mask(cv::Mat m_edge)
{
    cv::Mat m_out;
    cv::Mat mask = cv::Mat::zeros(m_edge.size(), m_edge.type());
    cv::Point points[4] = { cv::Point(205, 615),
                            cv::Point(540,460 ),
                            cv::Point(715, 460),
                            cv::Point(1180, 615)
                            };
    // create a binary polygon mask
    cv::fillConvexPoly(mask, points,1, cv::Scalar(255, 0, 0), cv::LINE_AA, 0);
    // multiply the edge_image and the mask to get the output
    cv::bitwise_and(m_edge, mask, m_out);

    return m_out;
}

// Hough lines 
/* Obtain all the line segments in the masked image which  
    are going to be part of the lane boundaries
    the m_mask is the masked binary image from  the previous function 
    that conatins all the detected lines in the image
*/

std::vector<cv::Vec2f> lDetector::houghLines(cv::Mat m_mask)
{
    std::vector<cv::Vec2f> lines;
    cv::Mat cdst;
    HoughLines(m_mask, lines, 1, CV_PI/360 , 2, 0, 0 );

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
            cv::line(cdst , pt1, pt2, cv::Scalar(0, 0, 255));//, 3, cv::LINE_AA 
             
        }
    
    return lines;
    
}

std::vector<std::vector<cv::Vec2f> > lDetector::lSeparation(std::vector<cv::Vec2f> lines, cv::Mat m_edges)
{
    std::vector<std::vector<cv::Vec2f> > loutput(2); // stores the outputs of lines detected
    size_t j = 0;
    cv::Point2f init;
    cv::Point2f endp;
    double slopthresh = 0.3;
    std::vector<double> slopes;
    std::vector<cv::Vec2f> chosenLines;
    std::vector<cv::Vec2f> righlines, leftlines;
    
    // find the gradient of all the detected lines 

    for (auto i: lines )
    {
        init = cv::Point2f(i[0], i[1]);
        endp = cv::Point2f(i[2], i[3]);
        
        double slope = (static_cast<double>(endp.y) -static_cast<double>(init.y))/(static_cast<double>(endp.x)-static_cast<double>(init.x) + 0.00001);

        // if the slope is horizontal, delete the line
        // otherwise, save and their respective slopes
        if(std::abs(slope)>slopthresh)
        {
            slopes.push_back(slope);
            chosenLines.push_back(i);
        }
    }
    // split lines into right and left lines
    imgcenter = static_cast<double>((m_edges.cols/2));
    while (j < chosenLines.size())
    {

        init = cv::Point2f(chosenLines[j][0], chosenLines[j][1]);
        endp = cv::Point2f(chosenLines[j][2], chosenLines[j][3]);

        // logic to classify lines as left or right

        if (slopes[j] > 0 && endp.x > imgcenter && init.x > imgcenter)
        {
            righlines.push_back(chosenLines[j]);
            rflags = true;
        }
        else if (slopes[j] < 0 && endp.x < imgcenter && init.x < imgcenter)
        {
            leftlines.push_back(chosenLines[j]);
            lflags = true;
        }
        j++;
    }

    loutput[0] = righlines;
    loutput[1] = leftlines;

    return loutput;
}

float lDetector::plotLine(cv::Mat m_input, std::vector<std::vector<cv::Point2f> > line)
{
    std::vector<cv::Point2f> polypts; // polygon points
    cv::Mat output;
    
    // create the transparent polygoly for better visualisation of the lane
    m_input.copyTo(output);
    polypts.push_back(line[2]);
    polypts.push_back(line[0]);
    polypts.push_back(line[1]);
    polypts.push_back(line[3]);
    //cv::fillConvexPoly(output, polypts, 1, cv::Scalar(0, 0, 255), LINE_AA, 0);
    //cv::addWeighted(output, 0.3, m_input, 1.0-0.3, 0, m_input);

    // plot both lines of the boundary

    cv::line(m_input, line[0], line[1], cv::Scalar(0, 255, 255), 5, cv::LINE_AA);
    cv::line(m_input, line[0], line[1], cv::Scalar(0, 255, 255), 5, cv::LINE_AA);

    //cv::putText(m_input, turn, cv::Point(50, 90), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, cvScalar(0, 255, 0), 1, LANE_AA);  

    cv::namedWindow("Detected Lane", cv::WINDOW_AUTOSIZE);
    cv::imshow("Detected Lane", m_input);

    return 0;  
  
}
