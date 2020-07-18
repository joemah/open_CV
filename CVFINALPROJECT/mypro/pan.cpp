#include "pan.h"
#include <opencv2/stitching.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/calib3d/calib3d.hpp>
//#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include <vector>

using namespace cv;
using namespace cv::xfeatures2d;

cv::Scalar colors[8] = {cv::Scalar(  0,   0, 204),
                        cv::Scalar(  0, 200, 255),
                        cv::Scalar(  0, 255,   0),
                        cv::Scalar(255,  51, 102),
                        cv::Scalar(238, 130, 238),
                        cv::Scalar(255, 255, 255),
                        cv::Scalar(128, 128, 128),
                        cv::Scalar(  0,   0,   0)};

cv::Vec3b keyColor(0,0,0);

#define red      0
#define yellor   1
#define green    2
#define blue     3
#define violet   4
#define white    5
#define gray     6
#define black    7


bool Pano::checkcolColor(cv::Mat &img, int x)
{
    for(int y=0; y<img.rows; y++)
	{
		if(img.at<cv::Vec3b>(y,x) != keyColor)
            return false;
    }
    return true;
}

cv::Mat Pano::removeSides(cv::Mat &img)
{
    int posxinit = 0, posxfinal = img.cols-1;
	bool logic;

	do
    {
		logic = false;
		if(Pano::checkcolColor(img, posxinit))
        { 
            posxinit++;	logic = true; 
        }
		if(Pano::checkcolColor(img, posxfinal))
        {
             posxfinal--;	logic = true;
        }
	}
    while(logic);
	return img(cv::Rect(posxinit, 0, posxfinal-posxinit+1, img.rows));
}



std::vector<cv::KeyPoint> Pano::applySift(cv::Mat &imgIn)
{
    cv::Mat img;                     // temporary image
	std::vector<cv::KeyPoint> keypoints;  // sift parameters
	
	cv::cvtColor(imgIn, img, cv::COLOR_RGB2GRAY);

    //define Sift object and extract keypoints
	cv::Ptr<SIFT> sift = SIFT::create();
    sift->detect(img, keypoints);

    //calculate the level of the pyramid to represent it later

    // for(unsigned int i=0; i<keypoints.size(); i++)
    // {
	// 	keypoints[i].octave = keypoints[i].octave & 0xFF;
	// 	if(keypoints[i].octave==255)
	// 		keypoints[i].octave = 0;
	// 	else
	// 		keypoints[i].octave++;
	// }

	return keypoints;
}



void Pano::knn(cv::Mat &descriptors1, cv::Mat &descriptors2, std::vector<cv::DMatch> &matches)
{
	std::vector<std::vector<cv::DMatch>> prematches;
	int k = 2; // number of matches to be returned
	cv::FlannBasedMatcher matcher;
	matcher.knnMatch(descriptors1, descriptors2, prematches, k); // Find two nearest matches
	//matches.reserve(prematches.size());

	const float thresholdratio = 0.7f;

    for (size_t i = 0; i < prematches.size(); i++)
    {
        if (prematches[i][0].distance < thresholdratio * prematches[i][1].distance)
        {
            matches.push_back(prematches[i][0]);
        }
    }
}


void Pano::projCyldri(std::vector<cv::Mat> &imgIn, std::vector<cv::Mat> &imgOut, double f)
{
    cv::Mat imgTmp;
	double xi, yi, xImg, yImg;

	imgOut.clear();
	imgOut.resize(imgIn.size());
	for(int k=0; k<imgIn.size(); k++)
    {
		if(imgIn[k].channels()!=3)
			cvtColor(imgIn[k], imgIn[k], cv::COLOR_GRAY2BGR);

		//create the destination image in black
		imgTmp.create(imgIn[k].rows, imgIn[k].cols, imgIn[k].type());
		imgTmp = colors[black];

		//check for the matches. As in OpenCV the point (0,0) is in
        //the upper left corner, it is necessary to carry out a translation prior to
        //transformation itself, to have the (0,0) in the center.
		for(int i=0; i<imgIn[k].rows; i++)
        {
			for(int j=0; j<imgIn[k].cols; j++)
            {
				// move the point (i, j)
				xi =  j - (0.5*imgIn[k].cols)+1;
				yi =  i - (0.5*imgIn[k].rows)+1;
				//calculate the x coordinate in the original image that corresponds to the transformed image
				xImg = f*tan(xi/f);
				//calculate the y coordinate in the original image that corresponds to the transformed image
				yImg = yi*sqrt(1+pow(tan(xi/f),2));
				//restore the displacement
				xImg =  xImg + (0.5*imgIn[k].cols)-1;
				yImg =  yImg + (0.5*imgIn[k].rows)-1;
				//If the point (xImg, yImg) is within the limits of the original image, take its color
				if( yImg>=0.0 && yImg<imgIn[k].rows && xImg>=0.0 && xImg<imgIn[k].cols)
					imgTmp.at<cv::Vec3b>(i,j) = imgIn[k].at<cv::Vec3b>(yImg, xImg);
			}
		}
		imgTmp.copyTo(imgOut[k]);
	}
}


cv::Mat Pano::panorama(std::vector<cv::Mat> &vecImg)
{	

    std::vector< std::vector<cv::KeyPoint> > keypoints;   // saves keypoints
	std::vector<cv::Point2f> pointsrc, pointdst;     // saves matching points
	std::vector<cv::DMatch>  matches;
	std::vector<cv::Mat>    descriptors, homografs;
	cv::Ptr<SIFT> extractor = SIFT::create();  // Extract descriptors
	int length = vecImg[0].cols*2*(vecImg.size());
	int height  = vecImg[0].rows*2;
	int half = (vecImg.size()-1)/2;
     

    std::cout << height << "\n" << length << "\n" << half << std::endl;
	cv::Mat canvas(height, length, CV_8UC3), panor; // Canvas where the panorama will be saved

	homografs.resize(vecImg.size());
	keypoints.resize(vecImg.size());
	descriptors.resize(vecImg.size());

	//find sift keypoints and descriptors

	for(int i=0; i<vecImg.size(); i++){
		std::cout << "Extracting SIFT descriptors from image number of the image: " << i << std::endl;
		//extract the keyPoint
		keypoints[i] = Pano::applySift(vecImg[i]);
		//compute descriptors
		extractor->compute(vecImg[i], keypoints[i], descriptors[i]);
		//cv::imshow("ff", vecImg[0]);

	}

    
   
	//std::cout << img_keypoints.type() << std::endl;
	//calculate the homographies of all the images
    //Preset the homography that goes between the central image and the canvas

	homografs[half] = (cv::Mat_<double>(3, 3) <<   1, 0, (length/2),
                                                 0, 1, (height-vecImg[0].rows)/2,
                                                 0, 0, 1);

	// calculate the homographs on the right side
	for(int i=half+1; i<vecImg.size(); i++)
    {
		std::cout << "Calculating homography of the right image number: " << i << std::endl;

		
		Pano::knn(descriptors[i], descriptors[i-1], matches);

		double max_dist = 0; double min_dist = 100;

	//-- Quick calculation of max and min distances between keypoints 
		for( int m = 0; m < descriptors[i-1].rows; m++ )
		{ 
			double dist = matches[m].distance;
			if( dist < min_dist ) min_dist = dist;
			if( dist > max_dist ) max_dist = dist;
		}
		printf("max dist: %f \n", max_dist );
		printf("min dist: %f \n", min_dist );
		// save the points
		for(unsigned int j=0; j < matches.size(); j++)
        {
			pointsrc.push_back(keypoints[i][matches[j].queryIdx].pt);
			pointdst.push_back(keypoints[i-1][matches[j].trainIdx].pt);
		}
		// find the homography
		homografs[i] = findHomography(pointsrc, pointdst, cv::RANSAC);
		homografs[i] = homografs[i-1]*homografs[i];
	}

	// calculate the homographs on the left side
	for(int i=half-1; i>=0; i--)
    { //int i=half+1
		std::cout << "Calculating homography of the left image number: " << i << std::endl;
		Pano::knn(descriptors[i], descriptors[i+1], matches);

		double max_dist = 0; double min_dist = 100;

	//-- Quick calculation of max and min distances between keypoints 
		for( int m = 0; m < descriptors[i-1].rows; m++ )
		{ 
			double dist = matches[m].distance;
			if( dist < min_dist ) min_dist = dist;
			if( dist > max_dist ) max_dist = dist;
		}
		printf("max dist: %f \n", max_dist );
		printf("min dist: %f \n", min_dist );
		//save the points
		for(unsigned int j=0; j<matches.size(); j++)
        {
			pointsrc.push_back(keypoints[i][matches[j].queryIdx].pt);
			pointdst.push_back(keypoints[i+1][matches[j].trainIdx].pt);
		}
		// find the homography
		homografs[i] = (findHomography(pointsrc, pointdst, cv::RANSAC, 1, cv::noArray()));
		homografs[i] = homografs[i+1]*homografs[i];

		 cv::Mat imgmatches;
    	cv::drawMatches( vecImg[0], keypoints[i], vecImg[1], keypoints[i+1],
                    matches,imgmatches, cv::Scalar::all(-1), cv::Scalar::all(-1),
                    std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
		cv::imshow("myfeatures", imgmatches);

	}
	
	
	// construct the panorama
	// cv::warpPerspective(vecImg[0], canvas, homografs[0], 
    //                     cv::Size(canvas.cols, 
    //                     canvas.rows), 1, 
    //                     cv::BORDER_CONSTANT, colors[black]);
    
    // cv::Mat result;
	// // cv::Mat result23;
	
	// for(int i=1; i<vecImg.size(); i++)
    // {   
        
	// 	// transform the image to include in the panorama
	// 	cv::warpPerspective(vecImg[i],canvas,homografs[i],cv::Size(vecImg[i].cols+vecImg[i+1].cols,vecImg[i].rows));
	// 	cv::Mat half(canvas,cv::Rect(0,0,vecImg[i+1].cols,vecImg[i+1].rows));
	// 	vecImg[i+1].copyTo(half);
	// 	// cv::warpPerspective(vecImg[i], panor, homografs[i],
    //     //                     cv::Size(canvas.cols, canvas.rows), 1,
    //     //                     cv::BORDER_TRANSPARENT, colors[black]);

	// }
	// std::cout << canvas.size() << std::endl;
	// //cv::imshow("can", canvas);
	// cv::waitKey(0);
	return canvas;
}










