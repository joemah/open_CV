// Project Computer Vision Course
// Joemah Magenya 
// Physics of Data 

#ifndef PANORAMIC_UTILS_H
#define PANORAMIC_UTILS_H

#include <memory>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/stitching.hpp>

// declaration of global variables
std::vector<std::vector<cv::KeyPoint>> keypoints;
std::vector<float> position;
std::vector<cv::Mat> descriptors;
int imgpairs;
float dist_x = 0; 
std::vector<std::vector<cv::DMatch>> matches;


cv::Scalar colors[8] = {cv::Scalar(  0,   0, 204), cv::Scalar(  0, 255,   0),
                        cv::Scalar(255,  51, 102), cv::Scalar(  0, 200, 255),
                        cv::Scalar(238, 130, 238), cv::Scalar(255, 255, 255),
                        cv::Scalar(128, 128, 128), cv::Scalar(  0,   0,   0)};

cv::Vec3b keycolor(0,0,0);

#define red      0
#define yellor   1
#define green    2
#define blue     3
#define violet   4
#define white    5
#define gray     6
#define black    7

//using namespace cv;

class PanoramicUtils
{
    public:

        void projectToClyldrical(std::vector<cv::Mat> &imgs, // input images 
                                 std::vector<cv::Mat> &cylimages, // projected images 
                                 double f // scaling factor  for a better alignment 
                                 )
        {
            cv::Mat imgtmp; // images placeholder 
            double xi, yi, xImg, yImg; // initial and final  postions 

            cylimages.clear(); // initialize the images 
            cylimages.resize(imgs.size()); // resize the projected images to  the same size as the original  image
            for(int k=0; k<imgs.size(); k++)
            {
                if(imgs[k].channels()!=3)
                    cvtColor(imgs[k], imgs[k], cv::COLOR_GRAY2BGR); // convert to grayscale 

                //create the destination image in black
                imgtmp.create(imgs[k].rows, imgs[k].cols, imgs[k].type());
                imgtmp = colors[black];

                //check for the matches. As in OpenCV the point (0,0) is in
                //the upper left corner, it is necessary to carry out a translation prior to
                //transformation itself, to have the (0,0) in the center.
                for(int i=0; i<imgs[k].rows; i++)
                {
                    for(int j=0; j<imgs[k].cols; j++)
                    {
                        // move the point (i, j)
                        xi =  j - (0.5*imgs[k].cols)+1;
                        yi =  i - (0.5*imgs[k].rows)+1;
                        //calculate the x coordinate in the original image that corresponds to the transformed image
                        xImg = f*tan(xi/f);
                        //calculate the y coordinate in the original image that corresponds to the transformed image
                        yImg = yi*sqrt(1+pow(tan(xi/f),2));
                        //restore the displacement
                        xImg =  xImg + (0.5*imgs[k].cols)-1;
                        yImg =  yImg + (0.5*imgs[k].rows)-1;
                        //If the point (xImg, yImg) is within the limits of the original image, take its color
                        if( yImg>=0.0 && yImg<imgs[k].rows && xImg>=0.0 && xImg<imgs[k].cols)
                            imgtmp.at<cv::Vec3b>(i,j) = imgs[k].at<cv::Vec3b>(yImg, xImg);
                    }
                }
                imgtmp.copyTo(cylimages[k]); 
            }
        }

        // select the keycolor
        bool checkcolcolor(cv::Mat &img, int x)
        {
            for(int y=0; y<img.rows; y++)
            {
                if(img.at<cv::Vec3b>(y,x) != keycolor)
                    return false;
            }
            return true;
        }

        cv::Mat clearBlacksEdges(cv::Mat &img)
        {
            int posxinit = 0, posxfinal = img.cols-1;
            bool isblack;
            // check for each side, the edges to eliminate
            do
            {
                isblack = false;
                if(checkcolcolor(img, posxinit))  // left column 
                { 
                    posxinit++;	
                    isblack = true; 
                }
                if(checkcolcolor(img, posxfinal)) // right column
                {
                    posxfinal--;	
                    isblack = true; 
                }
            }
            while(isblack);
            return img(cv::Rect(posxinit, 0, posxfinal-posxinit+1, img.rows));
        }

        // Take an image, a column and a threshold and count the number of pixels with
        // color other than that indicated by keyColor.
        // If the threshold is exceeded it returns false         
        //   Returns true if the threshold is not exceeded

        // scan the images to check  for keycolor
        bool checkrowcolor(cv::Mat &img, int y, int thresh)
        {
            int nbpixels = 0; // total number os black pixels
            bool bol = true; 
            for(int x= 0; x<img.cols && nbpixels < thresh ; x++) // x column to  scan
                if(img.at<cv::Vec3b>(y,x) != keycolor) nbpixels++;

            if(nbpixels >= thresh )	bol = false;

            return bol;
        }

        bool checkColcolor(cv::Mat &img, int x, int thresh)
        {
            int nbpixels = 0;
            bool ret = true;
            for(int y=0; y<img.rows && nbpixels < thresh; y++)
                if(img.at<cv::Vec3b>(y,x) != keycolor) nbpixels++;

            if(nbpixels >= thresh)	
            {
                ret = false;
            }

            return ret;
        }
        // count  the maxmum  number of black pixels in rows
        int mxblackRows(cv::Mat &img){
            int nbpixels,mxbpixels = 0; // number and max black  pixels
            for(int i=0; i<img.rows; i++)
            {
                nbpixels = 0;
                for(int x=0; x<img.cols; x++)
                {
                    if(img.at<cv::Vec3b>(i,x) != keycolor) nbpixels++;
                }
                if(nbpixels > mxbpixels) mxbpixels = nbpixels;
            }

            return mxbpixels; // return the max of black pixels
        }


        int mxblackCols(cv::Mat &img)
        {
            int nbpixels,mxbpixels = 0; // initialize the numbeer and max of black pixels
            for(int i=0; i<img.cols; i++){
                nbpixels=0;
                for(int y=0; y<img.rows; y++)
                    {
                        if(img.at<cv::Vec3b>(y,i) != keycolor) nbpixels++;
                    }	

                if(nbpixels > mxbpixels) mxbpixels = nbpixels;
            }

            return mxbpixels; 
        }

        // remove all black edges within the image for each row

        cv::Mat clearBlackBorders(cv::Mat &img)
        {
            clearBlacksEdges(img);
            int xi = 0, xf = img.cols-1; // initial and final  positions of x
            int yi = 0, yf = img.rows-1; // initial  and final  positions  of y
            bool trans;
            double thresh = 0.95;
            
            int maxcol = mxblackCols(img)*thresh;
            int maxrow = mxblackRows(img)*thresh;
            
            do
            {
                trans = false;		
                if(checkrowcolor(img, yi,maxrow))
                { 
                    yi++; 
                    trans = true; // upper row

                }		
                if(checkrowcolor(img, yf,maxrow))
                { 
                    yf--; 
                    trans = true;  // bottom row
                }
            }
            while(trans);
            cv::Mat image = img(cv::Rect(0, yi, xf + 1, yf - yi + 1));
            maxcol = mxblackCols(image);

            do
            {
                trans = false;		
                if(checkColcolor(img, xi , maxcol))  // left col
                { 
                    xi++;	
                    trans = true; 
                
                }
                		
                if(checkColcolor(img, xf,maxcol)) // right col
                { 
                    xf--;	
                    trans = true;  
                } 		
            }
            while(trans);
            return img(cv::Rect(xi, yi, xf - xi + 1, yf - yi + 1)); // return an image without borders
        }


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
            DetectAndCompute(cylimages);
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
            matchpair(cylimages, 0.3);
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
                std::cout << "Finding homograph of images " << i << " and " << i + 1  << std::endl;
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
            findhomographs(cylimages);
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


    
};

#endif // PANORAMIC_UTILS_H




