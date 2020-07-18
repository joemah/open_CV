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
#include <sstream>
#include <fstream>
#include <memory>
#include <iostream>
#include <vector>
#include <numeric>
#include <vector>

// declaration of global variables
std::vector<std::vector<cv::KeyPoint>> keypoints;
std::vector<float> position;
std::vector<cv::Mat> descriptors;
int imgpairs;
float dist_x = 0; 
std::vector<std::vector<cv::DMatch>> matches;

void DetectAndCompute(std::vector<cv::Mat> cylimages)
{
    //detect and compute features for each  image using SIFT
    int size = cylimages.size(); // total number of images
    cv::Ptr<cv::SIFT> detector = cv::SIFT::create();
    descriptors = std::vector<cv::Mat>(size);
    keypoints = std::vector<std::vector<cv::KeyPoint>>(size);

    // detect the keypoints and computer descriptors,  both at the same time
    for (auto i = 0; i < size ; i++)
    {
        std::cout << "Extracting SIFT descriptors from image number of the image: " << i << std::endl;
        detector->detectAndCompute(cylimages[i], cv::noArray(), keypoints[i], descriptors[i]);
    }
}
//find good  matches for each pair of images
void matchpair(std::vector<cv::Mat> cylimages, double scale)
{  
    int imgpairs = cylimages.size() - 1;
    cv::Ptr<cv::BFMatcher> matcher = cv::BFMatcher::create(cv::NORM_L2);
    matches = std::vector<std::vector<cv::DMatch>>(imgpairs);
    // find matches for each pairs of images 
    for (auto i = 0; i < imgpairs; i++)
    {
        matcher->match(descriptors[i], descriptors[i + 1], matches[i]);
        std::cout << "matching image:" << i << " and image " << i + 1 << std::endl;
        //sort matches
        std::sort(matches[i].begin(), matches[i].end());

        auto threshold = scale * matches[i][matches[i].size() - 1].distance;
        std::vector<cv::DMatch> goodmatches;
        for (auto j : matches[i])
        {
            if (j.distance > threshold)
                break;
            goodmatches.push_back(j);
        }
        matches[i].clear();
        matches[i] = goodmatches;
    }
    std::cout << "Found " << matches.size() << " matches" << std::endl;

}

void findhomographs(std::vector<cv::Mat> cylimages)
{
    //compute homographs for a  couple
    imgpairs = cylimages.size() - 1;
    std::vector<std::vector<uchar>> masks;
    masks = std::vector<std::vector<uchar>>(imgpairs);
    position = std::vector<float>(imgpairs);
    for (size_t i = 0; i < imgpairs; i++)
    {

        std::vector<cv::Point2f> pts1, pts2;
        //get the keypoints from the good matches
        for (int j = 0; j < matches[i].size(); j++)
        {
            pts1.push_back(keypoints[i][matches[i][j].queryIdx].pt);
            pts2.push_back(keypoints[i + 1][matches[i][j].trainIdx].pt);
        }
        //std::cout << matches[0] << std::endl;
        cv::Mat imgmatches;
        cv::drawMatches(cylimages[0], keypoints[i], cylimages[1], keypoints[i+1],
                        matches[i],imgmatches, cv::Scalar::all(-1), cv::Scalar::all(-1),
                        std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
        cv::imshow("mypoints.jpg", imgmatches);
        cv::imwrite("imgmaches.jpg", imgmatches);
        //std::cout << imgmatches.size() << std::endl;
        cv::findHomography(pts1, pts2, masks[i], cv::RANSAC);

        // compute  the average x distance for a pair of images corresponding to good matches
        float shift = 0; 
        float pos_x = 0;
        for (auto j = 0; j < matches[i].size(); j++)
        {
            if (masks[i][j] != 0) {
                shift += abs(pts1[j].x - pts2[j].x);
                pos_x++;
            }
        }
        shift = shift / pos_x++;
        position[i] = shift; 
        dist_x += shift;
    }
}

cv::Mat panorama(std::vector<cv::Mat> cylimages)
{

    int size = cylimages.size(); // total number of images 

    std::cout << "A panorama from " << size << " images." << std::endl;
    
    int length = dist_x + cylimages[0].cols; //length of the panorama

    cv::Mat panorama = cv::Mat(cylimages[0].rows, length, cylimages[0].type()); // Canvas where the panorama will be saved

    int x = 0; // initialize the  position of x 
    for (auto i = 0; i < size; i++)
    {
        cv::Mat panotemp = cv::Mat(panorama, cv::Rect(x, 0, cylimages[i].cols, cylimages[i].rows));
        cylimages[i].copyTo(panotemp);
        if (i >= imgpairs) 
        {
            break;
        }
        x += position[i]; // compute the current position of x 
    }
    return panorama; 
}


