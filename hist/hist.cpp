#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <vector>
#include <string>
#include <iostream>

void usage( char** argv); // a function  that gives instuction  on how to use the program

void showHistogram(std::vector<std::string> windowname, cv::Mat& img)
{   
    char tmpStr[256]; // temporary string 
    int bins = 256;// define the number of bins
    int chan = img.channels(); // number of channels

    std::vector<cv::Mat> hist(chan);

    // initialize histogram arrays

    for (int i = 0; i < hist.size(); i++)
    {
        hist[i] = cv::Mat::zeros(1, bins, CV_32SC1);
    }

    // calculate the histogram of the image

    for (int i = 0; i<img.rows; i++)
    {
        for (int j = 0; j<img.cols; j++)
        {
            for (int k = 0; k<chan; k++)
            {
               uchar val = chan == 1? img.at<uchar>(i, j) : img.at<cv::Vec3b>(i, j)[k];
               hist[k].at<int>(val) += 1; 
            }
        }
    }

    // for each histogram arrays, obtain the maximum (peak) value
    // needed to  normalize the dispay later

    int hmax[3] = {0, 0, 0};

    for (int i = 0; i < chan; i++)
    {
        for (int j = 0; j < bins-1; j++)
        {
            if (hist[i].at<int>(j)> hmax[i])
            {
                hmax[i] = hist[i].at<int>(j);
            }
            else
            {
                hmax[i] = hmax[i];
            }
            
            //hmax[i] = hist[i].at<int>(j) > hmax[i]? hmax[i].at<int>(j) : hmax[i];
        }
    }

    //const char* windowname[3] = {"Blue", "Green", "Red"};
    //const char* window[3] = {"EBlue", "EGreen", "ERed"};
    cv::Scalar colors[3] = { cv::Scalar(255, 0, 0), cv::Scalar(0, 255, 0), cv::Scalar(0, 0, 255)};

    std::vector<cv::Mat> canvas(chan);

    // display each histogram in a canvas
    for (int i = 0; i < chan; i++)
    {
        canvas[i] = cv::Mat::ones(125, bins, CV_8UC3);

        for(int j = 0, rows = canvas[i].rows; j < bins -1; j++)
        {
            cv::line(
                    canvas[i],
                    cv::Point(j, rows), 
                    cv::Point(j, rows-(hist[i].at<int>(j) * rows/hmax[i])),
                    chan == 1? cv::Scalar(200, 200, 200): colors[i],
                    1, 8, 0
                    );
        }

        //std::sprintf( tmpStr, "%s: %s", title, chan == 1 ? "value" : windowname[i]);
		//imshow( tmpStr, canvas[i]);  
        imshow(chan == 1 ? "value" : windowname[i], canvas[i]);  
        //imwrite(chan == 1 ? "value" : windowname[i], canvas[i]);  


    }
}


int main(int argc, char** argv)
{   
    usage(argv);

    if (argc < 2) // check  if the user followed the given  instruction  that is how to load the imge of choice
    {
        std::cout << "Please follow  instructions" << std::endl;
        return -1;
    }

    cv::Mat imageq;
  //char* window = (char*)"Equalized Image"; 
    //char input_window[128] = "Original Image";
    cv::Mat imgin = cv::imread(argv[1]);  // read an image of your choice as input 

 // check if the image is readable or not 
    if (imgin.empty())
    {
        std::cout << "The image you  are trying to open is not corrupted" << std::endl; // prints the error message to the user
        std::cin.get(); // waits for the user to press an input key
        return -1; // return 0 if the program runs perfectly else -1 if there is an error
    }


    // separate the image in 3 places ( B, G and R )
    std::vector<cv::Mat> bgr_planes; // initias the image with all  channels
    cv::split( imgin, bgr_planes ); // clone the input image to  the brg_planes and separate the channels
    cv::equalizeHist(bgr_planes[0], bgr_planes[0]); // equalize the  channels
    cv::equalizeHist(bgr_planes[1], bgr_planes[1]);
    cv::equalizeHist(bgr_planes[2], bgr_planes[2]);
    cv::merge(bgr_planes, imageq);  // merge the equalized channels and assign them to imageq

    // display equalized image
    showHistogram({"EBlue", "EGreen", "ERed"}, imageq); // show the histograms of the equalized image
    cv::imshow("Equalized Image ", imageq);
    //cv::imwrite("Equalized Image ", imageq);


    showHistogram({"Blue", "Green", "Red"}, imgin);
    cv::imshow("original  Image", imgin); // show the input image with its histogams
    //cv::imwrite("Equalized Image ", imageq);
    cv::waitKey(0); // wait until  the user exist the program
    return 0;
}
void usage(char** argv) // gives the direction of use of the program  to the user
{
    std::cout << "In order to  use this program v please do follow the instuctions otherwise you  will  not be able to rutn  the  program\n\n"
        << "load the image as follow \n\n"
        << argv[0] << " path/imagename.extnsioname\n\n" 
        << "For example ./" << argv[0]<< "./imagename.imageextension" // argv[o] is the name of the program.
        << std::endl;

}

