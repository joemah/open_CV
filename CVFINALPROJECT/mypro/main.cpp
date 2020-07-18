#include "pan.h"
#include <opencv2/stitching.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include <vector>
#include "pan.cpp"

int main ( int argc, char** argv )
{	
    // load the images 
    std::vector<cv::String> fname;
    //cv::glob("dolomites/*.png", fname, false);
    cv::glob("dolomites/*.png", fname, false);
    //cv::glob("lab/*.bmp", fname, false);
    //cv::glob("kitchen/*.bmp", fname, false);
    std::vector<cv::Mat> imgvector, panout;
    std::vector<cv::Mat> imgout;
    size_t count = fname.size();
    std::cout << "loading images " << std::endl;

    for (int i  = 0; i < count; i++)
    {
        imgvector.push_back(cv::imread(fname[i]));
            
    }
    // Check if have enough images
    cv::imshow("or", imgvector[0]);
    int numimages = static_cast<int>(imgvector.size());
    if (numimages < 2)
    {
        std::cout << "Need more images" << std::endl;
        return -1;
    }
    for (int i = 0; i < imgvector.size(); i++)
    {
        std::cout << "the image " << i << " is of size: " << imgvector[i].size() << std::endl;
    }

    std::cout << "loaded images, \nnow constructing the panorama." << std::endl; 

    Pano panorama; // create the panorama class object
	// turn to cylindrical
	panorama.projCyldri(imgvector, panout, 900);
    
    //cv::imshow("pan", panout[0]);
    //cv::imwrite("procyl.jpg", panout[0]);
	//remove the black edges from the side
    for (int i = 0; i < panout.size(); i++)
    {
        std::cout << "the image " << i << " is of size: " << panout[i].size() << std::endl;
    }
	for(int i=0; i < panout.size(); i++)
    {
        std::cout << "Removing black borders surrounding the image: " << i << std::endl;
        panout[i] = panorama.removeSides(panout[i]);
        
    }


	//panorama.matchTwoImages()
	// // constuct the panorama
    // std::cout << panout[0].size() << std::endl;
    // //::imshow("pan", panout[0]);

	imgout = panorama.panorama(panout);
	
    // // for (int i = 0; i < panout.size(); i++)
    // // {
    // //     std::cout << "the image " << i << " is of size: " << imgout[i].size() << std::endl;
    // // }
	
	// // std::cout << panout.size() << std::endl;

 
    cv::waitKey(0); 

	return 0;
}