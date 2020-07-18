// Project Computer Vision Course
// Joemah Magenya 
// Physics of Data 

#include <opencv2/features2d.hpp>
#include <opencv2/stitching.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

//#include "try.cpp"
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <numeric>
#include <vector>
#include "PanoramicUtils.cpp"

int main( int argc, char ** argv )
{   

    PanoramicUtils panimg;
    std::vector<cv::String> fname;
    cv::glob("dolomites/*.png", fname, false);
    cv::glob("kitchen/*.bmp", fname, false);
   // cv::glob("lab/*.bmp", fname, false);
    //cv::glob("pd/*.jpg", fname, false);

    std::vector<cv::Mat> imgvector;
    size_t count = fname.size();
    std::cout << "loading images " << std::endl;
    for (int i  = 0; i < count; i++)
    {
        imgvector.push_back(cv::imread(fname[i]));
            
    }
    cv::Mat pano;
    std::vector<cv::Mat> images;
    panimg.projectToClyldrical(imgvector, images, 500);
    for(int i=0; i < imgvector.size(); i++)
    {
        std::cout << "Clearing black borders surrounding the image: " << i << std::endl;
        images[i] = panimg.clearBlackBorders(images[i]);        
    }
    cv::imshow("Proj", images[0]);
    cv::imwrite("kmwb.jpg", images[0]);
    pano = panimg.panorama(images);
    std::cout << pano.size() << std::endl;
    cv::imshow("Panorama", pano);
    cv::imwrite("panorama.jpg", pano);
    cv::waitKey(0);
    return 0;
}


