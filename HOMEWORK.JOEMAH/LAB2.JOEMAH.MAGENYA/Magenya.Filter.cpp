// CREATED BY JOEMAH MAGENYA
// PHYSICS OF DATA 
// ID 1233392
/* Computer vison Asignment

    WHAT THE CODE DOES
    *receives an input image from  the user
    *Perfoms the filtering using Bilateral, MEdian and the GaussianBlur opencv functions
    *Filtering is done to  improve the quality  of the image, thus removing all the undesired noise. 
    *For each filter, a buffer is used to loop over different kernels of size kxk where k is odd > 3. 
    *The desired kernel size is then chosen by visualising changes in the filtered image. 
    *The best kernel basically depends on the Image to be filtered.

*/

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>


// initialize constants 

int size  = 10;


// funtion header 

void usage( char** argv); // a function  that gives instuction  on how to use the program

// the main  function  

int main(int argc, char** argv)
{
    usage(argv);

    if (argc < 2) // check  if the user followed the given  instruction  that is how to load the imge of choice
    {
        std::cout << "Please follow  instructions" << std::endl;
        return -1;
    }

    char window [] = "My Window"; // create a window name
    char windo [] = "Our filter";
    char wind []  = "Filtered By Gauass";
    char mymedien [] = "Filter With MedianBlur";
    cv::Mat image;
    cv::Mat image_outb;
    cv::Mat image_outm;
    cv::Mat image_outg;

    char zBuffer[35]; // detect hidden surfaces

    image = cv::imread(argv[1]); // load  the image to be filtered

    if (image.empty()) // check if the  the image is loaded or not 
    {
        std::cout << "Please load a proper image " << std::endl;
        return -1;
    }


    for (int i = 1; i < 80; i = i +2)
    {
        snprintf(zBuffer, 35, "kernel Size:  %d x %d",i, i); // copy the text to the zBuffer
        cv::bilateralFilter(image, image_outb, i, i, i); // remove noise using the Bilateral filter
        cv::putText(image_outb, zBuffer, cv::Point(image.cols/4, image.rows/8), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255, 255, 255), 2); // put text in the zBuffer to the "final image"
        cv::namedWindow(window, cv::WINDOW_AUTOSIZE); // create an empty  window
        cv::namedWindow(windo, cv::WINDOW_AUTOSIZE);
        cv::namedWindow(windo, cv::WINDOW_AUTOSIZE);
        cv::imshow(window, image); // whow the original image 
        cv::imshow(windo, image_outb); // show the filtered  image 
        cv::medianBlur(image, image_outm, i);
        cv::putText(image_outm, zBuffer, cv::Point(image.cols/4, image.rows/8), cv::FONT_HERSHEY_COMPLEX,1,cv::Scalar(255,255,255),2);
        cv::imshow(mymedien, image_outm);

        cv::GaussianBlur(image, image_outg, cv::Size(i,i),0,0);
        cv::putText(image_outg, zBuffer, cv::Point(image.cols/4, image.rows/8), cv::FONT_HERSHEY_COMPLEX,1,cv::Scalar(255,255,255), 2);
        cv::imshow(wind, image_outg);

        int c = cv::waitKey(4000); // wait for two seconds

        if (c == 27)
        {
            return 0;
        }
    }
  
    
    cv::waitKey(0); // wait a bit
    return 0;

}

void usage(char** argv)
{
    std::cout << "In order to  use this program v please do follow the instuctions otherwise you  will  not be able to rutn  the  program\n\n"
        << "load the image as follow \n\n"
        << argv[0] << " path/imagename.extnsioname\n\n" 
        << "For example ./" << argv[0]<< "./imagename.imageextension" // argv[o] is the name of the program.
        << std::endl;

}



