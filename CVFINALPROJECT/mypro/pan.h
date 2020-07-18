#ifndef PANO_H
#define PANO_H

#include <opencv2/features2d.hpp>
//#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/stitching.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <numeric>
#include <vector>

class Pano 
{
    public: 

        bool checkcolColor(cv::Mat &img, int x);
        cv::Mat removeSides(cv::Mat &img);
        std::vector<cv::KeyPoint> applySift(cv::Mat &imgIn);
        void knn(cv::Mat &descriptors1, cv::Mat &descriptors2, std::vector<cv::DMatch> &matches);
        void projCyldri(std::vector<cv::Mat> &imgIn, std::vector<cv::Mat> &imgOut, double f);
        cv::Mat panorama(std::vector<cv::Mat> & vecImg);

    private:
        int x = 0;
        int y =0;
};


#endif // PANO_H


